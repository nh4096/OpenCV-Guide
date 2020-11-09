#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void Sharpen(const Mat& myImage, Mat& Result)
{
	CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images
	const int nChannels = myImage.channels();
	Result.create(myImage.size(), myImage.type());
	for (int j = 1; j < myImage.rows - 1; ++j)
	{
		const uchar* previous = myImage.ptr<uchar>(j - 1);
		const uchar* current = myImage.ptr<uchar>(j);
		const uchar* next = myImage.ptr<uchar>(j + 1);
		uchar* output = Result.ptr<uchar>(j);
		for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i)
		{
			*output++ = saturate_cast<uchar>(5 * current[i]
				- current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
		}
	}
	Result.row(0).setTo(Scalar(0));
	Result.row(Result.rows - 1).setTo(Scalar(0));
	Result.col(0).setTo(Scalar(0));
	Result.col(Result.cols - 1).setTo(Scalar(0));
}
int main(int argc, char** argv)
{
	const string cmdkeys =
		"{help h ?    |        | print this message                 }"
		"{grayscale g |        | if true, grayscale; if false, color}"
		"{@image      | <none> | input image                        }";
	CommandLineParser parser(argc, argv, cmdkeys);
	parser.about("Filtering with mask");

	if (parser.has("help")) {
		parser.printMessage();
		return EXIT_SUCCESS;
	}
	if (!parser.check()) {
		parser.printErrors();
		return EXIT_FAILURE;
	}

	// read image
	string imageFile = parser.get<string>(0);
	Mat image;
	if (parser.has("grayscale")) {
		image = imread(imageFile, IMREAD_GRAYSCALE);
	}
	else {
		image = imread(imageFile, IMREAD_COLOR);
	}
	if (image.empty()) {
		cout << "Cannot read from file: " << imageFile << endl;
		return EXIT_FAILURE;
	}
	imshow("input", image); waitKey(0);

	// 1. filter by hand
	Mat output1;
	Sharpen(image, output1);
	imshow("hand", output1); waitKey(0);

	// 2. by filter2d()
	Mat output2;
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(image, output2, image.depth(), kernel);
	imshow("filter2d", output2); waitKey(0);
}
