// main.cpp
#include <stdlib.h>
#include <stdio.h>
#pragma hdrstop
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <ctype.h>
#include <getopt.h>
#include <stdarg.h>
#pragma hdrstop

// PROJECT: CSocket
#define BIT(x) (1 << (x))


long long get_timestamp() {
	time_t t;
	time(&t);
	return t * 1000ll;
}

int set_interface_attribs(int fd, int speed, int parity) {
	struct termios tty;
	if(tcgetattr(fd, &tty) != 0) {
		fprintf(stderr, "error %d from tcgetattr", errno);
		return -1;
	}
	cfsetospeed(&tty, speed);
	cfsetispeed(&tty, speed);
	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break as \000 chars
	tty.c_iflag &= ~IGNBRK; // disable break processing
	tty.c_lflag = 0;		// no signaling chars, no echo,  no canonical processing
	tty.c_oflag = 0;		// no remapping, no delays
	tty.c_cc[VMIN] = 0;		// read doesn't block
	tty.c_cc[VTIME] = 5;	// 0.5 seconds read timeout
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
	tty.c_cflag |= (CLOCAL | CREAD);   // ignore modem controls, enable reading
	tty.c_cflag &= ~(PARENB | PARODD); // shut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;
	if(tcsetattr(fd, TCSANOW, &tty) != 0) {
		fprintf(stderr, "error %d from tcsetattr", errno);
		return -1;
	}
	return 0;
}

void set_blocking(int fd, int should_block) {
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	if(tcgetattr(fd, &tty) != 0) {
		fprintf(stderr, "error %d from tggetattr", errno);
		return;
	}
	tty.c_cc[VMIN] = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout
	if(tcsetattr(fd, TCSANOW, &tty) != 0) {
		fprintf(stderr, "error %d setting term attributes", errno);
	}
}

static bool runner_value = false;
pthread_mutex_t lock;
void set_runner(bool state) {
	pthread_mutex_lock(&lock);
	runner_value = state;
	pthread_mutex_unlock(&lock);
}

bool is_runner() {
	bool state = false;
	pthread_mutex_lock(&lock);
	state = runner_value;
	pthread_mutex_unlock(&lock);
	return state;
}

void set_idle_priority(pthread_t tid) {
	struct sched_param param;
	param.sched_priority = 0;
	if(pthread_setschedparam(tid, SCHED_OTHER, &param) != 0) {
		perror("pthread_setschedparam");
	}
}

void *read_callback(void *ptr) {
	int fd = *reinterpret_cast<int *>(ptr);
	char buffer[512];
	int count;
	
	printf("Listing port ...\n");
	while(true) {
		count = read (fd, buffer, sizeof buffer);
		if(count < 0) {
			break;
		}
		fwrite(buffer, sizeof(char), count, stdout);
		fflush(stdout);
		usleep ((7 + 25) * 100);
	}
	return nullptr;
}

void help(const char *basename) {
	printf("Usage: %s [OPTION]\n", basename);
	printf("\t-h, --help\t\tPrint this help and exit.\n");
	printf("\t-p, --port=PORT\tserial port address\n");
	printf("\t-b, --baud=115200\tbaudrate Hz\n");
	printf("\t-e, --eof=[CR|LF|CRLF|NONE]\tflush serial\n");
}

int get_baudrate(const char *arg) {
	int value = atoi(arg);
	int baudate;
	switch(value) {
	case 110: baudate = B110; break;
	case 300: baudate = B300; break;
	case 600: baudate = B600; break;
	case 1200: baudate = B1200; break;
	case 2400: baudate = B2400; break;
	case 4800: baudate = B4800; break;
	case 9600: baudate = B9600; break;
	case 19200: baudate = B19200; break;
	case 38400: baudate = B38400; break;
	case 57600: baudate = B57600; break;
	default:
	case 115200: baudate = B115200; break;
	}
	return baudate;
}

enum { 
	FT_NONE = 0,
	FT_CR = BIT(1), 
	FT_LF = BIT(2), 
	FT_CRLF = FT_CR | FT_LF
};
int get_flush_type(const char *arg) {
	if(strcmp(arg, "CR") == 0) {
		return FT_CR;
	}
	if(strcmp(arg, "LF") == 0) {
		return FT_LF;
	}
	if(strcmp(arg, "CRLF") == 0) {
		return FT_CRLF;
	}
	return FT_NONE;
}

int write_va(int fd, int eof, const char *format, ...) {
	char buffer[1024];
	va_list argptr;
	int count;
	
	va_start(argptr, format);
	count = vsnprintf(buffer, sizeof(buffer), format, argptr);
	va_end(argptr);
	
	if(eof & FT_CR) {
		buffer[count++] = '\r';
	}
	if(eof & FT_LF) {
		buffer[count++] = '\n';
	}
	buffer[count++] = '\0';
	
	printf("send >> %s\n", buffer);
	// --
	write(fd, buffer, count);
	usleep ((7 + 25) * 100);	
	return count;
}


const char *device_serial = "MDMR112425408";
const char *state_gateway_str = R"({
	"api_version": "1.0", 
	"event_type": "gateway_state!", 
	"event_id": "02114da8-feae-46e3-8b00-a3f7ea8672df",
	"time_created": %ld
})";
const char *send_feedback_str = R"({
	"api_version": "1.0", 
	"event_type": "feedback!", 
	"event_id": "02114da8-feae-46e3-8b00-a3f7ea8672df",
	"time_created": %ld,
	"device_serial": "%s",
	"feedback_action_id": "FEEDBACK_POSITIVE"
})";
const char *send_display_str = R"({
	"api_version": "1.0",
	"event_type": "display!",
	"event_id": "02114da8-feae-46e3-8b00-a3f7ea8672df",
	"time_created": %ld,
	"time_validity_duration": 4000,
	"device_serial": "%s",
	"display_template_id": "PG3",
	"display_refresh_type": "DEFAULT",
	"display_fields": [
		{ "display_field_id": 1, "display_field_header": "Storage Unit", "display_field_text": "R15" },
		{ "display_field_id": 2, "display_field_header": "Item", "display_field_text": "Engine 12" },
		{ "display_field_id": 3, "display_field_header": "Quantity", "display_field_text": "10" } ]
})";


int main(int argc, char **argv) {
	pthread_t background;
	const char *portname = nullptr;
	int baudate = B115200;
	int eof = FT_LF;
	// signal(SIGINT, my_function);
	struct option longopts[] = {
		{ "help", no_argument, nullptr, 'h' },
		{ "eof",  optional_argument, nullptr, 'e' },
		{ "baud", optional_argument, nullptr, 'b' },
		{ "port", required_argument, nullptr, 'p' },
		{ 0 }
	};
	while(true) {
		char c = getopt_long(argc, argv, "heb:p:", longopts, 0);
		if(c == -1) {
			break;
		}
		switch(c) {
		case 'p':
			portname = strdup(optarg);
			break;
		case 'b':
			baudate = get_baudrate(optarg);
			break;
		case 'e':
			eof = get_flush_type(optarg);
			break;
		case 'h':
		case '?':
			help(argv[0]);
			return 0;
		}
	}
	if(portname == nullptr) {
		help(argv[0]);
		return -1;
	}
	printf(">> Connect: %s %d\n", portname, baudate);
	int fd = open(portname, O_RDWR | O_NOCTTY | O_NDELAY);
	if(fd < 0) {
		fprintf(stderr, "error %d opening %s: %s", errno, portname, strerror(errno));
		return -2;
	}
	set_interface_attribs (fd, baudate, 0);  // set speed to 115,200 bps, 8n1 (no parity)
	set_blocking (fd, 0);                // set no blocking
	
	int ret = pthread_create(&background, NULL, read_callback, (void *)&fd);
	set_idle_priority(background);
	// ret == 0
	printf("Waiting input ...\n");
	char buffer[1024];
	while(true) {
		fgets(buffer, sizeof(buffer), stdin); 
		// ADD EOF
		if(strncmp(buffer, "display", 7) == 0) {
			write_va(fd, FT_LF, send_display_str, get_timestamp(), device_serial);
		} else if(strncmp(buffer, "feedback", 8) == 0) {
			write_va(fd, FT_LF, send_feedback_str, get_timestamp(), device_serial);
		} else if(strncmp(buffer, "gateway", 7) == 0) {
			write_va(fd, FT_LF, state_gateway_str, get_timestamp());
		} else {
			printf("Undefined input ... %s\n", buffer);
		}
	}
	printf("Closing socket\n");
	close(fd);
	pthread_join(background, nullptr);
	printf("Closed socket\n");
	return 0;
}

