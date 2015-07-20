//
//  Texture.cpp
//  TextureSimilarity
//
//  Created by 张雨 on 3/24/15.
//  Copyright (c) 2015 Zhang, Yu. All rights reserved.
//

#include "Texture.h"

bool texture_similarity_init(string comparer, Mat* des){
    const char* path ="/Users/Rango/Documents/coding/XCode/TextureSimilarity_data/";
    char buff[512];
    sprintf(buff, "%s%s.jpg", path, comparer.c_str());
    IplImage* _src1 = cvLoadImage(buff, CV_LOAD_IMAGE_GRAYSCALE);
    IplImage* __src1 = cvCreateImage(cvSize(600, (600.0/_src1->width)*_src1->height), _src1->depth, _src1->nChannels);
    cvResize(_src1, __src1);
    Mat src1 = Mat(__src1);
    
    if (!src1.data) {
        cout << "Error reading images" << endl;
    }
    
    SiftFeatureDetector detector;
    vector<KeyPoint> kp1;          //SIFT feature points
    
    detector.detect(src1, kp1);
    
    if (!kp1.size()) {
        return false;
    }
    
    SiftDescriptorExtractor extractor;
    extractor.compute(src1,kp1,*des);
    return true;
}

int texture_save_for_each(Mat* des2, string comparee){
    const char* path ="/Users/Rango/Documents/coding/XCode/TextureSimilarity_data/";
    char buff[512];
    clock_t begin1 = clock();
    sprintf(buff, "%s%s.jpg", path, comparee.c_str());
    
    IplImage* _src1 = cvLoadImage(buff, CV_LOAD_IMAGE_GRAYSCALE);
    IplImage* __src1 = cvCreateImage(cvSize(600, (600.0/_src1->width)*_src1->height), _src1->depth, _src1->nChannels);
    cvResize(_src1, __src1);
    
    Mat src2 = Mat(__src1);
    cout << comparee.c_str() << ":" << endl;
    clock_t begin2 = clock();
    cout << "Time of Resize: " << begin2 - begin1 << endl;
    
    if (!src2.data) {
        cout << "Error reading images" << endl;
    }
    
    SiftFeatureDetector detector;
    vector<KeyPoint> kp2;          //SIFT feature points
    
    detector.detect(src2, kp2);
    
    if (!kp2.size()) {
        return -1;
    }
    
    SiftDescriptorExtractor extractor;
    extractor.compute(src2,kp2,*des2);
    
    return (int)kp2.size();
}

void texture_save(){

    for (int i = 1; i < 25; i++) {
        Mat* des2 = new Mat;
        char name[10];
        sprintf(name, "%d", i);
        string name_(name);
        int result = texture_save_for_each(des2, name_);
        if (result >= 0) {
            FileStorage fs("/Users/Rango/Documents/coding/XCode/leatherPatternIdentification/TextureSimilarity_data/data_"+name_+".xml", FileStorage::WRITE);
            fs<<"data_"+name_<<*des2;
            fs<<"size_"+name_<<result;
            fs.release();
        }
    }
    
    
}


float texture_similarity(Mat des1, string comparee){
    
    Mat des2;
    FileStorage fs("/Users/Rango/Documents/coding/XCode/leatherPatternIdentification/TextureSimilarity_data/data_"+comparee+".xml", FileStorage::READ);
    
    int sum_size = -1;
    
    if (!fs.isOpened()) {
        int mmm = 0;
        mmm ++;
        return 100;
    }

    clock_t begin1 = clock();
    fs["size_"+comparee] >> sum_size;
    if (sum_size == 0) {
        return 100;
    }else{
        fs["data_"+comparee] >> des2;
    }
    clock_t begin2 = clock();
    cout << "Reading time: " << begin2 - begin1 << endl;
    BFMatcher matcher(NORM_L2);
    vector<vector<DMatch>> matches;
    matcher.radiusMatch(des2,des1,matches,THRESHOLD);
    cout << "Matching time: " << clock() - begin2 << endl;
    
    vector<vector<DMatch>>::iterator m_ptr;
    float matches_sum = 0;
    for (m_ptr = matches.begin(); m_ptr != matches.end(); m_ptr++) {
        matches_sum += (m_ptr->size() == 0)?0:1;
    }
    
    cout << matches_sum << " / " << sum_size << " = " << matches_sum/sum_size << endl;
    return 1 - matches_sum/sum_size;///kp2.size(); //average posibility of finding a match for a feature point
}


