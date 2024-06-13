//
//  PGCentralManager(Mock).h
//  ConnectSDK
//
//  Copyright © 2019 Workaround GmbH. All rights reserved.
//

#import <ConnectSDK/PGMockPeripheral.h>


/**
 Mock peripheral methods
 */
@interface PGCentralManager(Mock)

/**
 Add a mock peripheral. PGPeripheral must be created from `-[PGMockPeripheral initWithIdentifier:]`
 
 @param peripheral The peripheral to add
 */
- (void)addMockPeripheral:(PGMockPeripheral * _Nonnull)peripheral;

@end
