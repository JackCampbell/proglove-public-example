//
//  PGFeedbackRequest.h
//  ConnectSDK
//
//  Copyright © 2021 proglove. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Predefined Feedback IDs
 */
typedef NS_ENUM(uint32_t, PGPredefinedFeedback) {
    /**
     A positive Feedback.
     */
    PGPredefinedFeedbackSuccess = 1,
    /**
     A negative Feedback.
     */
    PGPredefinedFeedbackError = 2,
    /**
     Special Feedback (Yellow).
     */
    PGPredefinedFeedbackSpecial1 = 3,
    /**
     Special Feedback (Purple).
     */
    PGPredefinedFeedbackSpecial2 = 4,
    /**
     Special Feedback (Cyan).
     */
    PGPredefinedFeedbackSpecial3 = 5
};


/**
 Model representing PGFeedback Request
 */
@interface PGFeedbackRequest : NSObject

/**
 Predefined feedback id.
 */
@property PGPredefinedFeedback predefinedFeedback;

/**
 Convenience init used to initiate PGFeedbackRequest with a predefined feedback.
 
 @return PGFeedbackRequest object
 */
- (nonnull instancetype)initWithFeedback:(PGPredefinedFeedback)feedback;

/**
 Empty init not available, use initWithFeedback.
 
 @return nil
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

@end
