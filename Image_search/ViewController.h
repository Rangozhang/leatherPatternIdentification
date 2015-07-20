//
//  ViewController.h
//  Image_search
//
//  Created by 张雨 on 3/25/15.
//  Copyright (c) 2015 Zhang, Yu. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ViewController : NSViewController{
    int result[25];
}

@property NSString* m_text;

@property (weak) IBOutlet NSButton *openButton;

@property (weak) IBOutlet NSTextField *pathText;

@property (weak) IBOutlet NSImageView *searchingImage;

@property (weak) IBOutlet NSImageView *img1;
@property (weak) IBOutlet NSImageView *img2;
@property (weak) IBOutlet NSImageView *img3;
@property (weak) IBOutlet NSImageView *img4;
@property (weak) IBOutlet NSImageView *img5;
@property (weak) IBOutlet NSImageView *img6;
@property (weak) IBOutlet NSImageView *img7;
@property (weak) IBOutlet NSImageView *img8;
@property (weak) IBOutlet NSImageView *img9;

@end

