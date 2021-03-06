#include "dsift.h"

using namespace std;
using namespace cv;

//利用opencv自带的sift特征提取
void llc_extract_dsift_feature(Mat &img, int step, int patchSize, Mat &dsiftFeature)
{
	SiftDescriptorExtractor sift;
	vector<KeyPoint> keypoints; // keypoint storage

    int width = img.cols;
    int height = img.rows;

    int remX = (width - patchSize) % step;
	int offsetX = floor(remX/2) + 1;
	int remY = (height - patchSize) % step;
	int offsetY = floor(remY/2) + 1;

    /*
     * 利用opencv自带的提取sift特征代码，
     * 自定义KeyPoint(关键点)，改编成
     * dense sift特征提取
     */
	// manual keypoint grid
	for (int y=offsetY+patchSize/2; y<=height-patchSize/2+1; y+=step)
    {
		for (int x=offsetX+patchSize/2; x<=width-patchSize/2+1; x+=step)
		{
			// x,y,radius
			keypoints.push_back(KeyPoint(float(x), float(y), float(step)));
		}
	}
	sift.compute(img, keypoints, dsiftFeature);
}


//利用vlfeat库提取dsift特征
void llc_extract_dsift_feature_vlfeat(Mat &img, int step, int binSize, Mat &dsiftFeature)
{
	VlDsiftFilter * vlf = vl_dsift_new_basic(img.rows, img.cols, step, binSize);
	// transform image in cv::Mat to float vector
	std::vector<float> imgvec;

	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			imgvec.push_back(img.at<unsigned char>(i,j) / 255.0f);
		}
	}
	// call processing function of vl
	vl_dsift_process(vlf, &imgvec[0]);

	//定义Mat存放提取到的dsift特征
    dsiftFeature = Mat(vl_dsift_get_keypoint_num(vlf), vlf->descrSize, CV_32FC1);

	for(int i = 0; i < vl_dsift_get_keypoint_num(vlf); i++)
	{
		for(int j = 0; j < vlf->descrSize; j++)
		{
			//将提取到的特征赋值给dsiftFeature保存
			dsiftFeature.at<float>(i,j) = vlf->descrs[j+i*vlf->descrSize];
		}
	}

	// Extract keypoints
    //const VlDsiftKeypoint * vlkeypoints;
    //vlkeypoints = vl_dsift_get_keypoints(vlf);
	//for (int i = 0; i < vl_dsift_get_keypoint_num(vlf); i++)
	//{
	//	cout << vlkeypoints[i].x << ", ";
	//	cout << vlkeypoints[i].y << endl;
	//}

	vl_dsift_delete(vlf); //释放资源，不然会挤爆内存
}


