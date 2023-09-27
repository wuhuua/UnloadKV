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
*   Created by wuhuua on 2023/9/23
*/

#include "text.h"
#include <iostream>

void Text::parseText(const char* data){
    this->text=std::string(data);
    this->setDataLength(text.length());
}

std::string Text::getText(){
    return this->text;
}

void Text::readMemory(int len){
    if(this->memory_pointer==0){
        this->text=NULLTEXT;
    }
    this->text.assign((char*)this->memory_pointer,len);
}