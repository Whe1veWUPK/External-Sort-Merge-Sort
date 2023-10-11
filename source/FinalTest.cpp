#include<iostream>
#include<limits>
#include<cmath>
#include "FileOperator.hpp"
#include "BufferBoundary.hpp"
#include "Timer.hpp"

void Merge(Buffer*inputBuffer,BufferBoundery*bufferBoundery,int numOfMergeWays,Buffer*outputBuffer,bool isFirst){
    int min = INT_MAX;
    int index = -1;
    FileOperator fileOperator;
    int outputIndex = 0;
    int bufferSize = outputBuffer->getBufferSize();
    int *curLoc = new int[numOfMergeWays];
    
    
    // 总的DataSize
    int totalSize = 0;
    //std::cout << "Each buffer need to process " << bufferBoundery[0].endPos - bufferBoundery[0].startPos << "\n";
    for (int i = 0; i < numOfMergeWays;++i){
        totalSize += (bufferBoundery[i].endPos - bufferBoundery[i].startPos+1);
    }
    std::cout <<"The totalSize is: "<< totalSize << "\n";
    for (int i = 0; i < totalSize;++i){
        min = INT_MAX;
        for (int j = 0; j < numOfMergeWays; ++j){
            if((inputBuffer[j].isOver())&&(bufferBoundery[j].curPos!=bufferBoundery[j].endPos)){
                std::cout << "Update inputBuffer!\n";
                //如果inputBuffer已经Merge完毕 并且还有对应的数据没有读取
                inputBuffer[j].resize(bufferSize);
                //进行读取
                fileOperator.writeToInputBuffer("Input.txt", bufferSize, bufferBoundery[j].curPos, &inputBuffer[j]);
            }
            if (!(inputBuffer[j].isOver())){
            
                if(inputBuffer[j].buffer[inputBuffer[j].getCurLocation()]<min){
                    min = inputBuffer[j].buffer[inputBuffer[j].getCurLocation()];
                    index = j;
                }
            }
            
        }
        std::cout << "Final choose : " << min << "\n";
        //移动位置
        inputBuffer[index].moveCurPos();
        //写入outputBuffer
        if(!outputBuffer->Full()){
           outputBuffer->append(outputIndex, min);
           ++outputIndex;
        }
        else{
           fileOperator.writeToFile("Output.txt", outputBuffer->getBufferSize(), isFirst, outputBuffer);
           for (int i = 0; i < bufferSize;++i){
                std::cout << outputBuffer->buffer[i] << " ";
           }
           std::cout << "\n";
           if (isFirst){
                // 更新 isFirst
                isFirst = false;
            }
           //重置outputBuffer
           outputBuffer->resize(bufferSize);
           //重置起始下标
           outputIndex = 0;
           
           outputBuffer->append(outputIndex, min);
           ++outputIndex;
        }
    }
    //把最后的outputBuffer进行输出
    if(!outputBuffer->Empty()){
        fileOperator.writeToFile("Output.txt", outputBuffer->getCurSize(), isFirst, outputBuffer);
    }
}
void finalTest(){
    FileOperator fileOperator;
    int dataSize = fileOperator.getDataSize("Input.txt");
    std::cout << "The data size is : " << dataSize << "\n";
    int k, m;
    std::cout << "Please input 'm' (the initial run number) :"
              << "\n";
    std::cin >> m;
    std::cout << "Please input 'k'(the num of merge ways) :"
              << "\n";
    std::cin >> k;
    Timer timer;
    timer.startTimer(); //开始计时
    int initialRunSize = dataSize / m ; // 设定初始的run 的 大小 同时也是Buffer 的大小
    //std::cout << "InitialRunSize is: " << initialRunSize << "\n";
    Buffer  outputBuffer(initialRunSize);
    
    fileOperator.createInitialRuns("Input.txt", "Output.txt", initialRunSize,&outputBuffer);
    outputBuffer.resize(initialRunSize);
    Buffer *inputBuffer = new Buffer[k];//构建 inputBuffer 个数为 merge way的个数
    for (int i = 0; i < k;++i){
        inputBuffer[i].resize(initialRunSize);
    }
    
    int mergePasses = std::ceil(std::log(m) / std::log(k));//求得要循环几次
    
    int numOfRuns = m;  //当前轮次的runs 个数
    int curRunSize = initialRunSize; //当前轮次的 run 的大小
    BufferBoundery *bufferBoundery = new BufferBoundery[k]; //inputBuffer的边界
    int curPos = 0;
    std::cout << "Need " << mergePasses << "\n";
    while(mergePasses--){
        //每一轮次的Merge
        int nextRoundNum = numOfRuns / k;//下一轮次的Run 数量
        //std::cout << "NextRoundNum is :" << nextRoundNum << "\n";
        if(numOfRuns%k!=0){
            //有余数则+1
            ++nextRoundNum;
        }
        bool isFirst = true; //第一次写入文件的标志
        //每一轮次 curPos要重新设置为0
        curPos = 0;
        if(numOfRuns==1){
            //剩一个Run直接退出
            break;
        }
        while(numOfRuns>0){
             if(numOfRuns>=k){
                //std::cout << "Cur numOfRuns is: " << numOfRuns << "\n";
                //如果剩余未merge Run的个数足够一次k-way merge
                for (int i = 0; i < k;++i){
                    //给InputBuffer的边界赋值
                    bufferBoundery[i] = BufferBoundery(curPos, curPos + curRunSize-1, curPos);
                    curPos += curRunSize;
                }
                for (int i = 0; i < k; ++i){
                    //向inputBuffer里写入数据
                    fileOperator.writeToInputBuffer("Input.txt", initialRunSize, bufferBoundery[i].curPos, &inputBuffer[i]);
                    // for (int i1 = 0; i1 < initialRunSize;++i1){
                    //     std::cout << inputBuffer[i].buffer[i1] << " ";
                    // }
                    // std::cout << "\n";
                    // 更新bufferBoundery内部的 curPos
                    bufferBoundery[i].curPos += initialRunSize-1;
                }
                //Merge 操作
                Merge(inputBuffer, bufferBoundery, k, &outputBuffer,isFirst);
                if(isFirst){
                    //更新 isFirst
                    isFirst = false;
                }
                //更新numOfRuns
                numOfRuns -= k;
             }
             else{
                //如果剩余未merge Run的个数不足够一次k-way merge
                for (int i = 0; i < numOfRuns;++i){
                    bufferBoundery[i] = BufferBoundery(curPos, curPos + curRunSize-1, curPos);
                    curPos += curRunSize;
                }
                for (int i = 0; i < numOfRuns;++i){
                    //向inputBuffer里写入数据
                    fileOperator.writeToInputBuffer("Input.txt", initialRunSize, bufferBoundery[i].curPos, &inputBuffer[i]);
                    // for (int i1 = 0; i1 < initialRunSize;++i1){
                    //     std::cout << inputBuffer[i].buffer[i1] << " ";
                    // }
                    // std::cout << "\n";
                    //更新inputBoundery内部的 curPos
                    bufferBoundery[i].curPos += initialRunSize;
                }
                //Merge操作
                Merge(inputBuffer, bufferBoundery, numOfRuns, &outputBuffer,isFirst);
                //更新isFirst
                if(isFirst){
                    isFirst = false;
                }
                //更新numOfRuns
                numOfRuns = 0;
             }
        }
        //更新下一轮的numOfRuns
        numOfRuns = nextRoundNum;
    }
    timer.endTimer(); //结束计时
    timer.calculateTime();
}
int main(){
    char choice = 'y';
    while(choice == 'y'){
        finalTest();
        std::cout << "Do you want to Continue ?"<< "\n";
        std::cout << "Yes(input 'y') No(input 'n')"
                  << "\n";
        std::cin >> choice;

    }
    return 0;
}