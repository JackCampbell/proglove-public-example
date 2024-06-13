package argex.io.pgexample;

import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;

import java.util.concurrent.Executors;
import java.util.logging.Logger;

import argex.io.pgexample.databinding.ScanActivityBinding;
import de.proglove.sdk.ConnectionStatus;
import de.proglove.sdk.IPgManager;
import de.proglove.sdk.IServiceOutput;
import de.proglove.sdk.PgManager;
import de.proglove.sdk.scanner.BarcodeScanResults;
import de.proglove.sdk.scanner.IScannerOutput;

public class ScanActivity extends AppCompatActivity implements IServiceOutput, IScannerOutput, View.OnClickListener {
	private static String TAG = ScanActivity.class.getSimpleName();
	private Logger logger = Logger.getLogger(TAG);
	private IPgManager manager = new PgManager(logger, Executors.newCachedThreadPool());
	private ScanActivityBinding binding;


	@Override
	protected void onCreate(@Nullable Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		binding = DataBindingUtil.setContentView(this, R.layout.scan_activity);
		binding.pairDevice.setOnClickListener(this);

		manager.subscribeToServiceEvents(this);
		manager.subscribeToScans(this);
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
		final String barcode = result.getBarcodeContent();
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				binding.barcodeText.setText(barcode);
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

	}
	public void pair_device() {
		if(!manager.isConnectedToService()) {
			showText("service is not connect");
			return;
		}
		// manager.isConnectedToScanner()
		if(manager.isConnectedToScanner()) {
			manager.disconnectScanner();
		} else {
			manager.startPairing();
		}
	}
	// IScannerOutput




	private void showText(String message) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(ScanActivity.this, message, Toast.LENGTH_SHORT).show();
			}
		});
	}

	@Override
	public void onClick(View view) {
		if(view.getId() == R.id.pair_device) {

		}
	}

	private void updateDevice() {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if(manager.isConnectedToScanner()) {
					binding.deviceStatus.setText("Connect");
				} else {
					binding.deviceStatus.setText("Disconnect");
				}
			}
		});
	}
}
