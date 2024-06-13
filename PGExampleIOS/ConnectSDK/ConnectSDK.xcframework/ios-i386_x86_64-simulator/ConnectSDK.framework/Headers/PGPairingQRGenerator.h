//
//  PGPairingQRGenerator.h
//  ConnectSDK
//
//  Copyright © 2019 Workaround GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 The PG Pairing QR error correction level

 - PGPairingQRGeneratorErrorCorrectionLevelL: Level L, 7% error correction capability
 - PGPairingQRGeneratorErrorCorrectionLevelM: Level M, 15% error correction capability
 - PGPairingQRGeneratorErrorCorrectionLevelQ: Level Q, 25% error correction capability
 - PGPairingQRGeneratorErrorCorrectionLevelH: Level H, 30% error correction capability
 */
typedef NS_ENUM(NSUInteger, PGPairingQRGeneratorErrorCorrectionLevel) {
	/// Level L, 7% error correction capability
	PGPairingQRGeneratorErrorCorrectionLevelL,
	/// Level M, 15% error correction capability
	PGPairingQRGeneratorErrorCorrectionLevelM,
	/// Level Q, 25% error correction capability
	PGPairingQRGeneratorErrorCorrectionLevelQ,
	/// Level H, 30% error correction capability
	PGPairingQRGeneratorErrorCorrectionLevelH
};

/**
 Generates a QR code with the given identifier and error correction level at the given size

 @param indicator The indicator to embed in the QR code
 @param errorCorrectionLevel The error correction level
 @param size The size of the image to generate
 @param scale The destination screen points to pixels scale
 @return The generated QR code
 */
UIImage *_Nonnull PGPairingQRGenerate(NSData *_Nonnull indicator, PGPairingQRGeneratorErrorCorrectionLevel errorCorrectionLevel, CGSize size, CGFloat scale);
