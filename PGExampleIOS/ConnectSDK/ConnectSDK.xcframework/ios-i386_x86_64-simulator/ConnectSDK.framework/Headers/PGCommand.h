//
//  PGCommand.h
//  ConnectSDK
//
//  Copyright © 2020 proglove. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ConnectSDK/PGCommandParams.h>

/**
 A PGCommand is used to send a command to a connected device through Connect SDK.
 The maximum number of PGCommands that can be sent to a device at a time is 1.
 The maximum PGCommands that can be queued for sending is 5. If PGCommand is requested and queue reached the limit, PGCommand will be droped and failed.
 */
@interface PGCommand<ObjectType> : NSObject

/**
 Convenience init used to initialize PGCommand with default PGCommandParams.
 
 @param data The data that will be encapsulated into a command.
 */
-(nonnull instancetype)init:(nonnull ObjectType)data;

/**
 Use to initialize PGCommand with additional parameters.
 
 @param data The data that will be encapsulated into a command.
 @param params The command parameters can affect how this command is executed.
 */
-(nonnull instancetype)init:(nonnull ObjectType)data withParams:(nonnull PGCommandParams *)params NS_SWIFT_NAME(init(data:params:));

/**
 Use init:withParams: instead

 @return nil
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

@end
