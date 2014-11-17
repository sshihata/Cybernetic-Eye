/*
 * =====================================================================================
 *
 *       Filename:  sift.cpp
 *
 *    Description:  functions specific to sift algorithm implementation
 *
 *        Version:  1.0
 *        Created:  11/14/2014 08:23:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samy Shihata (sshihata), 
 *   Organization:  GUC
 *
 * =====================================================================================
 */

#include "sift.h"
#include "globals.h"

using std::vector;
using cv::Mat;
using cv::KeyPoint;
using cv::Rect;

template<typename T>
void getScaleSpaceExtrema(const vector< vector< Mat > >& pyr, 
    vector< KeyPoint >& keypoints) {
  int octaves = (int) pyr.size();
  int scales = (int) pyr[0].size() - 1;
  for (int i = 0; i < octaves; i++)
    for (int j = 1; j < scales; j++) {
      vector< Mat > sample_scales;
      sample_scales.push_back(pyr[i][j]);
      sample_scales.push_back(pyr[i][j-1]);
      sample_scales.push_back(pyr[i][j+1]);
      getExtrema<T>(sample_scales, i, keypoints);
    }
}

template void getScaleSpaceExtrema<int>(const vector< vector< Mat > >&,
    vector< KeyPoint >&);
template void getScaleSpaceExtrema<uchar>(const vector< vector< Mat > >&,
    vector< KeyPoint >&);
template void getScaleSpaceExtrema<double>(const vector< vector< Mat > >&,
    vector< KeyPoint >&);

template<typename T>
void getExtrema(const vector< Mat >& sample_scales, const int octave,
    vector< KeyPoint >& keypoints) {
  for (int i = 1; i < sample_scales[0].rows-1; i++) {
    for (int j = 1; j < sample_scales[0].cols-1; j++) {
      T pixel = sample_scales[0].at<T>(i, j);
      Rect r(j-1, i-1, 3, 3);
      bool not_min = false, not_max = false;
      int pi = 0, pj = 0, sample = 0;
      Mat window = sample_scales[sample](r);
      while(!(not_min && not_max)) {
        T neig = window.at<T>(pi, pj++);
        not_min = neig < pixel || not_min;
        not_max = neig > pixel || not_max;
        if (pj == window.cols) {
          pi++; pj = 0;
          if (pi == window.rows) {
            sample++; pi = 0;
            if (sample == (int)sample_scales.size())
              break;
            window = sample_scales[sample](r);
          }
        }
      }
      if (!not_min || !not_max){
        keypoints.push_back(KeyPoint(j, i, 0,-1.0f, pixel, octave, -1));
      }
    }
  }
}

template void getExtrema<int>(const vector< Mat >&, const int, vector< KeyPoint >& );
template void getExtrema<uchar>(const vector< Mat >&, const int, vector< KeyPoint >& );
template void getExtrema<double>(const vector< Mat >&, const int, vector< KeyPoint >& );