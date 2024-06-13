//
//  PGCommandParams.h
//  ConnectSDK
//
//  Copyright © 2020 proglove. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Holder for parameter that affect the execution of commands. For example the queueing behaviour.
 */
@interface PGCommandParams : NSObject

/**
 When set to YES this command will clear all queued commands and then queue itself.
    *  Commands that are already started will not be canceled by this flag.
    *  This command will be first-in-queue afterwards but that does not guarantee execution of the command.
    *  It can be canceled by a different command with [replaceQueue] set to YES, too.
    (defaults to NO)
 */
@property BOOL replaceQueue;

@end
