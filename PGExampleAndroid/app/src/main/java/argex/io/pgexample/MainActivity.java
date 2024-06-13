package argex.io.pgexample;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;

import java.util.concurrent.Executors;
import java.util.logging.Logger;

import argex.io.pgexample.databinding.MainActivityBinding;
import de.proglove.sdk.ConnectionStatus;
import de.proglove.sdk.IPgManager;
import de.proglove.sdk.IServiceOutput;
import de.proglove.sdk.PgError;
import de.proglove.sdk.PgManager;
import de.proglove.sdk.button.ButtonPress;
import de.proglove.sdk.button.IButtonOutput;
import de.proglove.sdk.commands.PgCommand;
import de.proglove.sdk.commands.PgCommandParams;
import de.proglove.sdk.configuration.IPgGetConfigProfilesCallback;
import de.proglove.sdk.configuration.PgConfigProfile;
import de.proglove.sdk.display.IPgSetScreenCallback;
import de.proglove.sdk.display.PgScreenData;
import de.proglove.sdk.display.PgTemplateField;
import de.proglove.sdk.display.RefreshType;
import de.proglove.sdk.scanner.BarcodeScanResults;
import de.proglove.sdk.scanner.DeviceVisibilityInfo;
import de.proglove.sdk.scanner.IPgDeviceVisibilityCallback;
import de.proglove.sdk.scanner.IPgFeedbackCallback;
import de.proglove.sdk.scanner.IScannerOutput;
import de.proglove.sdk.scanner.PgPredefinedFeedback;

@SuppressLint({"DefaultLocale", "SetTextI18n"})
public class MainActivity extends AppCompatActivity implements IServiceOutput, IScannerOutput, IButtonOutput, View.OnClickListener {
	private static final String TAG = MainActivity.class.getSimpleName();
	private final Logger logger = Logger.getLogger(TAG);
	private final IPgManager manager = new PgManager(logger, Executors.newCachedThreadPool());
	private MainActivityBinding binding;


	@Override
	protected void onCreate(@Nullable Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		binding = DataBindingUtil.setContentView(this, R.layout.main_activity);
		binding.pairDevice.setOnClickListener(this);
		binding.triggerDevice.setOnClickListener(this);
		binding.deviceDisplay.setOnClickListener(this);
		binding.visibility.setOnClickListener(this);
		binding.profile.setOnClickListener(this);
		binding.orientation.setOnClickListener(this);

		manager.subscribeToServiceEvents(this);
		manager.subscribeToScans(this);
		manager.subscribeToButtonPresses(this);
	}

	@Override
	protected void onResume() {
		super.onResume();
		final Context context = getApplicationContext();
		manager.ensureConnectionToService(context);
	}

	@Override
	protected void onDestroy() {
		manager.unsubscribeFromServiceEvents(this);
		manager.unsubscribeFromScans(this);
		manager.unsubscribeFromButtonPresses(this);
		super.onDestroy();
	}
	// IServiceOutput
	@Override
	public void onServiceConnected() {
		showText("connect");
	}

	@Override
	public void onServiceDisconnected() {
		showText("disconnect");
	}
	// IServiceOutput



	// IScannerOutput
	@Override
	public void onBarcodeScanned(@NonNull BarcodeScanResults result) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				binding.barcodeText.setText(result.getBarcodeContent());
				binding.symbology.setText(result.getSymbology());
			}
		});
	}

	@Override
	public void onScannerConnected() {
		showText("connect-device");
		updateDevice();
	}

	@Override
	public void onScannerDisconnected() {
		showText("disconnect-device");
		updateDevice();
	}

	@Override
	public void onScannerStateChanged(@NonNull ConnectionStatus connectionStatus) {
		updateDevice();
	}
	public void pair_device() {
		if(!manager.isConnectedToService()) {
			showText("service is not connect");
			return;
		}
		if(manager.isConnectedToScanner()) {
			manager.disconnectScanner();
		} else {
			manager.startPairing();
			// manager.startPairingFromPinnedActivity(this);
		}
	}
	private void updateDevice() {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if(manager.isConnectedToScanner()) {
					binding.deviceStatus.setText("Connect");
					binding.pairDevice.setText("Unpair Device");
				} else {
					binding.deviceStatus.setText("Disconnect");
					binding.pairDevice.setText("Pair Device");
				}
			}
		});
	}
	// IScannerOutput


	// TRIGGER
	private void trigger_device() {
		PgCommandParams params = new PgCommandParams(true);
		PgCommand<PgPredefinedFeedback> feedback = PgPredefinedFeedback.ERROR.toCommand(params);
		manager.triggerFeedback(feedback, new IPgFeedbackCallback() {
			@Override
			public void onSuccess() {
				MainActivity.this.showText("Send trigger");
			}

			@Override
			public void onError(@NonNull PgError pgError) {
				MainActivity.this.showText("fail trigger");
			}
		});
	}
	// TRIGGER

	// DISPLAY
	private void display_device() {
		if(!manager.isConnectedToScanner() || !manager.isConnectedToDisplay()) {
			showText("no display !!!");
			return;
		}

		PgTemplateField[] data = {
				new PgTemplateField(1, "Header1", "Content1"),
				new PgTemplateField(2, "Header2", "Content2"),
				new PgTemplateField(3, "Header3", "Content3")
		};
		PgScreenData display = new PgScreenData("PG3", data, RefreshType.DEFAULT);
		manager.setScreen(display, new IPgSetScreenCallback() {
			@Override
			public void onSuccess() {
				MainActivity.this.showText("Send display");
			}
			@Override
			public void onError(@NonNull PgError pgError) {
				MainActivity.this.showText("fail display");
			}
		});
	}
	// DISPLAY

	// IButtonOutput
	@Override
	public void onButtonPressed(@NonNull ButtonPress buttonPress) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(MainActivity.this, String.format("Button: %d", buttonPress.getId()), Toast.LENGTH_SHORT).show();
			}
		});
	}


	// VISIBILITY
	private void updateVisibility() {
		manager.obtainDeviceVisibilityInfo(new IPgDeviceVisibilityCallback() {
			@Override
			public void onDeviceVisibilityInfoObtained(@NonNull DeviceVisibilityInfo deviceVisibilityInfo) {
				StringBuilder builder = new StringBuilder();
				builder.append("Serial: " + deviceVisibilityInfo.getSerialNumber() + "\n");
				builder.append("Firmware: " + deviceVisibilityInfo.getFirmwareRevision() + "\n");
				builder.append("Battery: " + deviceVisibilityInfo.getBatteryLevel() + "\n");
				builder.append("BCE: " + deviceVisibilityInfo.getBceRevision() + "\n");
				builder.append("Model: " + deviceVisibilityInfo.getModelNumber() + "\n");
				builder.append("Manufacture: " + deviceVisibilityInfo.getManufacturer() + "\n");
				builder.append("App: " + deviceVisibilityInfo.getAppVersion() + "\n");
				showAlert(builder.toString(), "Info");
			}

			@Override
			public void onError(@NonNull PgError pgError) {
				showAlert(pgError.toString(), "Error");
			}
		});
	}
	// PROFILE
	private void updateProfile() {
		manager.getConfigProfiles(new IPgGetConfigProfilesCallback() {
			@Override
			public void onConfigProfilesReceived(@NonNull PgConfigProfile[] pgConfigProfiles) {
				StringBuilder builder = new StringBuilder();
				for(PgConfigProfile profile : pgConfigProfiles) {
					builder.append("ID: " + profile.getProfileId() + "-Act:" + profile.isActive());
				}
				showAlert(builder.toString(), "Profile");
			}

			@Override
			public void onError(@NonNull PgError pgError) {
				showAlert(pgError.toString(), "Error");
			}
		});
	}

	// ORIENTATION
	private void orientationConfig() {
		PgError error = manager.showPickDisplayOrientationDialog(this);
		if(error != null) {
			showText(error.toString());
		}
	}




	// STUFF
	private void showText(String message) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(MainActivity.this, message, Toast.LENGTH_SHORT).show();
			}
		});
	}

	private void showAlert(final String message, final String title) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);

				builder.setTitle(title);
				builder.setMessage(message);
				builder.create().show();
			}
		});
	}

	@Override
	public void onClick(View view) {
		if(view.getId() == R.id.pair_device) {
			pair_device();
		} else if(view.getId() == R.id.trigger_device) {
			trigger_device();
		} else if(view.getId() == R.id.device_display) {
			display_device();
		} else if(view.getId() == R.id.visibility) {
			updateVisibility();
		} else if(view.getId() == R.id.profile) {
			updateProfile();
		} else if(view.getId() == R.id.orientation) {
			orientationConfig();
		}
	}
}
