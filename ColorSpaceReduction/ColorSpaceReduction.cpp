#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Use lookup table for faster mapping
void compute_table(unsigned char table[], unsigned int d)
{
	for (int i = 0; i < 256; ++i) {
		table[i] = i / d * d;
	}
}

void apply_reduction(Mat& image, const unsigned char table[])
{
	switch (image.channels())
	{
	case 1:
	{
		MatIterator_<unsigned char> it;
		for (it = image.begin<unsigned char>(); it != image.end<unsigned char>(); it++) {
			*it = table[*it];
		}
		break;
	}
	case 3:
	{
		break;
	}		
	}
}

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
	assert(divide > 0 && divide < 128);

	// read image
	string imageFile = parser.get<string>(0); 
	Mat image = imread(imageFile, IMREAD_COLOR);
	if (image.empty()) {
		cout << "Cannot read from file: " << imageFile << endl;
		return EXIT_FAILURE;
	}
	
	unsigned char table[256];
	compute_table(table,static_cast<unsigned char>(divide));

	imshow("input", image); waitKey(0);

	apply_reduction(image, table);

	imshow("output", image); waitKey(0);
}
