//
//  create_linesegment.cpp
//  Cross_LineSegment
//
//  Created by KentaYamagishi on 2016/04/24.
//  Copyright © 2016年 KentaYamagishi. All rights reserved.
//

#include "create_linesegment.hpp"

cv::Mat img;

Line_Segment::Line_Segment(int _firstx, int _firsty, int _endx, int _endy){
    first_point = cv::Point2i(_firstx, _firsty);
    end_point = cv::Point2i(_endx, _endy);
}

cv::Point2i Line_Segment::get_first_point(){
    return first_point;
}

cv::Point2i Line_Segment::get_end_point(){
    return end_point;
}

std::vector<Line_Segment> cleate_line(){
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
    img = cv::Mat::zeros(700, 700, CV_8UC3);
    
    for(int i = 0; i < line.size(); i++){
        cv::line(img, line[i].get_first_point(), line[i].get_end_point(), cv::Scalar(0,0,200), 2, 4);
        cv::circle(img, line[i].get_first_point(), 8, cv::Scalar(0,200,200), -1);
        cv::circle(img, line[i].get_end_point(), 8, cv::Scalar(0,200,200), -1);
    }
    cv::imshow("drawing", img);
}

void draw_intersection(cv::Point2i intersection){
    cv::circle(img, intersection, 8, cv::Scalar(0, 200, 0), -1);    //緑色の円を描画
    cv::imshow("drawing", img);
}