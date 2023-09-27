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