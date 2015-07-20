//
//  Color.h
//  TextureSimilarity
//
//  Created by 张雨 on 3/24/15.
//  Copyright (c) 2015 Zhang, Yu. All rights reserved.
//

#ifndef __TextureSimilarity__Color__
#define __TextureSimilarity__Color__

#include "header.h"

void color_similarity_init(string comparer, CvScalar center_values[]);

float m_distance(CvScalar m1, CvScalar m2);

float min_distance(CvScalar center_values[], CvScalar s);

float color_similarity(CvScalar center_values[], string comparee);

#endif /* defined(__TextureSimilarity__Color__) */
