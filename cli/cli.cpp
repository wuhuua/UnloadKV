#include "cli.h"
#include "../var/text.h"
#include <iostream>
#include <random>


Client::Client(std::string attr_name,std::string table_name,const char* save_dir):
    handler(attr_name,table_name,save_dir),textMap(attr_name,table_name,save_dir)
{
    this->attr_name=attr_name;
    this->table_name=table_name;
}

RC Client::init(){
    RC rc;
    rc=this->textMap.loadMap();
    if(rc==RC::EMPTY){
        std::cout<<"name illegal, exit!"<<std::endl;
        return rc;
    }
    if(rc==RC::FILE_NOT_EXIST){
        this->textMap.setEmpty();
        std::cout<<"no map file, init empty set"<<std::endl;
    }
    rc=handler.checkFile();
    if(rc==RC::FILE_NOT_EXIST){
        handler.initFile();
        this->textMap.setEmpty();
        std::cout<<"no data file, init empty set"<<std::endl;
    }
    return RC::SUCCESS;
}

void Client::start(){
    int num=0;
    printStartPage();
    printHelp();
    while(1){
        printCliPrefix();
        num=0;
        std::cin>>num;
        switch(num){
            case 1:{
                insert();
            }break;
            case 2:{
                select();
            }break;
            case 3:{
                quit();
            }break;
            case 4:{
                printHelp();
            }break;
            default:{
                error();
            }break;
        }
    }
}

void Client::insert(){
    std::string key;
    std::string line;
    std::cout<<"key:";
    std::cin>>key;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cout<<"text:";
    std::getline(std::cin, line);
    if(line.empty()){
        return;
    }
    // 设置数据并持久化到硬盘
    if(setText(key,line)!=RC::SUCCESS){
        std::cout<<"unable to insert"<<std::endl;
        return;
    }
    buffer.insert(key,line);
    this->updateFlag=true;
    printSuccess();
}

void Client::quit(){
    if(this->updateFlag){
        if(this->textMap.saveMap()!=RC::SUCCESS){
            std::cout<<"unable to save map file"<<std::endl;
        }
    }
    std::cout<<"bye"<<std::endl;
    exit(0);
}

void Client::error(){
    printError();
    printHelp();
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Client::select(){
    std::string key;
    std::cout<<"key:";
    std::cin>>key;
    std::string res;
    if(buffer.get(key,res)==RC::SUCCESS){
        std::cout<<std::endl;
        std::cout<<res<<std::endl;
        std::cout<<std::endl;
        return;
    }
    char* pointer=(char*)textMap.get(key);
    std::cout<<std::endl;
    std::cout<<getText(pointer,handler)<<std::endl;
    std::cout<<std::endl;
}

RC Client::setText(std::string key,std::string str){
    Text text=Text();
    // 存储传入的数据
    text.parseText(str.c_str());
    unsigned long long address;
    handler.insert(address,text.getText().c_str(),text.getDataLength());
    // 文件指针持久化到数据行中，并返回
    text.setDataAddress(address);
    this->textMap.insert(key,(unsigned long long)text.toBytes());
    return RC::SUCCESS;
}



std::string Client::getText(char* addr,VarRecordFileHandler& handler){
    char* mem_addr;
    varLenPointer pointer=(varLenPointer) addr;
    // 转换物理地址到内存地址
    handler.transVarAddress((char*)varLenAttr::parseAddr(pointer),mem_addr);
    Text text=Text((unsigned long long)mem_addr);
    text.readMemory(varLenAttr::parseLen(pointer));
    return text.getText();
}

void Client::printCliPrefix(){
    std::cout<<CLINAME;
    std::cout<<">";
}

void Client::printHelp(){
    std::cout<<"choose mode: (1)insert, (2)select, (3)quit (4)help"<<std::endl;
}

void Client::printError(){
    std::cout<<"please type in a right number to select mode"<<std::endl;
}

void Client::printSuccess(){
    std::cout<<"SUCCESS"<<std::endl;
}

void Client::printStartPage(){
    std::string line(50, '*');
    std::string emptyLine = "*" + std::string(48, ' ') + "*";
    std::string title = "*                  Unload KV                     *";
    std::string copyright = "*         Copyright ©️ 2023 UnloadBase            *";

    std::cout << line << std::endl;
    std::cout << emptyLine << std::endl;
    std::cout << title << std::endl;
    std::cout << emptyLine << std::endl;
    std::cout << copyright << std::endl;
    std::cout << emptyLine << std::endl;
    printAds();
    std::cout << emptyLine << std::endl;
    std::cout << line << std::endl;
}

void Client::printAds(){
    std::string helpKids="*"+std::string(12,' ')+"help poor kids in Uganda"+std::string(12,' ')+"*";
    std::string support="*"+std::string(7,' ')+"contact us through wuuhuua@163.com"+std::string(7,' ')+"*";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 3);
    if (dis(gen) == 0) {
        std::cout << helpKids << std::endl;
    }else{
        std::cout << support << std::endl;
    }
}