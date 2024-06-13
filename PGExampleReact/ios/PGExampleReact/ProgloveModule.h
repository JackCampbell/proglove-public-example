#import <React/RCTBridgeModule.h>
#import <React/RCTEventEmitter.h>
#import <React/RCTLog.h>
#import <ConnectSDK/ConnectSDK.h>
#import <ConnectSDK/PGFeedbackRequest.h>
#import <ConnectSDK/PGPeripheral.h>

@interface RCTProgloveModule : RCTEventEmitter<RCTBridgeModule, PGPeripheralDelegate, PGCentralManagerDelegate, PGLoggingDelegate>
@end
