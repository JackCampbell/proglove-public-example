//
//  PGDeviceInformation.h
//  ConnectSDK
//
//  Created by Bozidar Jevic on 09/11/2020.
//  Copyright © 2020 proglove. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Model representing device information
*/
@interface PGDeviceInformation : NSObject

/**
 Serial number.
 */
@property (nonatomic, readonly, nullable) NSString *serialNumber;

/**
 Firmware revision.
 */
@property (nonatomic, readonly, nullable) NSString *firmwareRevision;

/**
 PGDeviceInformation cannot be created directly. Instead, obtain a device information object through `PGPeripheral`

 @return nil
 */
- (nonnull instancetype)init NS_UNAVAILABLE;


@end
