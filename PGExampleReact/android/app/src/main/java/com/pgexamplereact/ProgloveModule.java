package com.pgexamplereact;

import android.content.Context;
import android.util.Log;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.LifecycleEventListener;
import java.util.Map;
import java.util.HashMap;
import java.util.concurrent.Executors;
import java.util.logging.Logger;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.UiThreadUtil;
import com.facebook.react.modules.core.DeviceEventManagerModule;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.Arguments;

import de.proglove.sdk.ConnectionStatus;
import de.proglove.sdk.IPgManager;
import de.proglove.sdk.IServiceOutput;
import de.proglove.sdk.PgError;
import de.proglove.sdk.PgManager;
import de.proglove.sdk.button.ButtonPress;
import de.proglove.sdk.button.IButtonOutput;
import de.proglove.sdk.commands.PgCommand;
import de.proglove.sdk.commands.PgCommandParams;
import de.proglove.sdk.display.IPgSetScreenCallback;
import de.proglove.sdk.display.PgScreenData;
import de.proglove.sdk.display.PgTemplateField;
import de.proglove.sdk.display.RefreshType;
import de.proglove.sdk.scanner.BarcodeScanResults;
import de.proglove.sdk.scanner.IPgFeedbackCallback;
import de.proglove.sdk.scanner.IPgScannerConfigCallback;
import de.proglove.sdk.scanner.IScannerOutput;
import de.proglove.sdk.scanner.PgPredefinedFeedback;
import de.proglove.sdk.scanner.PgScannerConfig;


class ProgloveModule extends ReactContextBaseJavaModule implements IServiceOutput, IScannerOutput, IButtonOutput {
	private static final String TAG = ProgloveModule.class.getSimpleName();
	private static final int FEEDBACK_SUCCESS = 0;
	private static final int FEEDBACK_ERROR = 1;
	private static final int FEEDBACK_WARNING = 2;
	private static final int ORIENTATION_UNSET = 0;
	private static final int ORIENTATION_NORTH = 1;
	private static final int ORIENTATION_EAST = 2;
	private static final int ORIENTATION_SOUTH = 3;
	private static final int ORIENTATION_WEST = 4;
	// private static final int ORIENTATION_NO
	private ReactApplicationContext context;
	private final Logger logger = Logger.getLogger(TAG);
	private IPgManager manager = null;

	ProgloveModule(ReactApplicationContext context) {
		super(context);
		this.context = context;
		// context.addLifecycleEventListener(this);
	}

	private void sendEvent(String eventName, @Nullable WritableMap params) {
		UiThreadUtil.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				context.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class).emit(eventName, params);
			}
		});
	}

	@NonNull
	@Override
	public String getName() {
		return "ProgloveModule";
	}

	@Nullable
	@Override
	public Map<String, Object> getConstants() {
		final Map<String, Object> constants = new HashMap<>();
		constants.put("FEEDBACK_SUCCESS", FEEDBACK_SUCCESS);
		constants.put("FEEDBACK_ERROR", FEEDBACK_ERROR);
		constants.put("FEEDBACK_WARNING", FEEDBACK_WARNING);
		constants.put("ORIENTATION_UNSET", ORIENTATION_UNSET);
		constants.put("ORIENTATION_NORTH", ORIENTATION_NORTH);
		constants.put("ORIENTATION_EAST", ORIENTATION_EAST);
		constants.put("ORIENTATION_SOUTH", ORIENTATION_SOUTH);
		constants.put("ORIENTATION_WEST", ORIENTATION_WEST);
		return constants;
	}

	@ReactMethod
	public void addListener(String eventName) {
		Log.w(TAG, "register event " + eventName);
	}
	@ReactMethod
	public void removeListeners(Integer count) {
		Log.w(TAG, "register increment" + count);
	}

	@Override
	public void onServiceConnected() {
		// PASS
	}

	@Override
	public void onServiceDisconnected() {
		// PASS
	}

	@Override
	public void onButtonPressed(@NonNull ButtonPress buttonPress) {
		WritableMap map = Arguments.createMap();
		map.putInt("button", buttonPress.getId());
		sendEvent("impulse", map);
	}

	@Override
	public void onBarcodeScanned(@NonNull BarcodeScanResults barcodeScanResults) {
		WritableMap map = Arguments.createMap();
		map.putString("content", barcodeScanResults.getBarcodeContent());
		map.putString("symbol", barcodeScanResults.getSymbology());
		sendEvent("barcode", map);
	}

	@Override
	public void onScannerConnected() {
		WritableMap map = Arguments.createMap();
		map.putBoolean("state", true);
		sendEvent("pair", map);
	}

	@Override
	public void onScannerDisconnected() {
		WritableMap map = Arguments.createMap();
		map.putBoolean("state", false);
		sendEvent("pair", map);
	}

	@Override
	public void onScannerStateChanged(@NonNull ConnectionStatus connectionStatus) {
		// PASS
	}


	@ReactMethod
	public void bindProglove() {
		manager = new PgManager(logger, Executors.newCachedThreadPool());
		manager.subscribeToServiceEvents(this);
		manager.subscribeToScans(this);
		manager.subscribeToButtonPresses(this);
		manager.ensureConnectionToService(context);
	}

	@ReactMethod
	public void unbindProglove() {
		if(manager == null) {
			return;
		}
		manager.unsubscribeFromButtonPresses(this);
		manager.unsubscribeFromScans(this);
		manager.unsubscribeFromServiceEvents(this);
	}

	@ReactMethod
	public void isConnected(Promise promise) {
		if(!manager.isConnectedToService()) {
			promise.reject(new Exception("service is not conncted"));
			return;
		}
		if(manager.isConnectedToScanner()) {
			promise.resolve(true);
		} else {
			promise.resolve(false);
		}
	}

	@ReactMethod
	public void pair(Promise promise) {
		if(!manager.isConnectedToService()) {
			promise.reject(new Exception("service is not conncted"));
			return;
		}
		if(manager.isConnectedToScanner()) {
			promise.resolve(false);
			return;
		}
		manager.startPairing();
		promise.resolve(true);
	}

	@ReactMethod
	public void unpair(Promise promise) {
		if(!manager.isConnectedToService()) {
			promise.reject(new Exception("service is not conncted"));
			return;
		}
		if(!manager.isConnectedToScanner()) {
			promise.resolve(false);
			return;
		}
		manager.disconnectScanner();
		promise.resolve(true);
	}

	@ReactMethod
	public void feedback(@NonNull Integer type, Promise promise) {
		if(!manager.isConnectedToService()) {
			promise.reject(new Exception("service is not conncted"));
			return;
		}
		PgCommandParams params = new PgCommandParams(true);
		PgCommand<PgPredefinedFeedback> feedback;
		if(type == FEEDBACK_SUCCESS) {
			feedback = PgPredefinedFeedback.SUCCESS.toCommand(params);
		} else if(type == FEEDBACK_ERROR) {
			feedback = PgPredefinedFeedback.ERROR.toCommand(params);
		} else {
			feedback = PgPredefinedFeedback.SPECIAL_1.toCommand(params);
		}
		manager.triggerFeedback(feedback, new IPgFeedbackCallback() {
			@Override
			public void onSuccess() {
				promise.resolve(true);
			}
			@Override
			public void onError(@NonNull PgError pgError) {
				promise.resolve(false);
			}
		});
	}


	@ReactMethod
	public void display(@NonNull String template, @NonNull ReadableArray fields, Promise promise) {
		if(!manager.isConnectedToService()) {
			promise.reject(new Exception("service is not conncted"));
			return;
		}
		if(!manager.isConnectedToScanner()) {
			promise.reject(new Exception("scanner is not conncted"));
			return;
		}
		int size = fields.size();
		PgTemplateField[] data = new PgTemplateField[size];
		for(int index = 0; index < size; index++) {
			ReadableMap map = fields.getMap(index);
			String header = map.getString("header");
			if(header == null) {
				header = "";
			}
			String content = map.getString("content");
			if(content == null) {
				content = "";
			}
			data[index] = new PgTemplateField(index + 1, header, content);
		}
		PgScreenData display = new PgScreenData(template, data, RefreshType.DEFAULT);
		PgCommandParams params = new PgCommandParams(true);
		manager.setScreen(display.toCommand(params), new IPgSetScreenCallback() {
			@Override
			public void onSuccess() {
				promise.resolve(true);
			}
			@Override
			public void onError(@NonNull PgError pgError) {
				promise.resolve(false);
			}
		});
	}

	@ReactMethod
	public void orientation(@NonNull Integer type, Promise promise) {
		PgError error = manager.showPickDisplayOrientationDialog(context);
		if(error == null) {
			promise.resolve(true);
		} else {
			promise.resolve(false);
		}
	}
}

