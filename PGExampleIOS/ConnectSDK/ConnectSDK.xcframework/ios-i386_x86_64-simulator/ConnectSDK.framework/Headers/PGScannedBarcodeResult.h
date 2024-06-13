//
//  PGScannedBarcodeData.h
//  ConnectSDK
//
//  Copyright © 2020 proglove. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
*  @class PGScannedBarcodeResult
*
*  @discussion Scanned barcode data.
*
*/@interface PGScannedBarcodeResult: NSObject

/**
 The scanned barcode string.
*/
@property(nonatomic, readonly, nonnull) NSString * barcodeContent;
/**
 The scanned barcode symbology, if available.
*/
@property(nonatomic, readonly, nullable) NSString * barcodeSymbology;

/**
 Scanned barcode data cannot be created directly. Instead, obtain a data object through `PGPeripheral`
 @return nil
*/
- (nonnull instancetype)init NS_UNAVAILABLE;
@end
