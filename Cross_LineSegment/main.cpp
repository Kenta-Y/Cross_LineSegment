//
//  main.cpp
//  Cross_LineSegment
//
//  Created by KentaYamagishi on 2016/04/22.
//  Copyright © 2016年 KentaYamagishi. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "create_linesegment.hpp"
#include "search_intersection.hpp"

extern elementptr head;
extern nodeptr root;

int main(int argc, const char * argv[]) {
    
    //初期設定
    cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO); //ウィンドウの初期化
    std::vector<Line_Segment> line; //線分の情報を格納するベクター
    line = cleate_line();  //線分の格納
    draw_line(line);    //線分の描画
    
    cv::waitKey(0);
    
    //y座標に関して線分の端点をソートする
    sort_y(line);
    
    //探索
    node_init();    //2分探索木の初期化
    sweep(head, root);  //交点の探索
    
    cv::waitKey(0);
    
    return 0;
}
