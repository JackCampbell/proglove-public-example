//
//  ConnectSDK.h
//  ConnectSDK
//
//  Copyright © 2019 Workaround GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 Project version number for ConnectSDK.
 */
FOUNDATION_EXPORT double ConnectSDKVersionNumber;

/**
 Project version string for ConnectSDK.
 */
FOUNDATION_EXPORT const unsigned char ConnectSDKVersionString[];

/**
 Project version string for ConnectSDK.
 */
extern const unsigned char * ConnectSDKVersionStringPtr;

/**
 Project version string for ConnectSDK.
 */
extern NSString * ConnectSDKVersionStringObject;

#import <ConnectSDK/PGCentralManager.h>
#import <ConnectSDK/PGCentralManager(Mock).h>
#import <ConnectSDK/PGPeripheral.h>
#import <ConnectSDK/PGPairingQRGenerator.h>
#import <ConnectSDK/PGMockPeripheral.h>
#import <ConnectSDK/PGError.h>
#import <ConnectSDK/PGLogging.h>
#import <ConnectSDK/PGScannedBarcodeResult.h>
#import <ConnectSDK/PGCommand.h>
#import <ConnectSDK/PGCommandParams.h>
#import <ConnectSDK/PGFirmwareUpdateManager.h>
#import <ConnectSDK/PGDeviceInformationRequest.h>
#import <ConnectSDK/PGDeviceInformation.h>
#import <ConnectSDK/PGConfigurationProfile.h>
#import <ConnectSDK/PGManager.h>
#import <ConnectSDK/PGScreenData.h>
#import <ConnectSDK/PGTemplateField.h>
#import <ConnectSDK/PGConfigurationManagerProtocol.h>
#import <ConnectSDK/PGDisplayManagerProtocol.h>
#import <ConnectSDK/PGSetDisplayOrientationRequest.h>
#import <ConnectSDK/PGFeedbackManagerProtocol.h>
#import <ConnectSDK/PGFeedbackRequest.h>
