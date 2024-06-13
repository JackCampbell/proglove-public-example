//
//  PGSetDisplayOrientationRequest.h
//  ConnectSDK
//
//  Copyright © 2021 proglove. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Definition of the valid display orientations.
 */
typedef NS_ENUM(NSInteger, PGOrientation) {
    // Invalid e.g. unset orientation
    PGInvalid = 0,
    // Default orientation.
    PGNorth = 1,
    // Orientation rotated from NORTH by 90 degrees clockwise
    PGEast = 2,
    // Orientation rotated from NORTH by 180 degrees clockwise
    PGSouth = 3,
    // Orientation rotated from NORTH by 270 degrees clockwise
    PGWest = 4
};

/**
 This object holds the data for updating a screen orientation on a ProGlove display device.
 */
@interface PGSetDisplayOrientationRequest : NSObject

/**
 The orientation to be set on a connected device.
 */
@property PGOrientation orientation;

/**
 Convenience init used to initiate PGSetDisplayOrientationRequest with a selected orientation.

 @return PGSetDisplayOrientationRequest object
 */
-(nonnull instancetype)initWithOrientation:(PGOrientation)orientation;

/**
 Empty init not available, use initWithOrientation.

 @return nil
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

@end
