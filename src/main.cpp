/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  main src file, contains entry point
 *
 *        Version:  1.0
 *        Created:  10/13/2014 02:24:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samy Shihata (sshihata), Mohamed Ashraf (m0hamed), Hossam Ahmed (hoss93)
 *   Organization:  GUC
 *
 * =====================================================================================
 */

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "utils.h"
#include "sift.h"
#include "globals.h"
#include <cmath>

using std::cout;
using std::endl;
using std::vector;
using cv::Mat;
using cv::KeyPoint;
using std::vector;
using cv::imread;

int main (int argc, char**argv) {
  if(argc != 2)
  {
    cout << " Usage: cybervis ImageToLoadAndDisplay" << endl;
    return -1;
  }

  Mat image;
  image = imread(argv[1], 0);

  if(!image.data)
  {
    cout << "Could not open or find the image" << endl ;
    return -1;
  }

  cv::namedWindow("Cybervis", cv::WINDOW_AUTOSIZE);// Create a window for display.
  imshow("Cybervis", image);

  vector< KeyPoint > keypoints;
  // Calls main SIFT function on a image and tells it to convert the matrix to
  // double and normalize to the range [0,1] before running SIFT
  findSiftInterestPoint<double>(image, keypoints, CV_64FC1, true);

  return 0;
}
