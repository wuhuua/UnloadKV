#include "cli/cli.h"

int main(){
    Client cli=Client("attr","table","./");
    if(cli.init()!=RC::SUCCESS){
        return 0;
    }
    cli.start();
    return 0;
}
