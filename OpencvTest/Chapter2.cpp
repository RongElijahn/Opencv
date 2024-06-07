//
//  Chapter2.cpp
//  OpencvTest
//
//  Created by Alien on 2023-05-25.
//

#include "Chapter2.hpp"

using namespace std;
using namespace cv;
int g_slider_position=0;
int g_run=1, g_dontset = 0;
VideoCapture g_cap;


int showImage(){
    Mat image;
    image =imread("./source/Image.png");
    if (image.empty()){
        cout<<"Cannot open the file!"<<endl;
        return -1;
    }
    namedWindow("Image", 0);
    imshow("Image",image);
    cout<<"done!!"<<endl;
    waitKey(0);
    destroyWindow("Image");
    return 0;
}

int showVideo(){
    VideoCapture cap;
    cap.open("./source/Video.mp4");
    namedWindow("Video",WINDOW_AUTOSIZE);
    Mat frame;
    for(;;){
        cap>>frame; //equal to cap.read(frame)
        if(frame.empty()) break;
        imshow("Video",frame);
        if(waitKey(33)>=0 ) break;
    }
    destroyWindow("Video");
    return 0;
}

//callback routine when sliding the trackbar.
void onTrackbarSlide(int pos, void*){ //pos is correlted to the variable: g_slider_position.
    g_cap.set(CAP_PROP_POS_FRAMES,pos);
    if(!g_dontset)
        g_run=1;
    g_dontset = 0;
}
int showVideoTrackbar(){
    g_cap.open("./source/Video.mp4");
    namedWindow("Video2",WINDOW_AUTOSIZE);
    int frames=(int)g_cap.get(CAP_PROP_FRAME_COUNT);
    int tmpw=(int)g_cap.get(CAP_PROP_FRAME_WIDTH);
    int tmph=(int)g_cap.get(CAP_PROP_FRAME_HEIGHT);
    
    cout<<"Video has "<<frames<<", Frames of dimensions("<<tmpw<<","<<tmph<<")."<<endl;
    
    createTrackbar("Trackbar", "Video2",&g_slider_position,frames,onTrackbarSlide);
    Mat frame;
    for(;;){
        if(g_run!=0){
            g_cap>>frame;
            if(frame.empty()) break;
            int current_pos=(int)g_cap.get(CAP_PROP_POS_FRAMES);
            g_dontset=1;
            setTrackbarPos("Trackbar", "Video2", current_pos);
            imshow("Video2",frame);
            g_run=-1;
        }
        char c =(char)waitKey(10);
        if(c=='s'){
            g_run =1;
            cout<<"Singel step, run="<<g_run<<endl;
        }
        if(c=='r'){
            g_run=-1;
            cout<<"Run mode, run="<<g_run<<endl;
        }
        if(c==27) break;
        
    }
    //destroyWindow("Video2");
    return 0;
}

void smoothVideo(){
    Mat image=imread("./source/Image.png");
    namedWindow("in", WINDOW_AUTOSIZE);
    namedWindow("out", WINDOW_AUTOSIZE);
    imshow("in", image);
    Mat out;
    GaussianBlur(image, out, Size(5,5), 3,3);
    //GaussianBlur(out, out, Size(5,5), 3,3);
    imshow("out",out);
    waitKey(0);
}

void downSampleImage(){
    Mat image=imread("./source/Image.png");
    namedWindow("in", WINDOW_AUTOSIZE);
    namedWindow("out", WINDOW_AUTOSIZE);
    imshow("in", image);
    Mat out;
    pyrDown(image, out);
    imshow("out",out);
    waitKey(0);
}

void CannyImage(){
    Mat image=imread("./source/Image.png");
    namedWindow("in", WINDOW_AUTOSIZE);
    namedWindow("out", WINDOW_AUTOSIZE);
    imshow("in", image);
    Mat img_gry,img_canny;
    cvtColor(image,img_gry, COLOR_BGR2GRAY);
    imshow("img_gry",img_gry);
    Canny(img_gry,img_canny,10,100,3,true);
    imshow("Canny",img_canny);
    waitKey(0);
}


int openCamera(int n,const char * m[]){
    namedWindow("openCamera",WINDOW_AUTOSIZE);
    VideoCapture cap;
    if(n==1){
        cap.open(0);
    }else{
        cap.open(m[1]);
    }
    if(!cap.isOpened()){
        cerr<<"Cannot open capture!"<<endl;
        return -1;
    }
    Mat video;
    for(;;){
        cap>>video;
        if(video.empty()) break;
        imshow("openCamera", video);
        if(waitKey(33)>=0 ) break;
    }
    return 0;
}

int writingToAnAVIFile(int n,const char * m[]){
    namedWindow("video",WINDOW_AUTOSIZE);
    namedWindow("Log_Polar",WINDOW_AUTOSIZE);
    VideoCapture cap;
    cap.open(0);
    double fps=cap.get(CAP_PROP_FPS);
    cv::Size size((int)cap.get(CAP_PROP_FRAME_WIDTH),(int)cap.get(CAP_PROP_FRAME_HEIGHT));
    
    VideoWriter writer;
    writer.open(m[2],VideoWriter::fourcc('M','J','P','G'),fps,size);
    Mat logpokar_frame,bgr_frame;
    for(;;){
        cap>>bgr_frame;
        if(bgr_frame.empty()) break;
        imshow("video", bgr_frame);
        logPolar(bgr_frame, logpokar_frame, Point2f(bgr_frame.cols/2,bgr_frame.rows/2), 40, WARP_FILL_OUTLIERS);
        imshow("Log_Polar", logpokar_frame);
        writer << logpokar_frame;
        char c = waitKey(10);
        if(c == 27) break;
    }
    
    cap.release();
    return 0;
}
