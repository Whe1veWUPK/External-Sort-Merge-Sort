#include<iostream>
#include "FileOperator.hpp"
void Merge(Buffer*inputBuffer,Buffer*outputBuffer){

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

    int initialRunSize = dataSize / m; //初始RunSize的大小 同时设置为buffer的大小
    Buffer*outputBuffer=new Buffer(initialRunSize);
    
    fileOperator.createInitialRuns("Input.txt", "Output.txt", initialRunSize, outputBuffer);
    Buffer *inputBuffer = new Buffer[k];//构建 inputBuffer 个数为 merge way的个数
    for (int i = 0; i < k;++i){
        inputBuffer[i].resize(initialRunSize);
    }
    int initialGroups = dataSize / initialRunSize;
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