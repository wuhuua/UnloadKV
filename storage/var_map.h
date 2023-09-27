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

#include <unordered_map>
#include "../var/varlen.h"
#include "../common/rc.h"

#define MAPFILESEP '_'
#define MAPFILEEND ".map"

class VarMap{
    private:
        std::string fullName;
        std::unordered_map<std::string,varLenPointer> textMap;
        RC serialize(const std::unordered_map<std::string, unsigned long long>& map, const std::string& filename);
        RC unserialize(std::unordered_map<std::string, unsigned long long>& map, const std::string& filename);
        std::string getMapFullName(std::string attr_name,std::string table_name,const char *base_dir);
    public:
        VarMap(std::string attr_name,std::string table_name,const char *base_dir);
        void insert(std::string key,unsigned long long pointer);
        unsigned long long get(std::string key);
        RC checkFile();
        RC loadMap();
        RC saveMap();
        void setEmpty();
}; 