//
//  PGConfigurationManagerProtocol.h
//  ConnectSDK
//
//  Copyright © 2020 proglove. All rights reserved.
//
#import <ConnectSDK/PGConfigurationProfile.h>
#import <ConnectSDK/PGCommand.h>
#import <ConnectSDK/PGPeripheral.h>

@protocol PGConfigurationManagerDelegate <NSObject>
/**
 The PGPeripheral did successfully set the configuration profile.
 
 @param peripheral The Scanner peripheral.
 @param configurationProfile The profile that is set to a connected device.
 */
- (void)peripheral:(nonnull PGPeripheral *)peripheral didSetConfigurationProfile:(nonnull PGConfigurationProfile *)configurationProfile;

/**
 The request to set a profile to a device failed.
 
 @param peripheral The Scanner peripheral if available.
 @param configurationProfile The profile that is tried to be set to a connected device.
 @param error The error occurred during the request.
 */
- (void)peripheral:(nullable PGPeripheral *)peripheral didFailToSetConfigurationProfile:(nullable PGConfigurationProfile *)configurationProfile error:(nullable NSError *)error;

@end


@protocol PGConfigurationManager <NSObject>

/**
 The configuration manager delegate.
*/
@property(nullable) id<PGConfigurationManagerDelegate> delegate;

/**
 This method will load configuration using a file at given path.
 One configuration at the time is supported, previously loaded configuration will be deleted.
 The file name must be proglove.proconfig
 
 @param configurationPath A path to a configuration file.
 @param completionHandler The completion handler containing error if encountered during configuration load.
 */
- (void)loadConfigurationFileAtPath:(nullable NSString *)configurationPath completionHandler:(void (^_Nonnull)(NSError * _Nullable error))completionHandler;

/**
 Method will delete all previously loaded configurations.
 
 @param completionHandler The completion handler containing error if encountered during configuration deletion.
 */
- (void)deleteLoadedConfigurationsWithCompletionHandler:(void (^_Nonnull)(NSError * _Nullable error))completionHandler;

/**
 Method will return an array of all the previously loaded configuration profiles.
 
 @param completionHandler The completion handler containing the array of all the previously loaded configurations.
 */
- (void)getAllConfigurationProfilesWithCompletionHandler:(void (^_Nonnull)(NSArray<PGConfigurationProfile *>  * _Nonnull configurationProfiles))completionHandler;

/**
 Use this method to set an active configuration profile.
    * Method will store the information about new active profile locally
    * Will try to apply the configuration profile to a connected device immediately.
 
 After each successful connection the active profile will be applied to a connected device.
 
 @param profileCommand The PGCommand with an profile.
 @param completionHandler The handler containing error indicating if the information is stored locally. The result if configuration profile is applied to a connected device will be sent via PGPeripheral delegate methods 'peripheral:didSetConfigurationProfile:' and 'peripheral:didFailToSetConfigurationProfile:error'
 */
- (void)changeActiveProfile:(nonnull PGCommand<PGConfigurationProfile *> *)profileCommand completionHandler:(void (^_Nonnull)(NSError * _Nullable error))completionHandler;

/**
 Use this method to retrieve the current active profile. The active profile is the profile that will be applied to a scanner on each successful connection.
 In case no active profile is set, nil will be returned.
 
 @param completionHandler The handler containing the active profile if available.
 */
- (void)getActiveConfigurationProfileWithCompletionHandler:(void (^_Nonnull)(PGConfigurationProfile * _Nullable activeProfile))completionHandler;

@end
