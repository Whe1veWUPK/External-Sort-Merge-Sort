#ifndef BUFFERBOUNDERY_HPP
#define BUFFERBOUNDERY_HPP
class BufferBoundery{
public:
    int startPos;   //开始位置
    int endPos;     //结束位置
    int curPos;     //当前位置
    BufferBoundery();//无参构造函数
    BufferBoundery(int startPos, int endPos, int curPos);//含参构造函数
};

#endif