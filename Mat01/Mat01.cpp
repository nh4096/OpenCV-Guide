#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void mat_example_1()
{
    // multiple Mat object share underlying matrix
    Mat a(3, 3, CV_8UC1, 128);
    Mat b(a);
    Mat c = a;
    assert(a.data == b.data && a.data == c.data);

    // modify one affects all
    cout << a << endl;
    b = 20;
    cout << a << endl;
}

void mat_example_2()
{
    // create ROI
    Mat a(3, 3, CV_8UC1, 128);
    Mat a_roi(a, Rect(1, 1, 2, 2));
    a_roi = 20;
    cout << a << endl;
}

int main()
{
    //mat_example_1();
    mat_example_2();
}
