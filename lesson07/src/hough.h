#pragma once

#include <opencv2/highgui.hpp>

cv::Mat buildHough(cv::Mat sobel);

const int max_theta = 360;