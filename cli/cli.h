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