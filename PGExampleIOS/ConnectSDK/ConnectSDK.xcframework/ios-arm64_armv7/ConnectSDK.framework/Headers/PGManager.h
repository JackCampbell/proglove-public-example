//
//  PGManager.h
//  ConnectSDK
//
//  Copyright © 2019 Workaround GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PGManagerDelegate;

/**
 *  @class PGManager
 *
 *  @discussion Entry point to the manager role. Commands should only be issued when its state is <code>PGManagerStatePoweredOn</code>.
 *
 */

@interface PGManager : NSObject

/**
 Represents the current state of a PGManager.
 
 - PGManagerStateUnknown: State unknown, update imminent.
 - PGManagerStateResetting: The connection with the system service was momentarily lost, update imminent.
 - PGManagerStateUnsupported: The platform doesn't support the Bluetooth Low Energy Central/Client role.
 - PGManagerStateUnauthorized: The application is not authorized to use the Bluetooth Low Energy role.
 - PGManagerStatePoweredOff: Bluetooth is currently powered off.
 - PGManagerStatePoweredOn: Bluetooth is currently powered on and available to use.
 */
typedef NS_ENUM(NSInteger, PGManagerState) {
	/// State unknown, update imminent.
	PGManagerStateUnknown = 0,
	/// The connection with the system service was momentarily lost, update imminent.
	PGManagerStateResetting,
	/// The platform doesn't support the Bluetooth Low Energy Central/Client role.
	PGManagerStateUnsupported,
	/// The application is not authorized to use the Bluetooth Low Energy role.
	PGManagerStateUnauthorized,
	/// Bluetooth is currently powered off.
	PGManagerStatePoweredOff,
	/// Bluetooth is currently powered on and available to use.
	PGManagerStatePoweredOn
};

/**
 *  @property state
 *
 *  @discussion The current state of the manager, initially set to <code>PGManagerStateUnknown</code>.
 *				Updates are provided by required delegate method {@link managerDidUpdateState:}.
 *
 */
@property(nonatomic, readonly) PGManagerState state;

/**
 *  @property delegate
 *
 *  @discussion The delegate object that will receive manager events.
 *
 */
@property(nonatomic, weak, nullable) id<PGManagerDelegate> delegate;

@end

/**
 *  @protocol PGManagerDelegate
 *
 *  @discussion The delegate of a {@link PGManager} object must adopt the <code>PGManagerDelegate</code> protocol. The
 *              single required method indicates the availability of the manager.
 *
 */
@protocol PGManagerDelegate <NSObject>

@required
/**
 *  @method centralManagerDidUpdateState:
 *
 *  @param manager  The manager whose state has changed.
 *
 *  @discussion     Invoked whenever the manager's state has been updated. Commands should only be issued when the state is
 *                  <code>PGManagerStatePoweredOn</code>. A state below <code>PGManagerStatePoweredOn</code>
 *                  implies that scanning has stopped and any connected peripherals have been disconnected. If the state moves below
 *                  <code>PGManagerStatePoweredOff</code>, all <code>PGPeripheral</code> or <code>PGCentral</code> objects obtained from this
 *                  manager become invalid and must be retrieved or discovered again.
 *
 *  @see            state
 *
 */
- (void)managerDidUpdateState:(nonnull PGManager *)manager;

@end

NS_ASSUME_NONNULL_END
