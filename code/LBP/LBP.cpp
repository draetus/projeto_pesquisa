#include "LBP.hpp"

LBP::LBP(){}

LBP::~LBP(){}
    
/*
 * Execute the LBP Algorithm
 */
template <typename _Tp>
void LBP::LBP_(const cv::Mat& src, cv::Mat& dst)
{
    dst = cv::Mat::zeros(src.rows - 1, src.cols - 1, CV_8UC1);
    for (int i = 1; i < src.rows ; i++)
    {
        for (int j = 1; j < src.cols ; j++)
        {
            _Tp center = src.at<_Tp>(i,j);
            unsigned char code = 0;
            code |= (src.at<_Tp>(i - 1, j - 1) > center) << 7;
            code |= (src.at<_Tp>(i - 1, j) > center) << 6;
            code |= (src.at<_Tp>(i - 1, j + 1) > center) << 5;
            code |= (src.at<_Tp>(i, j + 1) > center) << 4;
            code |= (src.at<_Tp>(i + 1, j + 1) > center) << 3;
            code |= (src.at<_Tp>(i + 1, j) > center) << 2;
            code |= (src.at<_Tp>(i + 1, j - 1) > center) << 1;
            code |= (src.at<_Tp>(i, j - 1) > center) << 0;
            dst.at<unsigned char>(i - 1, j - 1) = code;
        }
    }
}

/*
 * Main function that selects which type of LBP to use and other tests
 */
void LBP::run(const cv::Mat &img_input, cv::Mat &img_output)
{
    if (img_input.empty())
        return;

    int height = img_input.size().height;
    int width = img_input.size().width;
    int channels = img_input.channels();

    cv::Mat img_gray;
    if (channels > 1)
        cv::cvtColor(img_input, img_gray, CV_BGR2GRAY);
    else
        img_input.copyTo(img_gray);

    switch (img_gray.type())
    {
        case CV_8SC1:
            LBP_<char>(img_gray, img_output);
            break;

        case CV_8UC1:
            LBP_<unsigned char>(img_gray, img_output);
            break;
            
        case CV_16SC1:
            LBP_<short>(img_gray, img_output);
            break;
                
        case CV_16UC1:
            LBP_<unsigned short>(img_gray, img_output);
            break;

        case CV_32SC1:
            LBP_<int>(img_gray, img_output);
            break;

        case CV_32FC1:
            LBP_<float>(img_gray, img_output);
            break;

        case CV_64FC1:
            LBP_<double>(img_gray, img_output);
            break;

    }
}

/*
 * Does the same as run() but shows the image in a new window
 */
void LBP::run_and_show(const cv::Mat &img_input, cv::Mat &img_output)
{
    run(img_input, img_output);

    cv::namedWindow("LBP Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Input LBP Image", img_input);
    cv::waitKeyEx(0);

    cv::Mat LBP_image;

    cv::namedWindow("LBP Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Output LBP Image", img_output);
    cv::waitKeyEx(0);
}
