//
//  PGFeedbackManagerProtocol.h
//  ConnectSDK
//
//  Copyright © 2021 proglove. All rights reserved.
//
#import <ConnectSDK/PGCommand.h>
#import <ConnectSDK/PGFeedbackRequest.h>

/**
 Protocol contains all the feedback related methods.
 */
NS_SWIFT_NAME(PGFeedbackManager)
@protocol PGFeedbackManagerProtocol <NSObject>

/**
 Plays sequence on a connected scanner based on a provided id.
 */
- (void)playFeedbackSequenceWithFeedbackCommand:(nonnull PGCommand<PGFeedbackRequest *> *)feedbackRequest completionHandler:(void (^_Nonnull)(NSError * _Nullable error))completionHandler;

@end
