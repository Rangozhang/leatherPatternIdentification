//
//  ViewController.m
//  Image_search
//
//  Created by 张雨 on 3/25/15.
//  Copyright (c) 2015 Zhang, Yu. All rights reserved.
//

#import "ViewController.h"
#include "Algorithm_run.h"

@implementation ViewController

- (IBAction)openButtonPressed:(id)sender {
    _m_text = _pathText.stringValue;
    NSLog(@"%@", _m_text);
    [_searchingImage setImage: [NSImage imageNamed:_m_text]];
}

- (IBAction)searchButtonPressed:(id)sender {
    algorithm_run(_m_text.UTF8String, result);
    NSLog(@"%d", result[3]);
    [_img1 setImage: [NSImage imageNamed:[NSString stringWithFormat:@"%d", result[1]]]];
    [_img2 setImage: [NSImage imageNamed:[NSString stringWithFormat:@"%d", result[2]]]];
    [_img3 setImage: [NSImage imageNamed:[NSString stringWithFormat:@"%d", result[3]]]];
    [_img4 setImage: [NSImage imageNamed:[NSString stringWithFormat:@"%d", result[4]]]];
    [_img5 setImage: [NSImage imageNamed:[NSString stringWithFormat:@"%d", result[5]]]];
    [_img6 setImage: [NSImage imageNamed:[NSString stringWithFormat:@"%d", result[6]]]];
    [_img7 setImage: [NSImage imageNamed:[NSString stringWithFormat:@"%d", result[7]]]];
    [_img8 setImage: [NSImage imageNamed:[NSString stringWithFormat:@"%d", result[8]]]];
    [_img9 setImage: [NSImage imageNamed:[NSString stringWithFormat:@"%d", result[9]]]];
}

- (IBAction)initButtonPressed:(id)sender {
    texture_save();
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

@end
