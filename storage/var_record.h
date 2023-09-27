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

#pragma once

#include "../common/rc.h"
#include <string>
#include <vector>

#define VARFILESEP '_'
#define VARFILEEND ".data"

/*
*   VarRecordFileHandler本质上是变长数据在内存中存储的代理
*   通过handler来和内存中的数据进行交互
*   VarRecordFileHandler应当对数据具有完全的管理权限
*   由于变长数据在内存中随机存储且只存储一份，外部不应考虑其析构问题
*/
class VarRecordFileHandler{
    private:
        // 存放文件全名
        std::string fullName;
        // 存放指向内存数据的指针
        char* data=nullptr;
        std::string getFileName(std::string attr_name,std::string table_name);
        std::string getFilePathWithName(std::string attr_name,std::string table_name,const char *base_dir);
    public:
        RC initFile();
        VarRecordFileHandler(std::string attr_name,std::string table_name,const char *base_dir);
        RC checkFile();
        ~VarRecordFileHandler();
        // 初次转换时懒加载文件内容到内存中
        RC transVarAddress(char* file_addr, char* &memory_addr);
        RC insert(unsigned long long &address,const char* insert_data,int length);
};

