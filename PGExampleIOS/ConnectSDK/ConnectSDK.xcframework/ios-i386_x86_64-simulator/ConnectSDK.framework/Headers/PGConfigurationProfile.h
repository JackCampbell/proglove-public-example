//
//  PGConfigurationProfile.h
//  ConnectSDK
//
//  Copyright © 2020 proglove. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Configuration profile model class.
 */
@interface PGConfigurationProfile : NSObject

/**
 The id of the configuration profile.
 */
@property (nonatomic, readonly, nonnull) NSString *profileId;

-(nonnull instancetype)initWithId:(nullable NSString *)profileId;

/**
 PGConfigurationProfile cannot be created directly. Instead, obtain a profile object through `PGCentralManager`

 @return nil
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

@end
