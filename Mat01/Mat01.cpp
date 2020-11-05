#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// multiple Mat objects share underlying matrix
void mat_example_1()
{    
    Mat a(3, 3, CV_8UC1, 128);
    Mat b(a);
    Mat c = a;
    assert(a.data == b.data && a.data == c.data);

    // modify one affects all
    cout << a << endl;
    b = 20;
    cout << a << endl;
}

// create ROI
void mat_example_2()
{
    Mat a(3, 3, CV_8UC1, 128);
    Mat a_roi(a, Rect(1, 1, 2, 2));
    a_roi = 20;
    cout << a << endl;
}

// create Mat explicitly
void mat_example_3()
{    
    Mat a(3, 3, CV_16UC3, Scalar(0, 255, 192, 128));
    cout << a << endl;

    Mat b(2, 2, CV_8SC2, Scalar(-64, 64));
    cout << b << endl;

    //Mat c(3, {2,3,4 }, CV_16FC1, Scalar::all(25.0));

    // random values
    Mat r(Size(3, 2), CV_8SC2);
    randu(r, Scalar::all(-128), Scalar::all(127));
    cout << r << endl;

    // create via vector
    vector<unsigned char> v;
    for (int i = 0; i < 3; ++i) {
        v.push_back(i * 20);
    }
    cout << Mat(v) << endl;
    //Mat m(3, 1, CV_8UC1); m.at(0) = 0; m[1] = 20; m[2] = 40;
    //cout << m << endl;

    cout << Mat::zeros(2, 3, CV_32FC1) << endl; // (nrow,ncol)

    cout << Mat::ones(Size(3, 4), CV_16FC2) << endl; // Size(width,height)

    cout << Mat::eye(3, 4, CV_8UC1) << endl;
}

int main()
{
    //mat_example_1();
    //mat_example_2();
    mat_example_3();
}
