//
//  PGLogger.h
//  ConnectSDK
//
//  Copyright © 2019 Workaround GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Log flags, used to determine the severity of a log message
 
 - PGLogFlagError: Error log flag - used for severe problems
 - PGLogFlagWarning: Warning log flag - used for less severe, recoverable problems
 - PGLogFlagInfo: Info log flag - used for informational purposes
 - PGLogFlagDebug: Debug log flag - used to aid debugging
 - PGLogFlagVerbose: Verbose log flag - used for very verbose debugging
 */
typedef NS_OPTIONS(NSUInteger, PGLogFlag) {
	
	/// Error log flag - used for severe problems
	PGLogFlagError      = (1 << 0),
	/// Warning log flag - used for less severe, recoverable problems
	PGLogFlagWarning    = (1 << 1),
	/// Info log flag - used for informational purposes
	PGLogFlagInfo       = (1 << 2),
	/// Debug log flag - used to aid debugging
	PGLogFlagDebug      = (1 << 3),
	/// Verbose log flag - used for very verbose debugging
	PGLogFlagVerbose    = (1 << 4),
};


/**
 Log levels, used for filtering log messages
 
 - PGLogLevelOff: Off log level - no messages will be logged
 - PGLogLevelError: Error log level - only errors will be logged
 - PGLogLevelWarning: Warning log level - errors and warnings will be logged
 - PGLogLevelInfo: Info log level - errors, warnings and info will be logged
 - PGLogLevelDebug: Debug log level - errors, warnings, info and debug will be logged
 - PGLogLevelVerbose: Verbose log level - errors, warnings, info, debug and verbose will be logged
 - PGLogLevelAll: All log level - All messages will be logged
 */
typedef NS_ENUM(NSUInteger, PGLogLevel) {
	/// Off log level - no messages will be logged
	PGLogLevelOff       = 0,
	/// Error log level - only errors will be logged
	PGLogLevelError     = (PGLogFlagError),
	/// Warning log level - errors and warnings will be logged
	PGLogLevelWarning   = (PGLogLevelError   | PGLogFlagWarning),
	/// Info log level - errors, warnings and info will be logged
	PGLogLevelInfo      = (PGLogLevelWarning | PGLogFlagInfo),
	/// Debug log level - errors, warnings, info and debug will be logged
	PGLogLevelDebug     = (PGLogLevelInfo    | PGLogFlagDebug),
	/// Verbose log level - errors, warnings, info, debug and verbose will be logged
	PGLogLevelVerbose   = (PGLogLevelDebug   | PGLogFlagVerbose),
	/// All log level - All messages will be logged
	PGLogLevelAll       = NSUIntegerMax
};

@protocol PGLoggingDelegate;

/**
 The logging class for the library
 */
@interface PGLogging : NSObject

/**
 The class delegate property. Set a delegate to receive log messages
 */
@property(class, nonatomic, weak, nullable) id<PGLoggingDelegate> delegate;

/**
 Do not create instances of this class.
 
 @return nil
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

@end

/**
 The logging class delegate protocol
 */
@protocol PGLoggingDelegate <NSObject>

@required

/**
 This method notifies the delegate of new log messages when they occur
 
 @param asynchronous If `YES`, this log message can be handled asynchronously
 @param flag The log flag
 @param context A context for the message, if provided
 @param file The file that the log occurred in
 @param function The function that the log occurred in
 @param line The line that the log occurred on
 @param tag A tag for the message, if provided
 @param message The message to log
 */
- (void)PGLog:(BOOL)asynchronous
	   	   flag:(PGLogFlag)flag
	    context:(NSInteger)context
	       file:(NSString * _Nonnull)file
	   function:(NSString * _Nonnull)function
	       line:(NSUInteger)line
	   	    tag:(nullable id)tag
	    message:(NSString * _Nonnull)message;

@end
