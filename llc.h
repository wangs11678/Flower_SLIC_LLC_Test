#ifndef LLC_H_INCLUDED
#define LLC_H_INCLUDED

#include <opencv2/opencv.hpp>

//生成采样点网格
void meshgrid(const cv::Range &xgv, const cv::Range &ygv, int step, cv::Mat &X, cv::Mat &Y);

//计算feaSetX, feaSetY
void calculateSiftXY_opencv(int width, int height, int patchSize, int binSize, int step, cv::Mat &feaSet_x, cv::Mat &feaSet_y);
void calculateSiftXY_vlfeat(int width, int height, int patchSize, int binSize, int step, cv::Mat &feaSet_x, cv::Mat &feaSet_y);

void llc_coding(cv::Mat &B, cv::Mat &X, cv::Mat &llcCodes, int knn);

void llc_pooling(cv::Mat &tdictionary,
                 cv::Mat &tinput,
                 cv::Mat &tllccodes,
                 cv::Mat &llcFeature,
                 cv::Mat &feaSet_x,
                 cv::Mat &feaSet_y,
                 int width,
                 int height
                );

void llc_coding_pooling(cv::Mat &img,
						cv::Mat &dsiftFeature,
						cv::Mat &dictionary,
						cv::Mat &llcFeature,
                        int knn,
                        int step,
                        int binSize,
                        int patchSize
                       );

#endif // LLC_H_INCLUDED
