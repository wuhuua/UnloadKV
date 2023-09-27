#include "buffer.h"

void Buffer::insert(std::string key,std::string text){
    this->bufferMap.emplace(key,text);
}

RC Buffer::get(std::string key,std::string& text){
    if(bufferMap.find(key)!=bufferMap.end()){
        text=bufferMap.at(key);
        return RC::SUCCESS;
    }
    return RC::EMPTY;
}