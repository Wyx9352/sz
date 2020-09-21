//
//  main.cpp
//  opencv
//
//  Created by 王艺璇 on 2020/9/20.
//  Copyright © 2020 王艺璇. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdlib>

using namespace std;
using namespace cv;


int main()
{
    Mat frame, yuv;

    VideoCapture capture;
    int w = 320;
    int h = 240;
    capture.open(0);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,w);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,h);

    /*
    VideoCapture capture;
    int w = 1280;
    int h = 720;
    string filename = "./xx.mp4";
    capture.open(filename);
    */
    if(!capture.isOpened())
    {
        cerr << "No camera or video input!\n";
        return -1;
    }

    int bufLen = w*h*3/2;
    unsigned char* pYuvBuf = new unsigned char[bufLen];
    FILE* pFileOut = fopen("/Users/wyx/Desktop/output.yuv", "wb");
    if (!pFileOut)
    {
        printf("pFileOut open error \n");
        system("pause");
        exit(-1);
    }
    //int cnt = 0;

    while(true)
    {
        capture >> frame;
        if(frame.empty())
            continue;
        imshow("origin",frame);
        cvtColor(frame,yuv,CV_RGB2YUV_I420);

        imshow("yuv",yuv);

        memcpy(pYuvBuf, yuv.data, bufLen*sizeof(unsigned char));

        fwrite(pYuvBuf, bufLen*sizeof(unsigned char), 1, pFileOut);


        if(cvWaitKey(10) == 'q')
            break;
    }

    fclose(pFileOut);
    delete[] pYuvBuf;
    system("pause");
    return 0;
}

//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//using namespace std;
//CvVideoWriter* video=NULL;
//  //FILE* pFile;
//FILE* pFile = fopen("/Users/wyx/Desktop/output2.yuv", "wb");
//
//
//IplImage* RgbToYUV420(IplImage* pImage)
//{
////cout<<"number of channels:"<<pImage->nChannels<<"  width step:"<<pImage->widthStep<<endl;
//cout<<"width:"<<pImage->width<<"  height:"<<pImage->height<<endl;
////cout<<"order of data:"<<pImage->dataOrder<<endl;
////cout<<"channel sequence:"<<pImage->channelSeq<<endl;*/
//
//
//int width=pImage->width;
//int height=pImage->height;
//int yuvSize=width*height*3/2;
//char* pRgbBuf=pImage->imageData;
//char* pYBuf,*pUBuf,*pVBuf;
//char* pYUVBuf;
//
//
//pYUVBuf=(char*)malloc(yuvSize);
//pYBuf=pYUVBuf;
//memset(pYBuf,0,yuvSize);
////pUBuf=pYBuf+width*height;
//
////yuv格式按YUV排列
//pUBuf=pYBuf+width*height;
//pVBuf=pUBuf+width*height/4;
//
//unsigned char r,g,b;
//unsigned char y,u,v;
//
//for(int i=0;i<height;i++)
//for(int j=0;j<width;j++)
//{
//b=*(pRgbBuf);
//g=*(pRgbBuf+1);
//r=*(pRgbBuf+2);
///*y = (unsigned char)(  0.299* r + 0.587* g +  0.114 * b )   ;
//            u = (unsigned char)( -0.169 * r -  0.332 * g + 0.500 * b + 128)  ;
//            v = (unsigned char)( 0.500 * r +0.419 * g -  0.0813 * b + 128);  */
//
//
////这才是正确的公式？？？？
//y=uchar(0.257*r + 0.504*g + 0.098*b + 16);
//u=uchar(-0.148*r - 0.291*g + 0.439*b + 128);
//v=uchar(0.439*r - 0.368*g - 0.071*b + 128);
//
//
///*y=0.299*r + 0.587*g + 0.114*b;
//            u=(r-y)*0.713 + 128;
//            v=(b-y)*0.564 + 128;*/
//
//
//if(y>255)y=255;
//else if(y<0)y=0;
//if(u>255)u=255;
//else if(u<0)u=0;
//if(v>255)v=255;
//else if(v<0)v=0;
//*(pYBuf++)=y;
///**(pVBuf++)=v;
//*(pUBuf++)=u;*/
//
//
//pRgbBuf+=3;
///**(pRgbBuf++)=y;
//*(pRgbBuf++)=v;
//*(pRgbBuf++)=u;*/
//
//if(i%2==0&&j%2==0)
//{
////对uv取样
//*(pVBuf++)=v;
//*(pUBuf++)=u;
//}
//}
//
////pImage->imageData=pYUVBuf;
///*IplImage* yimg = cvCreateImageHeader(cvSize(width, height),IPL_DEPTH_8U,1);
//cvSetData(yimg,pYUVBuf,width);*/
//
////pImage->imageSize=yuvSize;
//
//
////fprintf(pFile,"%s",pYUVBuf);
//fwrite(pYUVBuf,1,yuvSize,pFile);
//
//
////pImage->imageData=pYBuf;
////pImage->imageDataOrigin=pYBuf;
///*strcpy_s(pImage->channelSeq,"YVU");
//pImage->dataOrder=1;*/
//
//
//return pImage;
//}
//
//
//
//int main( int argc, char** argv )
//{
//CvCapture* capture = 0;
//IplImage* frame = 0;
//int frameWidth=320;
//int frameHeight=240;
//capture = cvCaptureFromCAM( 0 );
////capture = cvCaptureFromAVI("1.wmv");//播放视频 就换成这句
//video=cvCreateVideoWriter("/Users/wyx/Desktop/out2.yuv",CV_FOURCC('I','4','2','0'),15,
//cvSize(frameWidth,frameHeight));
//if(video) //如果能创建CvVideoWriter对象则表明成功
//{
//cout<<"VideoWriter has created."<<endl;
//}
//fopen("/Users/wyx/Desktop/output2.yuv","wb");
////fopen_s(&pFile,"yuvvideo.yuv","wb");
//int fps=15; //捕捉帧率
////double fps = cvGetCaptureProperty(capture,CV_CAP_PROP_FPS); //视频帧率
//
//
//CvVideoWriter* writer = 0; //保存就加上这句
//int isColol=1;
//int frameW=320;
//int frameH=240;
//int n=1;
//writer=cvCreateVideoWriter("out.avi",CV_FOURCC('M', 'P', '4', '2'),fps,cvSize(frameW,frameH),isColol);
//
//
//cvNamedWindow( "摄像头", 1 );
//
//
////for(int i=0;i<50;i++) //2秒
//for(;;) //一直读
//{
//frame = cvQueryFrame( capture );
//
//    IplImage* ptmp = frame;
//cout<<"width0:"<<ptmp->width<<"  height0:"<<ptmp->height<<endl;
//cvWriteFrame(writer,frame );
//
//
//cvShowImage( "摄像头", frame ); //显示一帧图像
//frame=RgbToYUV420(frame); //转换
//n=cvWriteFrame(video,frame);
//
//
//cvWaitKey(1000 / fps);//视频速度
//}
//
//
//cvReleaseVideoWriter(&writer);
//cvReleaseImage(&frame);
//cvReleaseCapture( &capture );
//cvDestroyWindow("摄像头");
//return 0;
//}
