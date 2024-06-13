//
//  PGDisplayManager.h
//  ConnectSDK
//
//  Copyright © 2021 proglove. All rights reserved.
//
#import <ConnectSDK/PGCommand.h>
#import <ConnectSDK/PGScreenData.h>
#import <ConnectSDK/PGSetDisplayOrientationRequest.h>

/**
 Protocol contains all the display configuration related methods.
 */
NS_SWIFT_NAME(PGDisplayManager)
@protocol PGDisplayManager <NSObject>

/**
 Use this method to set a screen data to a connected device.
 
 @param screenDataCommand The PGCommand with a all the screen data.
 @param completionHandler The completion handler returning an error in case request failed.
 */
- (void)setScreen:(nonnull PGCommand<PGScreenData *> *)screenDataCommand completionHandler:(void (^_Nonnull)(NSError * _Nullable error))completionHandler;
 
/**
 This method can be used to change the orientation on a connected device.
 
 @param orientationCommand The PG command containing PGSetDisplayOrientationRequest with a concrete orientation.
 @param completionHandler The completion handler returning an error in case the  request failed.
 */
- (void)setDisplayOrientation:(nonnull PGCommand<PGSetDisplayOrientationRequest *> *)orientationCommand completionHandler:(void (^_Nonnull)(NSError * _Nullable error))completionHandler;
@end
