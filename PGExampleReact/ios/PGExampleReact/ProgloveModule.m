
#import "ProgloveModule.h"


@implementation RCTProgloveModule

PGCentralManager *central = nil;

RCT_EXPORT_MODULE(ProgloveModule);

- (NSDictionary *)constantsToExport {
  return @{
    @"FEEDBACK_SUCCESS": [NSNumber numberWithInt:PGPredefinedFeedbackSuccess],
    @"FEEDBACK_ERROR": [NSNumber numberWithInt:PGPredefinedFeedbackError],
    @"FEEDBACK_WARNING": [NSNumber numberWithInt:PGPredefinedFeedbackSpecial1],
    @"ORIENTATION_UNSET": [NSNumber numberWithInt:PGInvalid],
    @"ORIENTATION_NORTH": [NSNumber numberWithInt:PGWest],
    @"ORIENTATION_EAST": [NSNumber numberWithInt:PGEast],
    @"ORIENTATION_SOUTH": [NSNumber numberWithInt:PGSouth],
    @"ORIENTATION_WEST": [NSNumber numberWithInt:PGWest]
  };
}

-(void)startObserving {
  // Will be called when this module's first listener is added.
}

-(void)stopObserving {
    // Will be called when this module's last listener is removed, or on dealloc.
}

+ (BOOL) requiresMainQueueSetup {
  return YES;
}


- (NSArray<NSString *> *)supportedEvents{
    return @[ @"pair", @"barcode", @"impulse" ];
}

RCT_EXPORT_METHOD(bindProglove) {
  NSLog(@":bindProglove ...\n");
  PGLogging.delegate = self;
  if(central != nil) {
    return;
  }
  central = [[PGCentralManager init] initWithDelegate:self enableRestoration:NO];
}

RCT_EXPORT_METHOD(unbindProglove) {
  NSLog(@":unbindProglove ...\n");
  central = nil; // finish
}

RCT_EXPORT_METHOD(isActive: (RCTPromiseResolveBlock)resolve withPromise:(RCTPromiseRejectBlock)reject) {
  if(central != nil) {
    resolve([NSNumber numberWithBool:TRUE]);
  } else {
    resolve([NSNumber numberWithBool:FALSE]);
  }
}

RCT_EXPORT_METHOD(pair: (RCTPromiseResolveBlock)resolve withPromise:(RCTPromiseRejectBlock)reject) {
  if(central.state != PGManagerStatePoweredOn) {
    reject(@"event_failture", @"device is not powered on", nil);
    return;
  }
  if(central.connectedScanner == NULL) {
    resolve([NSNumber numberWithBool:FALSE]);
    return;
  }
  UIImage *image = [central initiateScannerConnectionWithImageSize:CGSizeMake(320, 320)];
  dispatch_async(dispatch_get_main_queue(), ^{
    [self showPairAlert:image];
  });
  resolve([NSNumber numberWithBool:TRUE]);
}

RCT_EXPORT_METHOD(unpair: (RCTPromiseResolveBlock)resolve withPromise:(RCTPromiseRejectBlock)reject) {
  if(central.state != PGManagerStatePoweredOn) {
    reject(@"event_failture", @"device is not powered on", nil);
    return;
  }
  if(central.connectedScanner != NULL) {
    resolve([NSNumber numberWithBool:FALSE]);
    return;
  }
  [central cancelScannerConnection:central.connectedScanner];
  resolve([NSNumber numberWithBool:TRUE]);
}

RCT_EXPORT_METHOD(isConnected: (RCTPromiseResolveBlock)resolve withPromise:(RCTPromiseRejectBlock)reject) {
  if(central.connectedScanner == NULL) {
    resolve([NSNumber numberWithBool:FALSE]);
  } else {
    resolve([NSNumber numberWithBool:TRUE]);
  }
}

RCT_EXPORT_METHOD(display:(NSString *)template withField:(NSArray<NSDictionary *> *)fields withResolve:(RCTPromiseResolveBlock)resolve withPromise:(RCTPromiseRejectBlock)reject) {
  PGTemplateField *line1 = [[PGTemplateField alloc]initWithFieldId:1 header:@"Storage Unit" content:@"R15"];
  PGTemplateField *line2 = [[PGTemplateField alloc]initWithFieldId:2 header:@"Item" content:@"Engine 12"];
  PGTemplateField *line3 = [[PGTemplateField alloc]initWithFieldId:3 header:@"Quantity" content:@"10"];
  id objects[] = { line1, line2, line3 };
  NSUInteger count = sizeof(objects) / sizeof(id);

  NSArray<PGTemplateField *> *lines = [[NSArray alloc] initWithObjects:objects count:count];
  PGScreenData *data = [[PGScreenData alloc] initWithTemplateId:@"PG3" templateFields:lines refreshType:PGFullRefresh duration:5000];
  PGCommand<PGScreenData *> *command = [[PGCommand<PGScreenData *>alloc] init:data];
  [central.displayManager setScreen:command completionHandler:^(NSError *_Nullable error) {
    if(error != nil) {
      resolve([NSNumber numberWithBool:FALSE]);
    } else {
      resolve([NSNumber numberWithBool:TRUE]);
    }
  }];
}

RCT_EXPORT_METHOD(feedback:(NSInteger)type withResolve:(RCTPromiseResolveBlock)resolve withPromise:(RCTPromiseRejectBlock)reject) {
  PGPredefinedFeedback feedback = (PGPredefinedFeedback)type;
  PGFeedbackRequest *request = [[PGFeedbackRequest alloc] initWithFeedback:feedback];
  PGCommand *command = [[PGCommand alloc] init:request];
  [central.feedbackManager playFeedbackSequenceWithFeedbackCommand:command completionHandler:^(NSError *_Nullable error) {
    if(error != nil) {
      resolve([NSNumber numberWithBool:FALSE]);
    } else {
      resolve([NSNumber numberWithBool:TRUE]);
    }
  }];
}

RCT_EXPORT_METHOD(orientation:(NSInteger)type withResolve:(RCTPromiseResolveBlock)resolve withPromise:(RCTPromiseRejectBlock)reject) {
  PGOrientation orientation = (PGOrientation)type;
  PGSetDisplayOrientationRequest *request = [[PGSetDisplayOrientationRequest alloc] initWithOrientation:orientation];
  PGCommand *command = [[PGCommand alloc] init:request];
  [central.displayManager setDisplayOrientation:command completionHandler:^(NSError * _Nullable error) {
    if(error != nil) {
      resolve([NSNumber numberWithBool:FALSE]);
    } else {
      resolve([NSNumber numberWithBool:TRUE]);
    }
  }];
}

- (void)PGLog:(BOOL)asynchronous flag:(PGLogFlag)flag context:(NSInteger)context file:(NSString * _Nonnull)file function:(NSString * _Nonnull)function line:(NSUInteger)line tag:(nullable id)tag message:(NSString * _Nonnull)message {
  NSLog(@"PGLog: %@", message);
}

- (void)managerDidUpdateState:(nonnull PGManager *)manager {
}

- (void)centralManager:(nonnull PGCentralManager *)centralManager didFailToConnectToScanner:(nonnull PGPeripheral *)scanner error:(nullable NSError *)error {
}

- (void)centralManager:(nonnull PGCentralManager *)centralManager didFailToInitiateConnection:(nullable NSError *)error {
}

- (void)centralManager:(nonnull PGCentralManager *)centralManager didLostConnectionAndReconnectingToScanner:(nonnull PGPeripheral *)scanner {
}

- (void)centralManager:(nonnull PGCentralManager *)centralManager didStartSearchingForIndicator:(nullable NSString *)indicator {
}

- (void)centralManager:(nonnull PGCentralManager *)centralManager scannerDidBecomeReady:(nonnull PGPeripheral *)scanner {
}

- (void)centralManager:(nonnull PGCentralManager *)centralManager connectingToScanner:(nonnull PGPeripheral *)scanner {
  scanner.delegate = self;
}

- (void)centralManager:(nonnull PGCentralManager *)centralManager scannerDidConnect:(nonnull PGPeripheral *)scanner {
  [self sendEventWithName:@"pair" body: @{
      @"state": [NSNumber numberWithBool:TRUE]
  }];
  dispatch_async(dispatch_get_main_queue(), ^{
    [self hidePairAlert];
  });
}

- (void)centralManager:(nonnull PGCentralManager *)centralManager didDisconnectFromScanner:(nonnull PGPeripheral *)scanner error:(nullable NSError *)error {
  [self sendEventWithName:@"pair" body: @{
    @"state": [NSNumber numberWithBool:FALSE]
  }];
}




UIAlertController *alert = nil;

-(void)showPairAlert:(UIImage *)image {
    UIViewController *root = [[[[UIApplication sharedApplication] delegate] window] rootViewController];
    alert = [UIAlertController alertControllerWithTitle:@"Pair" message:nil preferredStyle:UIAlertControllerStyleAlert];
    // UIImageView *code = [[UIImageView alloc] initWithImage:image];
    UIImageView *code = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 320, 320)];
    [code setImage:image];
    [alert.view addSubview:code];
    [alert.view addConstraint:[NSLayoutConstraint constraintWithItem:alert.view attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1 constant:320]];
    [alert.view addConstraint:[NSLayoutConstraint constraintWithItem:alert.view attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1 constant:320]];
    [alert addAction:[UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        // auto closing dialog
    }]];

    [root presentViewController:alert animated:YES completion:nil];
}

-(void)hidePairAlert {
   // UIViewController *root = [[[[UIApplication sharedApplication] delegate] window] rootViewController];
   [alert dismissViewControllerAnimated:YES completion:nil];
}


- (void)peripheral:(PGPeripheral *)peripheral didScanBarcodeWithResult:(PGScannedBarcodeResult *)result {
  NSMutableDictionary *dict = [NSMutableDictionary dictionaryWithSharedKeySet: @{
    @"content": result.barcodeContent
  }];
  if(result.barcodeSymbology) {
    dict[@"symbol"] = result.barcodeSymbology;
  }
  [self sendEventWithName:@"pair" body: dict];
}

- (void)encodeWithCoder:(nonnull NSCoder *)coder {
    
}

- (void)traitCollectionDidChange:(nullable UITraitCollection *)previousTraitCollection {
    
}

- (void)preferredContentSizeDidChangeForChildContentContainer:(nonnull id<UIContentContainer>)container {
    
}

- (CGSize)sizeForChildContentContainer:(nonnull id<UIContentContainer>)container withParentContainerSize:(CGSize)parentSize {
    return parentSize;
}

- (void)systemLayoutFittingSizeDidChangeForChildContentContainer:(nonnull id<UIContentContainer>)container {
    
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(nonnull id<UIViewControllerTransitionCoordinator>)coordinator {
    
}

- (void)willTransitionToTraitCollection:(nonnull UITraitCollection *)newCollection withTransitionCoordinator:(nonnull id<UIViewControllerTransitionCoordinator>)coordinator {
    
}

- (void)didUpdateFocusInContext:(nonnull UIFocusUpdateContext *)context withAnimationCoordinator:(nonnull UIFocusAnimationCoordinator *)coordinator {
    
}

- (void)setNeedsFocusUpdate {
    
}

- (BOOL)shouldUpdateFocusInContext:(nonnull UIFocusUpdateContext *)context {
    return YES;
}

- (void)updateFocusIfNeeded {
    
}
@end
