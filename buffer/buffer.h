#include <unordered_map>
#include "../common/rc.h"
#include <string>

class Buffer{
    private:
        std::unordered_map<std::string,std::string> bufferMap;
    public:
        Buffer(){}
        void insert(std::string key,std::string text);
        RC get(std::string key,std::string& text);
};