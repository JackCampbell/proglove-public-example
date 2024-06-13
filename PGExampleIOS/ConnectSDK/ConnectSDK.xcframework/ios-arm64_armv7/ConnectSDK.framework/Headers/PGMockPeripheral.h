//
//  PGMockPeripheral.h
//  ConnectSDK
//
//  Copyright © 2019 Workaround GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <ConnectSDK/PGPeripheral.h>

/**
 A mock peripheral for use in testing
 */
@interface PGMockPeripheral : PGPeripheral

/**
 `YES` if the peripheral is available for connection, `NO` otherwise. Set this property to control if the peripheral appears in the App
 */
@property(nonatomic, assign) BOOL available;

/**
 The advertisement data to use. A collection of keys and values
 */
@property(nonatomic, readonly, nonnull) NSDictionary <NSString *, id> *advertisementData;

/**
 Initialise with a given identifier

 @param identifier The identifier to initialise with
 @return The Mock peripheral instance
 */
- (nonnull instancetype)initWithIdentifier:(nonnull NSString *)identifier;

/**
 Advertise the Scanner with the given indicator, equivalent to scanning the pairing QR with the Scanner

 @param indicator The indicator to advertise with
 */
- (void)advertiseWithIndicator:(nonnull NSString *)indicator;

/**
 Set the battery level of the Mock

 @param batteryLevel The battery level
 */
- (void)setBatteryLevel:(uint8_t)batteryLevel;

/**
 Send a barcode to the central

 @param barcode The barcode string to send
 */
- (void)sendBarcode:(nonnull NSString *)barcode;

@end
