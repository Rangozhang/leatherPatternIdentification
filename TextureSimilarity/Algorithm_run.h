//
//  Algorithm_run.h
//  TextureSimilarity
//
//  Created by 张雨 on 3/24/15.
//  Copyright (c) 2015 Zhang, Yu. All rights reserved.
//

#ifndef __TextureSimilarity__Algorithm_run__
#define __TextureSimilarity__Algorithm_run__

#include "Header.h"
#include "Texture.h"
#include "Color.h"

bool operator < (pair<int, float> temp1, pair<int, float> temp2);

void quick_sort(pair<int, float> arr[], int begin, int end);

void algorithm_run(string, int[]);

#endif /* defined(__TextureSimilarity__Algorithm_run__) */
