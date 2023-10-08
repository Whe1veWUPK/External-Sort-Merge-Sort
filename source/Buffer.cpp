#include <iostream>
#include "Buffer.hpp"
Buffer::Buffer(){
    //Buffer的无参构造函数
    this->setBufferSize(10);
    this->setCurLoation(0);
    this->setCurSize(0);
    this->isFull = false;
    this->isEmpty = true;
    this->buffer = new int[this->bufferSize];
    
}
Buffer::Buffer(int bufferSize){
    //Buffer的构造函数
    this->setBufferSize(bufferSize);
    this->setCurLoation(0);
    this->setCurSize(0);
    this->isFull = false;
    this->isEmpty = true;
    this->buffer = new int[this->bufferSize];
}
int Buffer::getBufferSize(){
    return this->bufferSize;
}
int Buffer::getCurLocation(){
    return this->curLocation;
}
int Buffer::getCurSize(){
    return this->curSize;
}
void Buffer::setBufferSize(int bufferSize){
    this->bufferSize = bufferSize;
}
void Buffer::setCurLoation(int curLocation){
    this->curLocation = curLocation;
}
void Buffer::setCurSize(int curSize){
    this->curSize = curSize;
}
void Buffer::append(int index,int value){
    //向buffer 里 插入数据 的函数
    this->buffer[index] = value;
    ++this->curSize;
    if(this->curSize > 0){
        this->isEmpty = false;
    }
    if(this->curSize == this->bufferSize){
        this->isFull = true;
    }
}
void Buffer::resize(int resize){
    //重新设定 buffer 的 size 应在每一轮结束后使用
    this->bufferSize = resize;
    this->buffer = new int[this->bufferSize];
    this->isEmpty = true;
    this->isFull = false;
    this->curSize = 0;
    this->curLocation = 0;
}
bool Buffer::Full(){
    //判断 buffer是否为满
    return this->isFull;
}
bool Buffer::Empty(){
    //判断 buffer是否为空
    return this->isEmpty;
}