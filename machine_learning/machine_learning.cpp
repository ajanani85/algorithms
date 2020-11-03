#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;

void splitImage(const cv::Mat &src, std::vector<cv::Mat> &res, const cv::Size &block)
{
	if(block.height > src.rows || block.width > src.cols)
	{
		return;
	}

	int row = 0;
	while(row < src.rows)
	{
		cv::Mat mat;

	}

}

int main(int argc, char **argv) {

	cv::Mat raw_img = cv::imread("/home/ubuntu/eclipse-workspace/algorithms/machine_learning/images/digits.png", cv::IMREAD_GRAYSCALE);

	std::vector<cv::Mat> row_images;



	cv::imshow("machine_learning", raw_img);

	if(cv::waitKey(0) != 'q')
	{
		;
	}

	return 0;
}
