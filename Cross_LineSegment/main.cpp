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
cv::Mat img;

void draw_line(std::vector<Line_Segment> line){
    img = cv::Mat::zeros(700, 700, CV_8UC3);
    
    for(int i = 0; i < line.size(); i++){
        cv::line(img, line[i].get_first_point(), line[i].get_end_point(), cv::Scalar(0,0,200), 2, 4);
        cv::circle(img, line[i].get_first_point(), 8, cv::Scalar(0,200,200), -1);
        cv::circle(img, line[i].get_end_point(), 8, cv::Scalar(0,200,200), -1);
    }
    
    cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    cv::imshow("drawing", img);
}

typedef cv::Point2i datatype;

typedef struct element{
    cv::Point2i p1, p2;
    element *next;
} *elementptr;

typedef struct node{
    cv::Point v;
    struct node *lson, *rson;
} *nodeptr;

struct element nil2;
struct node nil;
elementptr head;
nodeptr root;

int node_init(){
    root = new node;
    if(root == NULL) return 0;
    root->v.x = -1;
    root->rson = root->lson = &nil;
    
    return 1;
}

int insert_point(datatype data){
    nodeptr p, q = 0;
    p = root;
    while (p != &nil){
        q = p;
        if(data.x == p->v.x) return 0;
        if(data.x < p->v.x) p = p->lson;
        else                p = p->rson;
    }
    p = new node;
    if(p == NULL) return 0; //挿入失敗
    p->v = data;
    p->lson = p->rson = &nil;
    if(data.x < q->v.x) q->lson = p;
    else                q->rson = p;
    //std::cout << "a";
    return 1;
}

int delete_point(datatype data){
    nodeptr f = 0, p, q;
    p = root;
    //while((p != &nil || data.x != p->v.x)){
    while(p != &nil){
        if(data.x == p->v.x) break;
        f = p;
        if(p->v.x > data.x) p = p->lson;
        else                p = p->rson;
    }
    if(p == &nil) return 0;
    if(p->lson == &nil || p->rson == &nil){
        if(p->lson == &nil) q = p->rson;
        else                q = p->lson;
        if(f->lson == p) f->lson = q;
    }else{
        q = p->rson;
        f = q;
        while(q->lson != &nil){
            f = q;
            q = q->lson;
        }
        p->v = q->v;
        if(q == f) p->rson = q->rson;
        else f->lson = q->rson;
    }
    //std::cout<<"b";
    return 1;
}

void treeInterval(nodeptr p, int x1, int x2, int y){
    if(p != &nil){
        //std::cout<<x1<<", "<<x2<<", "<<p->v.x<<std::endl;
        if(p->v.x >= x1 && p->v.x <= x2){
            /*交点*/
//            cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
            cv::circle(img, cv::Point(p->v.x, y), 8, cv::Scalar(200, 0, 0), -1);
//            cv::imshow("drawing", img);
            
            std::cout << "foo, " << p->v.x << ", " << p->v.y << ", " << x1 << ", " << x2 << std::endl;
            treeInterval(p->lson, x1, x2, y);
            treeInterval(p->rson, x1, x2, y);
        }
        if(p->v.x <= x1) treeInterval(p->rson, x1, x2, y);
        if(p->v.x >= x2) treeInterval(p->lson, x1, x2, y);
    }
}

void sweep(elementptr head, nodeptr root){
    while(head != NULL){
        //std::cout<<head->p1.y<<", "<<head->p2.y<<std::endl;
        if(head->p1.y < head->p2.y) insert_point(head->p1);
        else if(head->p1.y > head->p2.y) delete_point(head->p2);
        else{
            //std::cout << "c";
            if(head->p1.x < head->p2.x) treeInterval(root, head->p1.x, head->p2.x, head->p1.y);
            else                        treeInterval(root, head->p2.x, head->p1.x, head->p1.y);
        }
        head = head->next;
        
    }
}

struct BothPoint{
    cv::Point2i first_point;
    cv::Point2i end_point;
};

/*
 array = ソートしたいデータ
 begin = 要素の最初
 end = 要素の末尾
*/
void QuickSort(std::vector<BothPoint> &array, int begin, int end){
    int i = begin;
    int j = end;
    int pivot;
    BothPoint temp;
    
    pivot = array[ ( begin + end ) / 2 ].first_point.y;  // 中央の値をpivotにする
    
    while(1){
        while( array[i].first_point.y < pivot ) ++i;   /* 枢軸以上の値が見つかるまで右方向へ進めていく */
        while( array[j].first_point.y > pivot ) --j;   /* 枢軸以下の値が見つかるまで左方向へ進めていく */
        if( i >= j )break;  // 軸がぶつかったらソート終了
        
        // 入れ替え
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
    }
    
    // 軸の左側をソートする
    if( begin < i - 1 ) QuickSort( array, begin, i - 1 );
    // 軸の右側をソートする
    if( j + 1 < end ) QuickSort( array, j + 1, end );
}
bool test = false;

int insert_element(datatype first, datatype end){
    if(!test){
        head = new element;
        if(head == NULL) return 0; //挿入失敗
        head->p1 = first;
        head->p2 = end;
        head->next = &nil2;
        test = true;
    }else{
        elementptr p = head, q = 0;
        while (p != &nil2){
            q = p;
            p = p->next;
        }
        p = new element;
        if(p == NULL) return 0; //挿入失敗
        p->p1 = first;
        p->p2 = end;
        p->next = &nil2;
        q->next = p;
    }
    return 1;
}



int element_init(){
    head = new element;
    if(head == NULL) return 0;
    head->next = &nil2;
    
    return 1;
}

int main(int argc, const char * argv[]) {
    
    //初期設定
    std::vector<Line_Segment> line; //線分の情報を格納するベクター
    line = makeline();  //線分の格納
    draw_line(line);    //線分の描画
    
    cv::waitKey(0);
    
    //y座標に関して線分の端点をソートする
    std::vector<BothPoint> both_p;
    for(int i = 0; i < line.size(); i++){
        BothPoint tmp1 = {line[i].get_first_point(),line[i].get_end_point()};
        BothPoint tmp2 = {line[i].get_end_point(),line[i].get_first_point()};
        both_p.push_back(tmp1);
        both_p.push_back(tmp2);
    }
    QuickSort(both_p, 0, (int)both_p.size()-1);
    
    node_init();
    //element_init();
    for(int i = 0; i < both_p.size(); i++){
        //std::cout << both_p[i].first_point.x << "," << both_p[i].first_point.y << std::endl;
        insert_element(both_p[i].first_point, both_p[i].end_point);
    }
    
    //探索
    sweep(head, root);
    
                cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
                cv::imshow("drawing", img);
    cv::waitKey(0);
    
    return 0;
}
