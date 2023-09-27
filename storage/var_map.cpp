#include "var_map.h"
#include <iostream>
#include <fstream>

RC VarMap::serialize(const std::unordered_map<std::string, unsigned long long>& map, const std::string& filename) {
    if (filename.empty()) {
        return RC::EMPTY;
    }
    std::ofstream file(filename, std::ios::binary);
    if (file) {
        size_t size = map.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& pair : map) {
            const std::string& key = pair.first;
            const unsigned long long& value = pair.second;
            size_t keySize = key.size();  // 键的长度
            file.write(reinterpret_cast<const char*>(&keySize), sizeof(keySize));
            file.write(key.data(), keySize);
            file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }
        file.close();
        return RC::SUCCESS;
    }
    return RC::FILE_NOT_EXIST;
}

RC VarMap::unserialize(std::unordered_map<std::string, unsigned long long>& map, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file) {
        size_t size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            size_t keySize;
            file.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));
            std::string key(keySize, '\0');  // 创建键的字符串，长度为 keySize
            file.read(&key[0], keySize);
            unsigned long long value;
            file.read(reinterpret_cast<char*>(&value), sizeof(value));
            map[key] = value;
        }
        file.close();
        return RC::SUCCESS;
    }
    return RC::FILE_NOT_EXIST;
}

std::string VarMap::getMapFullName(std::string attr_name,std::string table_name,const char *base_dir){
    return std::string(base_dir)+table_name+MAPFILESEP+attr_name+MAPFILEEND;
}


VarMap::VarMap(std::string attr_name,std::string table_name,const char *base_dir){
    this->fullName=getMapFullName(attr_name,table_name,base_dir);
}

RC VarMap::checkFile(){
    if(this->fullName.empty()){
        return RC::EMPTY;
    }
    std::ofstream file(this->fullName, std::ios::in | std::ios::binary);
    if(file.is_open()){
        return RC::FILE_EXIST;
    }
    return RC::FILE_NOT_EXIST;
}

RC VarMap::loadMap(){
    RC rc=this->checkFile();
    if(rc!=RC::FILE_EXIST){
        return rc;
    }
    return this->unserialize(this->textMap,this->fullName);
}

RC VarMap::saveMap(){
    return this->serialize(this->textMap,this->fullName);
}

void VarMap::setEmpty(){
    this->textMap.clear();
}

void VarMap::insert(std::string key,unsigned long long pointer){
    this->textMap.emplace(key,pointer);
}

unsigned long long VarMap::get(std::string key){
    return this->textMap.at(key);
}
