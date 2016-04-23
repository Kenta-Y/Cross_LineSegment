//
//  main.cpp
//  Cross_LineSegment
//
//  Created by KentaYamagishi on 2016/04/22.
//  Copyright © 2016年 KentaYamagishi. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class Line_Segment{
private:
    cv::Point2i first_point;
    cv::Point2i end_point;
public:
    Line_Segment(int _firstx, int _firsty, int _endx, int _endy){
        first_point = cv::Point2i(_firstx, _firsty);
        end_point = cv::Point2i(_endx, _endy);
    }
    
    cv::Point2i get_first_point(){
        return first_point;
    }
    
    cv::Point2i get_end_point(){
        return end_point;
    }
};

std::vector<Line_Segment> makeline(){
    std::vector<Line_Segment> line;
    line.push_back(Line_Segment(500, 220, 500, 600));   // A
    line.push_back(Line_Segment(250, 500, 600, 500));   // B
    line.push_back(Line_Segment(630, 120, 630, 450));   // C
    line.push_back(Line_Segment(300, 220, 300, 400));   // D
    line.push_back(Line_Segment(150,  50, 150, 370));   // E
    line.push_back(Line_Segment(250, 270, 600, 270));   // F
    line.push_back(Line_Segment( 50, 150, 500, 150));   // G
    line.push_back(Line_Segment(320,  50, 660,  50));   // H
    
    return line;
}

void draw_line(std::vector<Line_Segment> line){
    cv::Mat img = cv::Mat::zeros(700, 700, CV_8UC3);
    
    for(int i = 0; i < line.size(); i++){
        cv::line(img, line[i].get_first_point(), line[i].get_end_point(), cv::Scalar(0,0,200), 2, 4);
        cv::circle(img, line[i].get_first_point(), 8, cv::Scalar(0,200,200), -1);
        cv::circle(img, line[i].get_end_point(), 8, cv::Scalar(0,200,200), -1);
    }
    
    cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    cv::imshow("drawing", img);
}

int main(int argc, const char * argv[]) {
    
    //初期設定
    std::vector<Line_Segment> line; //線分の情報を格納するベクター
    line = makeline();  //線分の格納
    draw_line(line);    //線分の描画
    
    cv::waitKey(0);
    
    //y座標に関して線分の端点をソートする
    
    //探索
    
    return 0;
}
