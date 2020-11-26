#ifndef HELLO_OPENCV_CC
#define HELLO_OPENCV_CC

#include <string>
#include <iostream>

#include <glog/logging.h>
#include <gflags/gflags.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

using std::string;

DEFINE_string(name, "Yoyo", "Your name to greet you.");

// Draws a good looking rounded rectangle
void rounded_rectangle(
    cv::Mat &src, cv::Point topLeft, cv::Point bottomRight, const cv::Scalar lineColor,
    const int thickness, const int cornerRadius, const int lineType)
{
    /* corners:
    * p1 - p2
    * |     |
    * p4 - p3
    */
    cv::Point p1 = topLeft;
    cv::Point p2 = cv::Point(bottomRight.x, topLeft.y);
    cv::Point p3 = bottomRight;
    cv::Point p4 = cv::Point(topLeft.x, bottomRight.y);

    // draw straight lines
    cv::line(src, cv::Point(p1.x + cornerRadius, p1.y), cv::Point(p2.x - cornerRadius, p2.y), lineColor, thickness, lineType);
    cv::line(src, cv::Point(p2.x, p2.y + cornerRadius), cv::Point(p3.x, p3.y - cornerRadius), lineColor, thickness, lineType);
    cv::line(src, cv::Point(p4.x + cornerRadius, p4.y), cv::Point(p3.x - cornerRadius, p3.y), lineColor, thickness, lineType);
    cv::line(src, cv::Point(p1.x, p1.y + cornerRadius), cv::Point(p4.x, p4.y - cornerRadius), lineColor, thickness, lineType);

    // draw arcs
    cv::ellipse(src, p1 + cv::Point(cornerRadius, cornerRadius), cv::Size(cornerRadius, cornerRadius), 180.0, 0, 90, lineColor, thickness, lineType);
    cv::ellipse(src, p2 + cv::Point(-cornerRadius, cornerRadius), cv::Size(cornerRadius, cornerRadius), 270.0, 0, 90, lineColor, thickness, lineType);
    cv::ellipse(src, p3 + cv::Point(-cornerRadius, -cornerRadius), cv::Size(cornerRadius, cornerRadius), 0.0, 0, 90, lineColor, thickness, lineType);
    cv::ellipse(src, p4 + cv::Point(cornerRadius, -cornerRadius), cv::Size(cornerRadius, cornerRadius), 90.0, 0, 90, lineColor, thickness, lineType);
}

int main(int argc, char **argv)
{

    FLAGS_logtostderr = 1;
    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    LOG(INFO) << "Hello " << FLAGS_name;

    // Using opencv, process webcam video &
    // overlay boxes in random colors.
    cv::VideoCapture cap(0);
    cv::Mat frame;
    cv::RNG rng(12345);
    while (cap.isOpened())
    {
        cap.read(frame);
        cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        rounded_rectangle(frame, cv::Point(100, 100), cv::Point(500, 500), color, 2, 2, 1);
        cv::imshow("frame", frame);
        char c = (char)cv::waitKey(1);
        if (c == 27)
            break;
    }

    return 0;
}
#endif
