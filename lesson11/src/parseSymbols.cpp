#include "parseSymbols.h"
#include <filesystem>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include "hog.h"

#define NSAMPLES_PER_LETTER 5
#define LETTER_DIR_PATH std::string("lesson10/generatedData/letters")

cv::Scalar rnd() {
    return cv::Scalar(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128); // можно было бы брать по модулю 255, но так цвета будут светлее и контрастнее
}

cv::Mat draw(int rows, int cols, const std::vector<std::vector<cv::Point>>& contoursPoints) {



    // создаем пустую черную картинку
    cv::Mat blackImage(rows, cols, CV_8UC3, cv::Scalar(0, 0, 0));
    // теперь мы на ней хотим нарисовать контуры
    cv::Mat imageWithContoursPoints = blackImage.clone();
    for (const auto& points : contoursPoints) {
        //        // сейчас мы смотрим на контур номер contourI
        //
        cv::Scalar contourColor = rnd(); // выберем для него случайный цвет

        for (auto &point : points) {
            imageWithContoursPoints.at<cv::Vec3b>(point.y, point.x) = cv::Vec3b(contourColor[0], contourColor[1], contourColor[2]);
        }

    }

    return imageWithContoursPoints;
}

char findLetter(const cv::Mat& img)
{
      HoG a = buildHoG(img);
    double distMin = DBL_MAX; char res = 'a';
    for (char letter = 'a'; letter <= 'z'; ++letter)
    {
        for (int i = 1; i <= NSAMPLES_PER_LETTER; ++i)
        {
            cv::Mat lt = cv::imread(LETTER_DIR_PATH + "/" + letter + "/" + std::to_string(2) + ".png");
            HoG b = buildHoG(lt);
            auto d = distance(a, b);
            if (d < distMin)
            {
                res = letter;
                distMin = d;
            }
        }
    }
    return res;
}

std::vector<cv::Mat> splitSymbols(const cv::Mat& original)
{

    cv::Mat img;
    cv::cvtColor(original, img, cv::COLOR_BGR2GRAY);

    cv::Mat binary;
    cv::threshold(img, binary, 127, 255, cv::THRESH_BINARY_INV);

    cv::adaptiveThreshold(img, binary, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, 5, 13);

    cv::Mat binary_eroded;
    cv::erode(binary, binary_eroded, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4)));

    cv::Mat binary_dilated;
    cv::dilate(binary, binary_dilated, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4)));

    binary = binary_dilated;
    std::vector<std::vector<cv::Point>> contoursPoints;
    cv::findContours(binary, contoursPoints, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    cv::Mat imageWithContoursPoints = draw(img.rows, img.cols, contoursPoints);

    std::vector<std::vector<cv::Point>> contoursPoints2;
    cv::findContours(binary, contoursPoints2, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    cv::Mat imageWithContoursPoints2 = draw(img.rows, img.cols, contoursPoints2);

    std::vector<cv::Rect> rects;
    cv::Mat imgWithBoxes = original.clone();
    for (const auto& points : contoursPoints) {
        cv::Rect box = cv::boundingRect(points);
        rects.push_back(box);
    }

    auto cmp = [&](const cv::Rect& r1, const cv::Rect& r2)
            {
        return r1.x < r2.x;
            };
    std::sort(rects.begin(), rects.end(), cmp);
    std::vector<cv::Mat> symbols;
    for (const auto& rect : rects)
    {
        symbols.emplace_back(original, rect);
    }
    std::string out_path = "lesson11/resultsData/";
    for (int i = 0; i < 76; ++i)
    {
        cv::imwrite(out_path + "test" + std::to_string(i) + ".jpg", symbols[i]);
        findLetter(symbols[i]);
        std::cout << std::to_string(i) << ": " << findLetter(symbols[i]) << "\n";
    }
    // TODO 101: чтобы извлечь кусок картинки (для каждого прямоугольника cv::Rect вокруг символа) - загуглите "opencv how to extract subimage"
    return symbols;

}

