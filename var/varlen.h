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
*   Created by wuhuua on 2023/9/21
*/

#pragma once

#include <string>

/*
*    定义变长数据在data中以定长为8字节的指针存放，包含长度数据和指针数据
*    |--|------------------|
*     P1        P2
*     P1存放2个字节大小的无符号整型数
*     P2存放6个字节长度的地址指针
*/
typedef unsigned long long varLenPointer;
#define VAR_LENGTH_BITNUM 16
// 定义变长字段在表元数据中长度为-1
#define VAR_ATTR_LEN -1

/*
*   变长数据的抽象类，包含8字节指针，继承varLenAttr的类可以添加实际数据字段
*   varLenAttr以状态机的方式工作，当file_pointer=!0时为持久态，当memory_pointer!=0时为内存态
*   子类的扩展功能都应该在内存态实现，并且维护封装后的数据，不应使用memory_pointer指向的空间
*/
class varLenAttr{
    protected:
        varLenPointer file_pointer=0;
        unsigned long long memory_pointer=0;
    public:
        varLenAttr(){};
        varLenAttr(unsigned long long memory_pointer_):memory_pointer(memory_pointer_){}
        varLenAttr(int length,unsigned long long address);

    /*
    *   持久态函数
    */
    public:
        // 将持久化指针返回
        char* toBytes();
        // 获取指向内存数据的指针
        void parseBytes(char* data);
        int getDataLength();
        unsigned long long getDataAddress();
        void setDataLength(int len);
        void setDataAddress(unsigned long long address);

    /*
    *   内存态函数
    */
    public:
        void setMemoryPointer(unsigned long long address);
    
    /*
    *   varAttrPointer的静态方法
    */
    public:
        unsigned long long static parseAddr(varLenPointer pointer);
        int static parseLen(varLenPointer pointer);
        int static getBitNumULL();
};