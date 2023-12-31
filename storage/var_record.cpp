/*
Copyright (c) 2023 UnloadHome and/or its affiliates. All rights reserved.
UnloadKV is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
 */

/*
*   Created by wuhuua on 2023/9/25
*/

#include "var_record.h"
#include <fstream>

std::string VarRecordFileHandler::getFileName(std::string attr_name,std::string table_name){
    return table_name+VARFILESEP+attr_name+VARFILEEND;
}


std::string VarRecordFileHandler::getFilePathWithName(std::string attr_name,std::string table_name,const char *base_dir){
    return std::string(base_dir)+'/'+getFileName(attr_name,table_name);
}


VarRecordFileHandler::VarRecordFileHandler(std::string attr_name,std::string table_name,const char *base_dir){
    this->fullName=getFilePathWithName(attr_name,table_name,base_dir);
}

VarRecordFileHandler::~VarRecordFileHandler(){
    delete[] this->data;
}

RC VarRecordFileHandler::initFile(){
    if(this->fullName.empty()){
        return RC::EMPTY;
    }
    std::ofstream file(this->fullName);
    if (file.is_open()) {
        file.close();
        return RC::SUCCESS;
    } 
    return RC::FILE_NOT_EXIST;
}

RC VarRecordFileHandler::transVarAddress(char* file_addr, char* &memory_addr){
    if(this->data==nullptr){
        if(this->fullName.empty()){
            return RC::EMPTY;
        }
        std::ifstream file;
        file.open(this->fullName, std::ios_base::in | std::ios_base::binary);
        if (file.is_open()) {
            file.seekg(0, std::ios::end);
            std::streampos fileSize = file.tellg();
            file.seekg(0, std::ios::beg);
            this->data = new char[(unsigned long long)fileSize];
            file.read(this->data, fileSize);
            file.close();
        }
        else {
            return RC::FILE_NOT_OPENED;
        }
    }
    memory_addr=(char*)((unsigned long long)this->data+(unsigned long long)file_addr);
    return RC::SUCCESS;
}

RC VarRecordFileHandler::insert(unsigned long long &address,const char* insert_data,int length){
    if(this->fullName.empty()){
        return RC::EMPTY;
    }
    std::ofstream file(this->fullName, std::ios::in | std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file.seekp(0, std::ios::end);
        std::streampos endPosition = file.tellp();
        address = static_cast<unsigned long long>(endPosition);
        file.write(insert_data, length);
        file.close();
    } else {
        return RC::FILE_NOT_OPENED;
    }
    return RC::SUCCESS;
}

RC VarRecordFileHandler::checkFile(){
    if(this->fullName.empty()){
        return RC::EMPTY;
    }
    std::ofstream file(this->fullName, std::ios::in | std::ios::binary);
    if(file.is_open()){
        return RC::FILE_EXIST;
    }
    return RC::FILE_NOT_EXIST;
}