/*
Copyright (c) 2023 UnloadHome and/or its affiliates. All rights reserved.
UnloadBase is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
 */

/*
*   Created by wuhuua on 2023/9/21
*/

#include "varlen.h"
#include <limits>

varLenAttr::varLenAttr(int length,unsigned long long address){
    this->file_pointer=address;
    this->file_pointer=getDataAddress();
    unsigned long long length_=0ULL;
    length_+=length;
    this->file_pointer+=length_<<(getBitNumULL()-VAR_LENGTH_BITNUM);
}

char* varLenAttr::toBytes(){
    return (char*)this->file_pointer;
}

void varLenAttr::parseBytes(char* data){
    this->file_pointer=(unsigned long long)data;
}

int varLenAttr::getDataLength(){
    return parseLen(this->file_pointer);
}

unsigned long long varLenAttr::getDataAddress(){
    return parseAddr(this->file_pointer);
}

int varLenAttr::getBitNumULL(){
    return sizeof(varLenPointer)*8;
}

void varLenAttr::setDataLength(int len){
    this->file_pointer=parseAddr(this->file_pointer);
    this->file_pointer+=(unsigned long long)len<<(getBitNumULL()-VAR_LENGTH_BITNUM);
}

void varLenAttr::setDataAddress(unsigned long long address){
    this->file_pointer&=(unsigned long long)parseLen(this->file_pointer)<<(getBitNumULL()-VAR_LENGTH_BITNUM);
    this->file_pointer+=address;
}

void varLenAttr::setMemoryPointer(unsigned long long pointer){
    this->memory_pointer=pointer;
}

unsigned long long varLenAttr::parseAddr(varLenPointer pointer){
    unsigned long long mask = std::numeric_limits<unsigned long long>::max() >> VAR_LENGTH_BITNUM;
    return pointer&mask;
}

int varLenAttr::parseLen(varLenPointer pointer){
    int addressBitNum=getBitNumULL()-VAR_LENGTH_BITNUM;
    return static_cast<int>((pointer>>addressBitNum)&0xFFFF);
}