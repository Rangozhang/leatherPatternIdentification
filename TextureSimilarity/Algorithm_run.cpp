//
//  Algorithm_run.cpp
//  TextureSimilarity
//
//  Created by 张雨 on 3/24/15.
//  Copyright (c) 2015 Zhang, Yu. All rights reserved.
//

#include "Algorithm_run.h"

bool operator < (pair<int, float> temp1, pair<int, float> temp2){
    return temp1.second < temp2.second;
}

void quick_sort(pair<int, float> arr[], int begin, int end){
    if (begin < end) {
        int i = begin, j = end;
        pair<int, float> pivet = arr[i];
        while (i < j) {
            while (i < j && pivet < arr[j]) {
                j--;
            }
            if (i < j) {
                swap(arr[i++], arr[j]);
            }
            while (i < j && arr[i] < pivet) {
                i++;
            }
            if (i < j) {
                swap(arr[j--], arr[i]);
            }
        }
        arr[i] = pivet;
        quick_sort(arr, begin, i-1);
        quick_sort(arr, i+1, end);
    }
}

//mutex m_mutex;
//#include <unistd.h>

void thread_func_color(string name, float* result, CvScalar center_values[]){
    *result = color_similarity(center_values, name);
}

void thread_func_texture(string name, float* result, Mat des){
    *result += TEXTURE_WEIGHT * texture_similarity(des, name);
}

clock_t begin_c;
clock_t end_c;
clock_t begin_t, end_t;

void algorithm_run_color(string comparer, float arr[]){
    begin_c = clock();
    cout << "Color Similarity comparing..." << endl;
    CvScalar center_values[NCLUSTER];

    
    color_similarity_init(comparer, center_values);
    
    ///////////////////
    thread t[24];
    for (int i = 1; i < 25; i++) {
        char name[10];
        sprintf(name, "%d", i);
        string name_(name);
        t[i-1] = thread(thread_func_color, name_, &arr[i], center_values);
    }
    
    for (int i = 1; i < 25; i++) {
        t[i-1].join();
    }
    end_c = clock();
}

void algorithm_rum_texture(string comparer, float arr[]){
    begin_t = clock();
    cout << "Texture Similarity comparing..." << endl;
    Mat* des = new Mat;
    
    thread t[24];
    if (texture_similarity_init(comparer, des)) {
        for (int i = 1; i < 25; i++) {
            char name[10];
            sprintf(name, "%d", i);
            string name_(name);
            t[i-1] = thread(thread_func_texture, name_, &arr[i], *des);
            //            result[i].second += TEXTURE_WEIGHT * texture_similarity(*des, name_);
        }
        for (int i = 1; i < 25; i++){
            t[i-1].join();
        }
    }
    end_t = clock();
}

#include <unistd.h>

void algorithm_run(string comparer, int* rtn_arr) {
    clock_t begin = clock();
    
    pair<int, float> result[25] = {{0,0}};
    
    float color_arr[25] = {0.0};
    float texture_arr[25] = {0.0};
    
    thread color_thread = thread(algorithm_run_color, comparer, color_arr);
    thread texture_thread = thread(algorithm_rum_texture, comparer, texture_arr);
    color_thread.join();
    texture_thread.join();
    
    
    
    float max = 0;
    
    for (int i = 1; i < 25; i++) {
        result[i].first = i;
        result[i].second = color_arr[i];
        if (result[i].second > max) {
            max = result[i].second;
        }
    }
    
    for (int i = 1; i < 25; i++) {
        result[i].second = COLOR_WEIGHT * (result[i].second/max) + TEXTURE_WEIGHT * texture_arr[i];
    }
    
    quick_sort(result, 1, 24);
    
    for (int i = 1; i < 25; i++) {
        cout<<result[i].first<<".jpg : "<<result[i].second << endl;
        rtn_arr[i] = result[i].first;
    }
    
    //60130375
    //44675754
    //70936269
    //14104269
    cout << "Color Time: " << (end_c - begin_c)/CLOCKS_PER_SEC << endl;
    cout << "Texture Time: " << (end_t - begin_t)/CLOCKS_PER_SEC << endl;
    cout << "Sum Time: " << (clock() - begin)/CLOCKS_PER_SEC << endl;
    return;
}
