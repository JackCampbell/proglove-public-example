//
//  PGPeripheral.h
//  ConnectSDK
//
//  Copyright © 2020 proglove. All rights reserved.
//

#import <ConnectSDK/PGScannedBarcodeResult.h>
#import <ConnectSDK/PGConfigurationProfile.h>
#import <ConnectSDK/PGCommand.h>
#import <ConnectSDK/PGDeviceInformation.h>
#import <ConnectSDK/PGDeviceInformationRequest.h>

@protocol PGPeripheralDelegate;

/**
 Values representing the current connection state of the peripheral
 
 - PGPeripheralStateDisconnected: The peripheral is currently not connected to the central manager.
 - PGPeripheralStateConnecting: The peripheral is currently in the process of connecting to the central manager.
 - PGPeripheralStateDisconnecting: The peripheral is currently in the process of disconnecting from the central manager.
 - PGPeripheralStateSystemConnected: The peripheral is currently connected to the system, but not the App's central manager.
 - PGPeripheralStateDiscovering: The peripheral is currently being interrogated by the central manager
 - PGPeripheralStateReady: The peripheral is ready to be used
 */
typedef NS_ENUM(NSInteger, PGPeripheralState) {
    /// The peripheral is currently not connected to the central manager.
    PGPeripheralStateDisconnected,
    /// The peripheral is currently in the process of connecting to the central manager.
    PGPeripheralStateDisconnecting,
    /// The peripheral is currently in the process of disconnecting from the central manager.
    PGPeripheralStateConnecting,
    /// The peripheral is currently connected to the system, but not the App's central manager.
    PGPeripheralStateSystemConnected,
    /// The peripheral is currently being interrogated by the central manager
    PGPeripheralStateDiscovering,
    /// The peripheral is ready to be used
    PGPeripheralStateReady
};

/**
 Represents a PG Bluetooth barcode scanner peripheral
 */
@interface PGPeripheral : NSObject

/**
 Peripherals cannot be created directly. Instead, obtain a peripheral object through `PGCentral`

 @return nil
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 The delegate for PG Peripheral events
 */
@property(nonatomic, weak, nullable) id<PGPeripheralDelegate> delegate;

/**
 A unique identifier for this peripheral
 */
@property(nonatomic, readonly, nonnull) NSString *identifier;

/**
 The current connection state of the peripheral
 */
@property(nonatomic, readonly) PGPeripheralState state;

/**
 The name of the PG peripheral
 */
@property(nonatomic, readonly, nonnull) NSString *name;

/**
 The current battery level of the Scanner
 */
@property(nonatomic, readonly) uint8_t batteryLevel;

/**
 Use this method to retrieve a connected device information.

 @param deviceInfoCommand The PGCommand with a device information request.
 @param completionHandler The completion handler containing the device information if available. In case request failed, error will be returned.
 */
- (void)requestDeviceInformationWithDeviceInfoCommand:(nonnull PGCommand<PGDeviceInformationRequest *> *)deviceInfoCommand completionHandler:(void (^_Nonnull)(PGDeviceInformation * _Nullable deviceInformation, NSError * _Nullable error))completionHandler;

@end

/**
 The delegate protocol for the PG peripheral
 */
@protocol PGPeripheralDelegate <NSObject>

@optional
/**
 The PG peripheral updated its name

 @param peripheral The scanner peripheral
 */
- (void)peripheralDidUpdateName:(nonnull PGPeripheral *)peripheral;

/**
 The PG peripheral updated its connection state

 @param peripheral The PG peripheral
 */
- (void)peripheralDidUpdateState:(nonnull PGPeripheral *)peripheral;

/**
 Call this method in order to retrieve the RSSI of the peripheral while connected to the central manager.
 The peripheral calls the peripheral:didReadRSSI:error: method of its delegate object, which includes the RSSI value as a parameter.
 */
- (void)readRSSI;

/**
 The RSSI of the device was read

 @param peripheral The PG peripheral
 @param RSSI The new RSSI
 */
- (void)peripheral:(nonnull PGPeripheral *)peripheral didReadRSSI:(nonnull NSNumber *)RSSI;

/**
 The PG peripheral scanned a barcode

 @param peripheral The PG peripheral
 @param result The scanned data
 */
- (void)peripheral:(nonnull PGPeripheral *)peripheral didScanBarcodeWithResult:(nonnull PGScannedBarcodeResult *)result;

/**
 The PG peripheral encountered an error when scanning a barcode

 @param peripheral The Scanner peripheral
 @param error The error encountered, in the `PGPeripheralErrorDomain` domain
 */
- (void)peripheral:(nonnull PGPeripheral *)peripheral errorScanningBarcode:(nonnull NSError *)error;

/**
 The Scanner peripheral updated its battery level

 @param peripheral The Scanner peripheral
 */
- (void)peripheralDidUpdateBatteryLevel:(nonnull PGPeripheral *)peripheral;

@end
