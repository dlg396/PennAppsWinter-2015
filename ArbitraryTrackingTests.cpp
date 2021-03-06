#include "ArbitraryTracking.h"

void num2str(char *str, int length, int num) {
    for(int i = 0; i < length-1; i++) {
        str[length-i-2] = '0'+num%10;
        num /= 10;
    }
    str[length-1] = 0;
}

int main(int argc, char *argv[]) {
    char *path = "ball/";
    char *ext = "png";
    int numLength = 8;
    char numString[numLength+1];
    char filename[255];
    int start = 1;
    int end = 603;
    cv::Point2f initTopLeft(195,110);
    cv::Point2f initBottomDown(254,169);

    ArbitraryTracking cmt;
    for(int i = start; i <= end; i++) {
        num2str(numString, numLength+1, i);
		printf("%s",numString);
        sprintf(filename, "%s%s.%s", path, numString, ext);

        #ifdef DEBUG_MODE
        qDebug() << filename;
        #endif

        cv::Mat img = cv::imread(filename);
        cv::Mat im_gray;
        cv::cvtColor(img, im_gray, CV_RGB2GRAY);

        if(i == start)
            cmt.initialise(im_gray, initTopLeft, initBottomDown);
        cmt.processFrame(im_gray);

        for(int i = 0; i<cmt.trackedKeypoints.size(); i++)
            cv::circle(img, cmt.trackedKeypoints[i].first.pt, 3, cv::Scalar(255,255,255));
        cv::line(img, cmt.topLeft, cmt.topRight, cv::Scalar(255,255,255));
        cv::line(img, cmt.topRight, cmt.bottomRight, cv::Scalar(255,255,255));
        cv::line(img, cmt.bottomRight, cmt.bottomLeft, cv::Scalar(255,255,255));
        cv::line(img, cmt.bottomLeft, cmt.topLeft, cv::Scalar(255,255,255));
		
        imshow("frame", img);
        cv::waitKey(1);
    }
    return 0;
}
