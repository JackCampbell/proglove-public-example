//
//  PGScreenData.h
//  ConnectSDK
//
//  Copyright © 2021 proglove. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ConnectSDK/PGTemplateField.h>


/**
 The refresh type, the display should be using when setting a screen.
 
 - PGDefault: Uses the default refresh strategy defined by ProGlove. Partial or full refresh might be used.
 - PGFullRefresh: Uses a full refresh for this screen setting. This will take a bit longer, but removes artifacts from previous screens. Full-refresh will definitely be used.
 - PGPartialRefresh: Uses a partial refresh for this screen setting. This will be faster than a full refresh, but may produce artifacts of the current screen on the display. Partial-refresh will definitely be used.
 */
typedef NS_ENUM(NSInteger, PGRefreshType) {
    /// Uses the default refresh strategy defined by ProGlove. Partial or full refresh might be used.
    PGDefault,
    /// Uses a full refresh for this screen setting. This will take a bit longer, but removes artifacts from previous screens. Full-refresh will definitely be used.
    PGFullRefresh,
    ///  Uses a partial refresh for this screen setting. This will be faster than a full refresh, but may produce artifacts of the current screen on the display. Partial-refresh will definitely be used.
    PGPartialRefresh
};


/**
 This object holds the data for updating a screen on a ProGlove display device.
 */
@interface PGScreenData : NSObject

/**
 The id of the template to be used to construct the screen.
 */
@property (nonatomic, nonnull) NSString *templateId;

/**
 A list of PGTemplateField which hold the data for header and content for each field in the template.
 */
@property (nonatomic, nonnull) NSArray<PGTemplateField *> *templateFields;

/**
 The PGRefreshType type to be used while setting this screen.
 */
@property (nonatomic) PGRefreshType refreshType;

/**
 The duration for how long the notification should be displayed.
 Only used when sent with NotificationScreen, must be >0 in that case.
 An automatic transition back to the previous screen will take place after this time. A notification can be replaced by any other notification and by a new screen.
 Depending on your implementation, this is thus only an upper limit on the time this notification will be shown.
 */
@property (nonatomic) uint32_t durationMs;

/**
 Convenience initializer for creating PGScreenData model class. Refresh type will default to PGDefault and durationMs will default to 0.
 
 @param templateId The id of the template to be used to construct the screen.
 @param templateFields A list of PGTemplateField which hold the data for header and content for each field in the template
 */
- (nonnull instancetype)initWithTemplateId:(NSString * _Nonnull)templateId templateFields:(NSArray<PGTemplateField *> * _Nonnull)templateFields;

/**
 Designated initializer for creating PGScreenData model class.
 
 @param templateId The id of the template to be used to construct the screen.
 @param templateFields A list of PGTemplateField which hold the data for header and content for each field in the template
 @param refreshType The PGRefreshType type to be used while setting this screen.
 @param duration The duration for how long the notification should be displayed.
 */
- (nonnull instancetype)initWithTemplateId:(NSString * _Nonnull)templateId templateFields:(NSArray<PGTemplateField *> * _Nonnull)templateFields refreshType:(PGRefreshType)refreshType duration:(uint32_t)duration;

@end

