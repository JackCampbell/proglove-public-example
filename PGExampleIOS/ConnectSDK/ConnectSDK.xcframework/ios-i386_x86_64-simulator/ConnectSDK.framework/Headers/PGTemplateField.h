//
//  PGTemplateField.h
//  ConnectSDK
//
//  Copyright © 2021 proglove. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class represents the data, that should be displayed in a template field.
 */
@interface PGTemplateField : NSObject

/**
 The id of the field that should be filled with [header] and [content].
 */
@property (nonatomic) uint32_t fieldId;

/**
 The string that will be displayed in small letters on top of the field
 */
@property (nonatomic, nonnull) NSString *header;

/**
 The content of this field. The process critical information should be passed in here.
 */
@property (nonatomic, nonnull) NSString *content;

/**
 PGTemplateField  initializer.
 */
- (nonnull instancetype)initWithFieldId:(uint32_t)fieldId header:(nonnull NSString *)header content:(nonnull NSString *)content;

@end
