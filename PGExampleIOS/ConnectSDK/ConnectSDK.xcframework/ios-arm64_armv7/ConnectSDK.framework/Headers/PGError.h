//
//  PGError.h
//  ConnectSDK
//
//  Copyright © 2019 Workaround GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 The peripheral error domain
 */
extern NSString * _Nonnull const PGPeripheralErrorDomain;

/**
 All PG peripheral error codes
 */
typedef NS_ENUM(NSInteger, PGPeripheralError) {
    /**
    Bluetooth not available.
    */
    PGPeripheralErrorBluetoothNotAvailable,
    /**
    Unhandled error.
    */
    PGPeripheralErrorUnhandled,
    /**
    Unexpected error that cannot be resolved.
    */
    PGPeripheralErrorUnexpectedUnresolvable,
    /**
    Connecting timed out
    */
    PGPeripheralErrorConnectingTimedOut,
    /**
    Connection timed out
    */
    PGPeripheralErrorConnectionTimedOut,
    /**
    Not connected to the peripheral
    */
    PGPeripheralErrorNotConnected,
    /**
    Device is not ready to perform this action (usually when connecting)
    */
    PGPeripheralErrorNotReady,
    /**
    The peripheral closed the connection or went out of range
    */
    PGPeripheralErrorPeripheralDisconnected,
    /**
    The device was not paired, or pairing was cancelled
    */
    PGPeripheralErrorPeripheralNotPaired,
    /**
    The operation was cancelled
    */
    PGPeripheralErrorOperationCancelled,
    /**
    The write to the attribute went beyond the bounds of the attribute's size
    */
    PGPeripheralErrorAttributeWriteTooLarge,
    /**
    Writing to the attribute failed but can be retried later
    */
    PGPeripheralErrorAttributeWriteFailedTryLater,
    /**
    Required services were missing
    */
    PGPeripheralErrorMissingServices,
    /**
    An ATT error occurred discovering services
    */
    PGPeripheralErrorATTErrorDiscoveringServices,
    /**
    Required characteristics were missing
    */
    PGPeripheralErrorMissingCharacteristics,
    /**
    An ATT error occurred discovering characteristics, see PGPeripheralErrorServiceKey for the NSUUID of the service
    */
    PGPeripheralErrorATTErrorDiscoveringCharacteristics,
    /**
    Data read from the device was invalid. Could suggest the GATT cache is invalid, requiring a Bluetooth toggle.
    */
    PGPeripheralErrorInvalidData,
    /**
    The device is not compatible with this App based on its model number. See PGPeripheralErrorIncompatibleModelNumberKey for the model number
    */
    PGPeripheralErrorIncompatibleModel,
    /**
    Peripheral discovery timed out
    */
    PGPeripheralErrorDiscoveryTimedOut,
    /**
    Peripheral feature is unsupported
    */
    PGPeripheralErrorUnsupportedFeature,
    /**
    Peripheral was in an invalid state for performing this operation
    */
    PGPeripheralErrorInvalidState
};

/**
 The WearableApi error domain
 */
extern NSString * _Nonnull const PGWearableApiErrorDomain;

/**
 PG Wearable API error codes
 */
typedef NS_ENUM(NSInteger, PGWearableApiError) {
    /**
    Wapi request was canceled.
    */
    PGWearableApiErrorRequestCanceled,
    /**
    Wapi request was denied. Queue limit reached.
     */
    PGWearableApiErrorRequestDenied,
    /**
    Wapi request timed out.
     */
    PGWearableApiErrorRequestTimeout,
    /**
    Wrong wapi payload received.
     */
    PGWearableApiErrorInvalidPayload,
    /**
    The capability is not supported.
     */
    PGWearableApiErrorCapabilityNotSupported
};

/**
 The scanner feedback api error domain.
 */
extern NSString * _Nonnull const PGFeedbackApiErrorDomain;

typedef NS_ENUM(NSInteger, PGFeedbackApiError) {
    /**
     Feedback for sequence id not found.
    */
    PGFeedbackApiErrorSequenceNotFound
};

/**
 The scanner display api error domain.
 */
extern NSString * _Nonnull const PGDisplayApiErrorDomain;

/**
 PG Display API error codes.
 */
typedef NS_ENUM(NSInteger, PGDisplayApiError) {
    /**
     The provided Template id is nil or empty.
    */
    PGDisplayApiErrorEmptyTemplateId,
    /**
     The provided Template id not found in the list of supported ids.
    */
    PGDisplayApiErrorTemplateIdNotFound,
    /**
     There is mismatch in number of fields provided and supported by selected template.
    */
    PGDisplayApiErrorInvalidNumberOfFieldsInTemplate,
    /**
     The provided duration is negative value.
    */
    PGDisplayApiErrorNegativeDuration,
    /**
     The provided field id is not in the list of supported ids. The field id is number beetween 1 and number of supported fields.
    */
    PGDisplayApiErrorFieldIdNotInTemplate,
    /**
     The provided list of fields contain duplicate field id.
    */
    PGDisplayApiErrorDuplicateFieldId,
    /**
     The header value is too long.
    */
    PGDisplayApiErrorHeaderTooLong,
    /**
     The content value is too long.
    */
    PGDisplayApiErrorContentTooLong
};

/**
 The ConfigurationApi error domain
 */
extern NSString * _Nonnull const PGConfigurationErrorDomain;

/**
 PG configuration api error codes
 */
typedef NS_ENUM(NSInteger, PGConfigurationApiError) {
    /**
    Fail to parse data into Wapi object.
    */
    PGConfigurationApiErrorFailToParse,
    /**
    No data at given path.
    */
    PGConfigurationApiErrorMissingData,
    /**
     Configuration not loaded.
     */
    PGConfigurationNotFound,
    /**
     Configuration id nil.
     */
    PGConfigurationIdNil,
    /**
     Configuration manifest not present in the configuration file.
     */
    PGConfigurationMissingManifest,
    /**
     The configuration profile not found.
     */
    PGConfigurationMissingProfile,
    /**
     Missing profile id.
     */
    PGConfigurationMissingProfileId,
    /**
     Configuration missing default profile.
     */
    PGConfigurationMissingDefaultProfile,
    /**
     Configuration profile missing document.
     */
    PGConfigurationProfileMissingDocument
};

/**
 The UUID string of the service the error occurred on
 */
extern NSString * _Nonnull const PGPeripheralErrorServiceKey;
/**
 The incompatible model number NSString that was discovered for this device
 */
extern NSString * _Nonnull const PGPeripheralErrorIncompatibleModelNumberKey;
/**
A NSNumber Boolean value indicating if the central has retried connection to this peripheral
*/
extern NSString * _Nonnull const PGPeripheralErrorCentralHasRetriedConnectingKey;
