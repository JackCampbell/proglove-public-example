//
//  PGCentralManager.h
//  ConnectSDK
//
//  Copyright © 2019 Workaround GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ConnectSDK/PGManager.h>
#import <ConnectSDK/PGPeripheral.h>
#import <ConnectSDK/PGPairingQRGenerator.h>
#import <UIKit/UIKit.h>
#import <ConnectSDK/PGFirmwareUpdateManager.h>
#import <ConnectSDK/PGCommand.h>
#import <ConnectSDK/PGConfigurationProfile.h>
#import <ConnectSDK/PGConfigurationManagerProtocol.h>
#import <ConnectSDK/PGDisplayManagerProtocol.h>
#import <ConnectSDK/PGFeedbackManagerProtocol.h>


@class PGCentralManager;

/**
 *  @protocol PGCentralManagerDelegate
 *
 *  @discussion The delegate of a {@link PGCentralManager} object must adopt the <code>PGCentralManagerDelegate</code> protocol. The optional methods allow for the discovery and connection of peripherals.
 *
 */
@protocol PGCentralManagerDelegate <PGManagerDelegate>

@required

/**
 The central is searching for a peripheral scanner with an indicator.
 
 @param centralManager The PG central
 @param indicator The indicator the central is searching for.
 */
- (void)centralManager:(nonnull PGCentralManager *)centralManager didStartSearchingForIndicator:(nullable NSString *)indicator;

/**
 Now connecting to a Scanner
 
 @param centralManager The PG central
 @param scanner The scanner which is now connecting
 */
- (void)centralManager:(nonnull PGCentralManager *)centralManager connectingToScanner:(nonnull PGPeripheral *)scanner;

/**
 Scanner is connected but still not ready for use.
 
 @param centralManager The PG central.
 @param scanner The scanner which is now connected.
 */
- (void)centralManager:(nonnull PGCentralManager *)centralManager scannerDidConnect:(nonnull PGPeripheral *)scanner;

/**
 The Scanner became ready

 @param centralManager The PG central
 @param scanner The scanner which became ready
 */
- (void)centralManager:(nonnull PGCentralManager *)centralManager scannerDidBecomeReady:(nonnull PGPeripheral *)scanner;

/**
 The central failed to connect to the Scanner.

 @param centralManager The central
 @param scanner The Scanner
 @param error The error which occurred
 */
- (void)centralManager:(nonnull PGCentralManager *)centralManager didFailToConnectToScanner:(nonnull PGPeripheral *)scanner error:(nullable NSError *)error;

/**
 The central disconnected from the Scanner.

 @param centralManager The central
 @param scanner The Scanner
 @param error The error which occurred, if any
 */
- (void)centralManager:(nonnull PGCentralManager *)centralManager didDisconnectFromScanner:(nonnull PGPeripheral *)scanner error:(nullable NSError *)error;

/**
 The central manager failed to initiate Scanner connection.

 @param centralManager The central
 @param error The error which occurred, if any
*/
- (void)centralManager:(nonnull PGCentralManager *)centralManager didFailToInitiateConnection: (nullable NSError *)error;

/**
 The central manager did lost connection to Scanner and trying to reconnect.

 @param centralManager The central
 @param scanner The Scanner
*/
- (void)centralManager:(nonnull PGCentralManager *)centralManager didLostConnectionAndReconnectingToScanner:(nonnull PGPeripheral *)scanner;

@end

/**
 *  @class PGCentralManager
 *
 *  @discussion Entry point to the central role. Commands should only be issued when its state is <code>PGManagerStatePoweredOn</code>.
 *
 */
@interface PGCentralManager : PGManager

/**
 The central delegate
 */
@property(nonatomic, weak, nullable) id <PGCentralManagerDelegate> delegate;

/**
 The indicator the central is scanning for. This is a random string which is included in the QR code generated
 */
@property(nonatomic, readonly, nullable) NSString *scanningForIndicator;

/**
 A Boolean indicating whether the search for a scanner is currently in progress. The value of this property is set to YES when a search is initiated and remains in that state until the search results (or an appropriate error) are delivered, at which time the property is set to NO.
 */
@property(nonatomic, assign, readonly) BOOL isSearching;

/**
 When set to YES (true), continuousSearchEnabled option will enable continuous discovery of scanners, meaning that central manager will continue to search for scanners even when connection is established.
 Common use case is with fixed connection barcode, by scanning connection barcode, the current connection will be dropped and new one established.
 This option does not affect current central state hence will not start or stop searching process.
 When set to NO (false) the searching process will be terminated when connection is established.
 Default value is NO (false).
 */
@property(nonatomic, readwrite) BOOL continuousSearchEnabled;

/**
 The connected scanner, if one is connected
 */
@property(nonatomic, readonly, nullable) PGPeripheral *connectedScanner;

/**
 The firmware update manager.
 */
@property(nonatomic, readonly, nullable) id<PGFirmwareUpdateManager> firmwareUpdateManager;

/**
The configuration manager.
*/
@property(nonatomic, readonly, nullable) id<PGConfigurationManager> configurationManager;

/**
 The display manager. Use this manager to configure screen settings.
 */
@property(nonatomic, readonly, nullable) id<PGDisplayManager> displayManager;

/**
 The feedback manager. Use this manager to play feedback sequences on a connected device.
 */
@property(nonatomic, readonly, nullable) id<PGFeedbackManagerProtocol> feedbackManager;

#if TARGET_OS_IPHONE

/**
 Init the central manager with a delegate and optionally enable restoration

 @param delegate The delegate
 @param restoration A boolean value, `YES` if central manager restoration should be supported (restores the central manager from the previous App run)
 @return The central manager
 */
- (nonnull instancetype)initWithDelegate:(nonnull id<PGCentralManagerDelegate>)delegate enableRestoration:(BOOL)restoration;
#else
/**
 Init the central manager with a delegate
 
 @param delegate The delegate
 @return The central manager
 */
- (nonnull instancetype)initWithDelegate:(nonnull id<PGCentralManagerDelegate>)delegate;
#endif

/**
 This method generates an identifier which is embedded in a QR code for the Scanner to Scan, which the Scanner will advertise with. The central begins scanning for a Scanner advertising the generated identifier, and on discovering will connect to the Scanner. After Scanner interrogation, the scanner will become ready and `-centralManager:scannerDidBecomeReady:` will be called. This method is a convenience method which calls `-initiateScannerConnectionWithQRCorrectionLevel:imageSize:scale` with correction level Q (appropriate for dirty environments such as a warehouse) and the scale factor of the main screen
 
 @param size The image size
 @return The generated QR code
 */
- (nonnull UIImage *)initiateScannerConnectionWithImageSize:(CGSize)size;

/**
 This method generates an identifier which is embedded in a QR code for the Scanner to Scan, which the Scanner will advertise with. The central begins scanning for a Scanner advertising the generated identifier, and on discovering will connect to the Scanner. After Scanner interrogation, the scanner will become ready and `-centralManager:scannerDidBecomeReady:` will be called

 @param level The QR code correction level. 
 @param size The image size
 @param scale The destination screen points to pixels scale
 @return The generated QR code
 */
- (nonnull UIImage *)initiateScannerConnectionWithQRCorrectionLevel:(PGPairingQRGeneratorErrorCorrectionLevel)level imageSize:(CGSize)size scale:(CGFloat)scale;

/**
 Convenience method for generating connection barcode image with provided indicator (advertising name) embedded in it.
 
 @param indicator The advertising name that will be embedded into connection barcode.
 @param correctionLevel The connection  barcode correction level.
 @param size The image size.
 @param scale The destination screen points to pixels scale.
 */
- (nonnull UIImage *)generateScannerConnectionBarcodeWithIndicator:(nonnull NSString *)indicator correctionLevel:(PGPairingQRGeneratorErrorCorrectionLevel)correctionLevel imageSize:(CGSize)size scale:(CGFloat)scale;

/**
 Connect to a scanner using a given indicator. Previous connection will be canceled.

 @param indicator The indicator to use
 */
- (void)connectToScannerWithIndicator:(nonnull NSString *)indicator;

/**
 Use this method to cancel the established connection with Scanner.
 
 @param scanner A connected Scanner
 */
- (void)cancelScannerConnection:(nonnull PGPeripheral *)scanner;

/**
 Use this method to stop scanning process after initiateScannerConnectionWithImageSize is invoked and before pairing QR code is scanned.
 If connection with Scanner is established use cancelScannerConnection: to cancel the connection.
 */
- (void)stopScan;

@end

