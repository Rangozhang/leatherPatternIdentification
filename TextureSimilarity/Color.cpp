//
//  Color.cpp
//  TextureSimilarity
//
//  Created by 张雨 on 3/24/15.
//  Copyright (c) 2015 Zhang, Yu. All rights reserved.
//

#include "Color.h"

void color_similarity_init(string comparer, CvScalar center_values[]){
    const char* path ="/Users/Rango/Documents/coding/XCode/TextureSimilarity_data/";
    char buff[512];
    sprintf(buff, "%s%s.jpg", path, comparer.c_str());
    IplImage* src1 = cvLoadImage(buff, CV_LOAD_IMAGE_COLOR);
    
    //Kmeans
    CvMat *samples = cvCreateMat(NSAMPLE, 1, CV_32FC3);
    CvMat *clusters = cvCreateMat(NSAMPLE, 1, CV_32SC1);
    
    uchar* data = (uchar*)src1->imageData;
    int step = src1->widthStep/sizeof(uchar);
    int channels = src1->nChannels;
    CvMat *m_centers = cvCreateMat(NCLUSTER, 1, CV_32FC3);
    
    CvRNG random = cvRNG(cvGetTickCount());
    
    //printf("%d", cvRandInt(&random)%src1->height);

    for (int k = 0; k < NSAMPLE; k++) {
        int i = cvRandInt(&random)%src1->height;
        int j = cvRandInt(&random)%src1->width;
        CvScalar s;
        s.val[0] = (double)data[i*step+j*channels+0];
        s.val[1] = (double)data[i*step+j*channels+1];
        s.val[2] = (double)data[i*step+j*channels+2];
        cvSet2D(samples, k, 0, s);
    }

    //CvRNG* rng;

    cout << "Kmeans..." << endl;
    
    cvKMeans2(samples, NCLUSTER, clusters, TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0)
              , 1, &random ,KMEANS_PP_CENTERS, m_centers);
    
    for (int i = 0; i < NCLUSTER; i++) {
        center_values[i].val[0] = (float)cvGet2D(m_centers, i, 0).val[0];
        center_values[i].val[1] = (float)cvGet2D(m_centers, i, 0).val[1];
        center_values[i].val[2] = (float)cvGet2D(m_centers, i, 0).val[2];
    }
    
    for (int i = 0; i < NCLUSTER; i++) {
        cout << center_values[i].val[0] << " " << center_values[i].val[1] << " " << center_values[i].val[2] << endl;
    }
}

float m_distance(CvScalar m1, CvScalar m2){
    return abs(m1.val[0]-m2.val[0]) + abs(m1.val[1]-m2.val[1]) + abs(m1.val[2]-m2.val[2]);
}

float min_distance(CvScalar center_values[], CvScalar s){
    float min = 100000;
    for (int i = 0; i < NCLUSTER; i++) {
        float temp = m_distance(s, center_values[i]);
        min = (temp < min)? temp:min;
    }
    return min;
}

float color_similarity(CvScalar center_values[], string comparee) {
    const char* path ="/Users/Rango/Documents/coding/XCode/TextureSimilarity_data/";
    char buff[512];
    sprintf(buff, "%s%s.jpg", path, comparee.c_str());
    IplImage* src1 = cvLoadImage(buff, CV_LOAD_IMAGE_COLOR);
    
    int k = 0;
    float result = 100;
    
    uchar* data = (uchar*)src1->imageData;
    int step = src1->widthStep/sizeof(uchar);
    int channels = src1->nChannels;
    for (int i = 5; i < src1->height; i+=src1->height/10) {
        for (int j = 5; j < src1->width; j+=src1->width/10) {
            CvScalar s;
            s.val[0] = (double)data[i*step+j*channels+0];
            s.val[1] = (double)data[i*step+j*channels+1];
            s.val[2] = (double)data[i*step+j*channels+2];
            result = (k*result + min_distance(center_values, s))/(1+k);
            k++;
        }
    }
    
    return result;
}