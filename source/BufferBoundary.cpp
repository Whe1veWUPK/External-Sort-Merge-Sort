#include<iostream>
#include"BufferBoundary.hpp"
BufferBoundery::BufferBoundery(){
    //无参构造函数
    this->curPos = 0;
    this->startPos = 0;
    this->endPos = 0;
}
BufferBoundery::BufferBoundery(int startPos,int endPos,int curPos){
    //含参构造函数
    this->startPos = startPos;
    this->endPos = endPos;
    this->curPos = curPos;
}