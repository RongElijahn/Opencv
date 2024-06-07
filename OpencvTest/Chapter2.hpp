//
//  Chapter2.hpp
//  OpencvTest
//
//  Created by Alien on 2023-05-25.
//

#ifndef Chapter2_hpp
#define Chapter2_hpp

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
int showImage();
int showVideo();
void onTrackbarSlide(int pos, void*);
int showVideoTrackbar();
void smoothVideo();
void downSampleImage();
void CannyImage();
int openCamera(int n,const char * m[]);
int writingToAnAVIFile(int n,const char * m[]);
#endif /* Chapter2_hpp */
