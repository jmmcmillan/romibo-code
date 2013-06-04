//
//  ViewController.m
//  Romibo
//
//  Created by HCII on 12/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"
#import "EmotionNubView.h"
#import "DrivingNubView.h"
#import "ConfigViewController.h"
#import "Romibo.h"
#import "CmdDelegate.h"
#import "DrawPatternLockView.h"
#import "DrawPatternLockViewController.h"
#import "ChildBaseView.h"

@implementation ViewController 

//@synthesize commandPickerPopover;

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    self.view.backgroundColor = [[UIColor alloc] initWithPatternImage:[UIImage imageNamed:@"background-01.png"]];
    
    
    romibo = [[Romibo alloc] init];
    
    [self closePopup];
    
    [self setupHeadTiltSubview];
    [tNub setCmdDelegate:romibo];
    
    [self setupDrivingSubview];
    [dNub setCmdDelegate:romibo];
    
    //gathers the generic list of commands
    [self setupRomiboCommands];
    
    //sets up buttons specified in screens
    [self setupButtons];
    
    if (!childView)
    {
        childView = [[ChildBaseView alloc] initWithNibName:@"ChildBaseView" bundle:nil];
        childView.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
        
        [childView setRomibo:romibo];
        [childView setRomiboCommands:romiboCommands];
    }

}


-(void)setupButtons
{
    NSString* screenPath = [[NSBundle mainBundle] pathForResource:@"Home" ofType:@"txt"];
    
    NSString* allCommands = [NSString stringWithContentsOfFile:screenPath encoding:NSUTF8StringEncoding error:NULL];
    
    NSArray* commandsArray = [allCommands componentsSeparatedByString:@"\n"];
    
    for (int i = 1; i < 19; i++)
    {
        NSString* command = [commandsArray objectAtIndex:i-1];
        NSArray* commandFragments = [command componentsSeparatedByString:@","];
        
        if ([commandFragments count] < 2)
        {
            NSLog(@"Invalid command syntax: %@", command);
            continue;
        }
        
        NSString* cmd = [[commandFragments objectAtIndex:0] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
        
        NSString* label = [[commandFragments objectAtIndex:1] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
        
        if ([romiboCommands objectForKey:label] == nil)
        {
            [romiboCommands setObject:cmd forKey:label];
            [buttonLabels addObject:label];
        }
        
        UIButton* button = (UIButton*)[self.view viewWithTag:i];
        [button setTitle:label forState:UIControlStateNormal];
        
        //NSLog(@"%@", [[button titleLabel] text]);
    }
}

-(void)setupRomiboCommands
{
    
    NSString* commandPath = [[NSBundle mainBundle] pathForResource:@"RomiboCommands" ofType:@"txt"];
    
    NSString* allCommands = [NSString stringWithContentsOfFile:commandPath encoding:NSUTF8StringEncoding error:NULL];
    
    NSArray* commandsArray = [allCommands componentsSeparatedByString:@"\n"];
    
    romiboCommands = [[NSMutableDictionary alloc] init];
    buttonLabels = [[NSMutableArray alloc] init];
    
    for (int i = 0; i < commandsArray.count; i++)
    {
        NSString* command = [commandsArray objectAtIndex:i];
        NSArray* commandFragments = [command componentsSeparatedByString:@","];
        
        if ([commandFragments count] < 2)
        {
            NSLog(@"Invalid command syntax: %@", command);
            continue;
        }
        
        NSString* cmd = [[commandFragments objectAtIndex:0] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
        
        NSString* label = [[commandFragments objectAtIndex:1] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
        
        [romiboCommands setObject:cmd forKey:label];
        [buttonLabels addObject:label];
    }
}


-(IBAction)handleLongPress:(UILongPressGestureRecognizer*)gesture
{
    UIButton* button = (UIButton *) gesture.view;
    [self pickCommand:button];
    
}

-(IBAction)changeShell:(UILongPressGestureRecognizer*)gesture
{
    if (![childView isBeingPresented])
        [self presentModalViewController:childView animated:YES];

}



- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil
    
    [tNub release];
    [dNub release];
    [romibo release];
    [cmdTimer release];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    
    /*if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
     return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
     } else {
     return YES;
     }*/
    
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(void)setupHeadTiltSubview
{
    UIImageView* headTiltView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"tiltBackground.png"]];
    
    tNub = [[HeadTiltNubView alloc] init];
    
    headTiltView.frame = CGRectMake(400, 215, 338, 338);
    
    tNub.center = CGPointMake(CGRectGetMidX(headTiltView.bounds), CGRectGetMidY(headTiltView.bounds));
    
    tNub.userInteractionEnabled = YES;
    headTiltView.userInteractionEnabled = YES;
    
    [headTiltView addSubview:tNub];
    [tNub release];
    
    [self.view addSubview:headTiltView ];
    [headTiltView release];
}

-(void)setupDrivingSubview
{
    UIImageView* drivingView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"driveBackground.png"]];
    
    dNub = [[DrivingNubView alloc] init];
    
    drivingView.frame = CGRectMake(28, 215, 338, 338);
    
    dNub.center = CGPointMake(CGRectGetMidX(drivingView.bounds), CGRectGetMidY(drivingView.bounds));
    
    dNub.userInteractionEnabled = YES;
    drivingView.userInteractionEnabled = YES;
    
    [drivingView addSubview:dNub];
    [dNub release];
    
    [self.view addSubview:drivingView ];
    [drivingView release];
}

- (IBAction)stopClicked:(id)sender {
    
    [romibo sendString:@"drive 0 0\r"];
}

-(IBAction)configClicked:(id)sender
{
    ConfigViewController* configVC = [[ConfigViewController alloc] initWithNibName:@"ConfigViewController" bundle:nil];
    [configVC view];
    [configVC setPopDelegate:self];
    [configVC configureButtonState:[romibo isConnected]];
    
    if ([romibo isConnected])
        [configVC setTextBoxText:[romibo ipAddress]];
    else [configVC setTextBoxText:@"169.254.1.1"];      
    
    
    configPopover = [[UIPopoverController alloc] initWithContentViewController:configVC];
    [configVC release];
    
    configPopover.delegate = self;
    
    CGRect popoverRect = [self.view convertRect:[sender frame] toView:[sender superview]];
    
    [configPopover presentPopoverFromRect:popoverRect inView:self.view permittedArrowDirections:UIPopoverArrowDirectionUp animated: YES];
}

-(void)connectClicked:(NSString*)ipaddr
{
    [romibo connectToIP:ipaddr];
    [self closePopup];
}

-(void)disconnectClicked
{
    [romibo disconnect];
    [self closePopup];
}

-(void)setConnectionStatus
{
    if (romibo.isConnected)
        [connectionLabel setText:@"Connection OK"];
    else
        [connectionLabel setText:@"Not Connected"];
}

-(void)closePopup
{    
    if ([configPopover isPopoverVisible])
        [configPopover dismissPopoverAnimated:YES];
    
    [configPopover release];
}


-(IBAction)buttonClicked:(id)sender
{
    
    NSString* btnText = [((UIButton *)sender).titleLabel text];
    NSLog(@"Button text: %@", btnText);
    
    NSString* btnCommand = [romiboCommands objectForKey:btnText];
    NSLog(@"Button command: %@", btnCommand);

    NSString* command;
    if ([btnCommand hasSuffix:@".wav"] || [btnCommand hasSuffix:@".WAV"])
        command = [@"say " stringByAppendingString:btnCommand];
    else command = btnCommand;
    
    NSString* fullCommand = [NSString stringWithFormat:@"%@\r", command];
    NSLog(@"Full command: %@", fullCommand);
    
    [romibo sendString:fullCommand];
}


-(void)popoverControllerDidDismissPopover:(UIPopoverController *)popoverController
{
    
}

- (void)commandSelected:(NSString *)cmd {
    
    [lastButtonClicked setTitle:cmd forState:UIControlStateNormal];
    
    [commandPickerPopover dismissPopoverAnimated:YES];
}

-(void)pickCommand:(id)sender {
    
    lastButtonClicked = sender;
    
    if (commandPicker == nil) {
                
        commandPicker = [[CommandPickerController alloc] 
                             initWithStyle:UITableViewStylePlain];
        
        [commandPicker setDelegate:self];
        [commandPicker setCommands:buttonLabels];
         
        commandPickerPopover = [[UIPopoverController alloc] 
                                    initWithContentViewController:commandPicker];  
        
    }
    
    [commandPickerPopover presentPopoverFromRect:[sender frame]
                          inView:[self view]      
                            permittedArrowDirections:UIPopoverArrowDirectionAny 
                            animated:YES];

}


-(IBAction)happyClicked:(id)sender
{
    
    NSString* emotion = @"emote 100 100\r";
    NSLog(@"Full command: %@", emotion);
    
    [romibo sendString:emotion];
}



-(IBAction)surprisedClicked:(id)sender
{
    
    NSString* emotion = @"emote 100 -100\r";
    NSLog(@"Full command: %@", emotion);
    
    [romibo sendString:emotion];
}


-(IBAction)angryClicked:(id)sender
{
    
    NSString* emotion = @"emote -100 100\r";
    NSLog(@"Full command: %@", emotion);
    
    [romibo sendString:emotion];
}


-(IBAction)sadClicked:(id)sender
{
    
    NSString* emotion = @"emote -100 -100\r";
    NSLog(@"Full command: %@", emotion);
    
    [romibo sendString:emotion];
}

- (void)dealloc {
    
    [romibo release];
    romibo = nil;
    
    [connectionLabel release];
    connectionLabel = nil;
    
    [cmdTimer invalidate];
    cmdTimer = nil;
    
    [romiboCommands release];
    romiboCommands = nil;
    
    [buttonLabels release];
    buttonLabels = nil;
    
    [commandPicker release];
    commandPicker = nil;
    
    
    [super dealloc];
}
@end
