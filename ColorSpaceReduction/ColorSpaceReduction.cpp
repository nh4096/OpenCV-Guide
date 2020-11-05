#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    const string cmdkeys =
        "{help h ? |        | print this message       }"
        "{divide d | 4      | divide color space with d}"
        "{@image   | <none> | input image              }";
    CommandLineParser parser(argc, argv, cmdkeys);
    parser.about("Color space reduction tool");

	if (parser.has("help")) {
		parser.printMessage();
		return EXIT_SUCCESS;
	}
	if (!parser.check()) {
		parser.printErrors();
		return EXIT_FAILURE;
	}

	// check divide value
	int divide = parser.get<int>("divide"); 
	
	// read image
	string imageFile = parser.get<string>(0); 
	Mat image = imread(imageFile, IMREAD_COLOR);
	if (image.empty()) {
		cout << "Cannot read from file: " << imageFile << endl;
		return EXIT_FAILURE;
	}

}
