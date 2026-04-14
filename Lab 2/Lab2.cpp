#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>  
#include <ctime>    

using namespace cv;
using namespace std;

int main() {
    srand(time(nullptr));

    Mat baseCanvas(600, 800, CV_8UC3, Scalar(0, 0, 0));

    line(baseCanvas, Point(0, 0), Point(799, 599), Scalar(255, 0, 0), 3);
    rectangle(baseCanvas, Point(100, 100), Point(300, 250), Scalar(0, 255, 0), 2);
    circle(baseCanvas, Point(400, 300), 100, Scalar(0, 0, 255), -1);
    ellipse(baseCanvas, Point(400, 300), Size(150, 70), 30, 0, 360, Scalar(0, 255, 255), 2);

    vector<Point> pts = { Point(500,100), Point(600,150), Point(650,250),
                         Point(550,300), Point(450,200) };
    polylines(baseCanvas, pts, true, Scalar(255, 255, 0), 2);


    string text = "Karlov D.R. Group 22-PM-1";
    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 1.0;
    Scalar textColor = Scalar(255, 255, 255);
    int thickness = 2;

    int baseline = 0;
    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);

    Point textPos(100, 100);


    int dx = 4;
    int dy = 3;

    cout << "Àíèìàöèÿ çàïóùåíà. Íàæìèòå ESC äëÿ âûõîäà..." << endl;
    cout << "Ðàçìåð òåêñòà: øèðèíà = " << textSize.width
        << ", âûñîòà = " << textSize.height << endl;
    cout << "Baseline = " << baseline << endl;

    while (true) {

        Mat frame = baseCanvas.clone();


        putText(frame, text, textPos, fontFace, fontScale, textColor, thickness);

        imshow("My Drawing Animation", frame);

        textPos.x += dx;
        textPos.y += dy;


        if (textPos.x <= 0) {
            textPos.x = 0;
            dx = abs(dx); 
        }

        if (textPos.x + textSize.width >= frame.cols) {
            textPos.x = frame.cols - textSize.width;
            dx = -abs(dx); 
        }


        if (textPos.y - textSize.height <= 0) {
            textPos.y = textSize.height;
            dy = abs(dy); 
        }


        if (textPos.y >= frame.rows - baseline) {
            textPos.y = frame.rows - baseline;
            dy = -abs(dy); 
        }


        int key = waitKey(30);

        if (key == 27) {
            break;
        }
    }

    Mat finalImage = baseCanvas.clone();
    putText(finalImage, text, textPos, fontFace, fontScale, textColor, thickness);
    imwrite("SavedFigure.jpg", finalImage);

    cout << "Àíèìàöèÿ çàâåðøåíà. Èçîáðàæåíèå ñîõðàíåíî." << endl;

    return 0;
}
