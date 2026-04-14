/*#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace cv;
using namespace std;

string detectShape(const vector<Point>& contour) {
    double perimeter = arcLength(contour, true);
    vector<Point> approx;
    approxPolyDP(contour, approx, 0.04 * perimeter, true);

    int vertices = (int)approx.size();

    if (vertices == 3) {
        return "Triangle";
    }
    else if (vertices == 4) {
        Rect rect = boundingRect(approx);
        double aspectRatio = (double)rect.width / rect.height;
        if (aspectRatio >= 0.95 && aspectRatio <= 1.05) {
            return "Square";
        }
        else {
            return "Rectangle";
        }
    }
    else {
        double area = contourArea(contour);
        if (perimeter > 0) {
            double circularity = 4 * M_PI * area / (perimeter * perimeter);
            if (circularity > 0.7) {
                return "Circle";
            }
        }
        return "Polygon";
    }
}

int main(int argc, char** argv) {
    Mat img = imread("Figure.png");
    if (img.empty()) {
        cout << "Ошибка: не удалось загрузить изображение!" << endl;
        cout << "Проверьте, что файл Figure.png находится в папке с программой" << endl;
        return -1;
    }

    Mat gray, edges, binary;


    cvtColor(img, gray, COLOR_BGR2GRAY);

    GaussianBlur(gray, gray, Size(5, 5), 0);


    Canny(gray, edges, 50, 150);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(edges, binary, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat result = img.clone();

    cout << "Найдено контуров: " << contours.size() << endl;
    cout << "----------------------------------------" << endl;

    int shapeCount = 0;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);

        if (area < 500) continue;

        shapeCount++;

        double perimeter = arcLength(contours[i], true);

        Moments m = moments(contours[i]);
        Point2f center(m.m10 / m.m00, m.m01 / m.m00);

        string shapeName = detectShape(contours[i]);

        stringstream ss;
        ss << shapeName << "\nP=" << fixed << setprecision(1) << perimeter;
        string label = ss.str();

        drawContours(result, contours, (int)i, Scalar(0, 255, 0), 2);

        circle(result, center, 6, Scalar(0, 0, 255), -1);
        circle(result, center, 6, Scalar(255, 255, 255), 2);

        int fontFace = FONT_HERSHEY_SIMPLEX;
        double fontScale = 0.5;
        int thickness = 1;
        int baseline = 0;
        Size textSize = getTextSize(label, fontFace, fontScale, thickness, &baseline);

        Point textOrg(center.x - textSize.width / 2, center.y - textSize.height / 2 - 5);


    

        // Рисуем текст белым цветом
        putText(result, label, textOrg, fontFace, fontScale, Scalar(0,0, 0), thickness);

        // Вывод информации в консоль
        cout << "Фигура " << shapeCount << ": " << shapeName
            << " | Периметр = " << fixed << setprecision(1) << perimeter
            << " | Центр = (" << fixed << setprecision(0) << center.x
            << ", " << center.y << ")" << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << "Всего распознано фигур: " << shapeCount << endl;

   
    double scale = 0.5;  

    Mat smallOriginal, smallEdges, smallResult;
    resize(img, smallOriginal, Size(), scale, scale);
    resize(edges, smallEdges, Size(), scale, scale);
    resize(result, smallResult, Size(), scale, scale);

    // Отображение результатов в уменьшенных окнах
    namedWindow("Original", WINDOW_NORMAL);
    namedWindow("Canny Edges", WINDOW_NORMAL);
    namedWindow("Result", WINDOW_NORMAL);

    // Устанавливаем размер окон
    resizeWindow("Original", smallOriginal.cols, smallOriginal.rows);
    resizeWindow("Canny Edges", smallEdges.cols, smallEdges.rows);
    resizeWindow("Result", smallResult.cols, smallResult.rows);

    imshow("Original", smallOriginal);
    imshow("Canny Edges", smallEdges);
    imshow("Result", smallResult);

    // Сохранение результата
    imwrite("result_with_contours.png", result);
    cout << "\nРезультат сохранен в result_with_contours.png" << endl;

    waitKey(0);
    return 0;
}
*/