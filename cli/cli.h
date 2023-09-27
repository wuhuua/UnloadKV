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
*   Created by wuhuua on 2023/9/27
*/

#include <string>
#include "../common/rc.h"
#include "../storage/var_record.h"
#include "../storage/var_map.h"
#include "../buffer/buffer.h"
#include <unordered_map>

#define CLINAME "unloadkv"

class Client{
    private:
        std::string attr_name;
        std::string table_name;
        VarRecordFileHandler handler;
        VarMap textMap;
        Buffer buffer;

        bool updateFlag=false;

        RC setText(std::string key,std::string str);
        std::string getText(char* addr,VarRecordFileHandler& handler);

        void insert();
        void select();
        void quit();
        void error();

        void printCliPrefix();
        void printHelp();
        void printError();
        void printSuccess();
        void printStartPage();
        void printAds();
    public:
        Client(std::string attr_name,std::string table_name,const char* save_dir);
        RC init();
        void start();
};