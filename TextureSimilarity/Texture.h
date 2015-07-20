//
//  Texture.h
//  TextureSimilarity
//
//  Created by 张雨 on 3/24/15.
//  Copyright (c) 2015 Zhang, Yu. All rights reserved.
//

#ifndef __TextureSimilarity__Texture__
#define __TextureSimilarity__Texture__

#include "header.h"

bool texture_similarity_init(string comparer, Mat* des);

float texture_similarity(Mat des1, string comparee);

void texture_save();

#endif /* defined(__TextureSimilarity__Texture__) */
