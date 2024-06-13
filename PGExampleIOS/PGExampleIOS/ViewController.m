//
//  ViewController.m
//  PGExampleIOS
//
//  Created by Fırat ÖZDEMİR on 4.01.2023.
//

#import "ViewController.h"
#import <ConnectSDK/ConnectSDK.h>
#import <ConnectSDK/PGFeedbackRequest.h>
#import <ConnectSDK/PGPeripheral.h>

@interface ViewController () <PGCentralManagerDelegate, PGPeripheralDelegate, PGLoggingDelegate>
@property PGCentralManager *central;
@property (weak, nonatomic) IBOutlet UILabel *barcodeText;
@end

@implementation ViewController

/*
 PLIST =======
 
 
 <key>NSBluetoothAlwaysUsageDescription</key>
 <string>Bluetooth required in order to connect to a scanner</string>
 <key>UIBackgroundModes</key>
 <array>
     <string>bluetooth-central</string>
 </array>
 */

- (void)viewDidLoad {
    [super viewDidLoad];
    PGLogging.delegate = self;
    self.central = [[PGCentralManager alloc] initWithDelegate:self enableRestoration:NO];
}


UIAlertController *alert = nil;

-(void)showPairAlert:(UIImage *)image {
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
    [self presentViewController:alert animated:YES completion:nil];
}

- (IBAction)pairAndUnpair:(UIButton *)sender {
    NSLog(@"OnScannerConnect");
    if(self.central.state != PGManagerStatePoweredOn) {
        NSLog(@"Power Off !!");
        return;
    }
    if(self.central.connectedScanner != NULL) {
        [self.central cancelScannerConnection:self.central.connectedScanner];
        NSLog(@"Disconnecting");
        return;
    }
    UIImage *image = [self.central initiateScannerConnectionWithImageSize:CGSizeMake(320, 320)];
    [self showPairAlert:image];
}

- (void)centralManager:(nonnull PGCentralManager *)centralManager scannerDidConnect:(nonnull PGPeripheral *)scanner {
    [alert dismissViewControllerAnimated:YES completion:nil];
}


- (void)peripheral:(PGPeripheral *)peripheral didScanBarcodeWithResult:(PGScannedBarcodeResult *)result {
    [self.barcodeText setText:result.barcodeContent];
    if(result.barcodeSymbology) {
        NSLog(@"Barcode Symbol: %@", result.barcodeSymbology);
    }
}

- (IBAction)commandTest:(UIButton *)sender {
    PGCommandParams *params = [[PGCommandParams alloc] init];
    params.replaceQueue = YES;
    PGDeviceInformationRequest *request = [[PGDeviceInformationRequest alloc] init];
    PGCommand *command = [[PGCommand alloc] init:request withParams:params];
    [self.central.connectedScanner requestDeviceInformationWithDeviceInfoCommand:command completionHandler:^(PGDeviceInformation * _Nullable deviceInformation, NSError * _Nullable error) {
        // Complete
    }];
}

- (IBAction)displayTest:(UIButton *)sender {
    PGTemplateField *line1 = [[PGTemplateField alloc]initWithFieldId:1 header:@"Storage Unit" content:@"R15"];
    PGTemplateField *line2 = [[PGTemplateField alloc]initWithFieldId:2 header:@"Item" content:@"Engine 12"];
    PGTemplateField *line3 = [[PGTemplateField alloc]initWithFieldId:3 header:@"Quantity" content:@"10"];
    id objects[] = { line1, line2, line3 };
    NSUInteger count = sizeof(objects) / sizeof(id);

    NSArray<PGTemplateField *> *lines = [[NSArray alloc] initWithObjects:objects count:count];
    PGScreenData *data = [[PGScreenData alloc] initWithTemplateId:@"PG3" templateFields:lines refreshType:PGFullRefresh duration:5000];
    PGCommand<PGScreenData *> *command = [[PGCommand<PGScreenData *>alloc] init:data];
    [self.central.displayManager setScreen:command completionHandler:^(NSError *_Nullable error) {
        // PASS
    }];
}

- (IBAction)feedbackTest:(UIButton *)sender {
    PGFeedbackRequest *request = [[PGFeedbackRequest alloc] initWithFeedback:PGPredefinedFeedbackSpecial2];
    PGCommand *command = [[PGCommand alloc] init:request];
    [self.central.feedbackManager playFeedbackSequenceWithFeedbackCommand:command completionHandler:^(NSError *_Nullable error) {
        // OK
    }];
}

- (IBAction)orientationTest:(UIButton *)sender {
    PGSetDisplayOrientationRequest *request = [[PGSetDisplayOrientationRequest alloc] initWithOrientation:PGNorth];
    PGCommand *command = [[PGCommand alloc] init:request];
    [self.central.displayManager setDisplayOrientation:command completionHandler:^(NSError * _Nullable error) {
        // PASS
    }];
}

- (void)managerDidUpdateState:(nonnull PGManager *)manager {
    
}

- (void)centralManager:(nonnull PGCentralManager *)centralManager connectingToScanner:(nonnull PGPeripheral *)scanner {
    scanner.delegate = self;
}

- (void)centralManager:(nonnull PGCentralManager *)centralManager didDisconnectFromScanner:(nonnull PGPeripheral *)scanner error:(nullable NSError *)error {
    
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

- (void)PGLog:(BOOL)asynchronous flag:(PGLogFlag)flag context:(NSInteger)context file:(NSString * _Nonnull)file function:(NSString * _Nonnull)function line:(NSUInteger)line tag:(nullable id)tag message:(NSString * _Nonnull)message {
    NSLog(@"PGLOG: %@", message);
}


@end
