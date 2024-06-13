//
//  PGFirmwareUpdateManager.h
//  ConnectSDK
//
//  Copyright © 2020 proglove. All rights reserved.
//

/**
 @protocol PGFirmwareUpdateManagerDelegate
 
 The delegate protocol for the PGFirmwareUpdateManager. The delegate must adopt the PGFirmwareUpdateManagerDelegate protocol.
 The methods will provide the firmware update state information.
*/
@protocol PGFirmwareUpdateManagerDelegate <NSObject>

/**
 The firmware update has begun.
 */
- (void)didStartFirmwareUpdate;

/**
 The current update progress expressed in percentage.
 
 @param percentage The firmware update completed percentage.
 */
- (void)didChangeFirmwareUpdateProgress:(NSInteger)percentage;

/**
 The firmware update is successfully completed.
 */
- (void)didCompleteFirmwareUpdate;

/**
 The firmware update failed.
 
 @param error The error which occurred.
*/
- (void)didFailToUpdateFirmwareWithError:(NSError * _Nullable)error;

@end


/**
 @protocol PGFirmwareUpdateManager
 
 The protocol for the PGFirmwareUpdateManager.
*/
@protocol PGFirmwareUpdateManager <NSObject>

/**
 The firmware update manager delegate.
*/
@property(nullable) id<PGFirmwareUpdateManagerDelegate> delegate;

@end


