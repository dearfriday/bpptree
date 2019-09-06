#include <iostream>
#include <map>
#include <Json/value.h>
#include "Bpptree.h"

using namespace bpptree;


struct transaction {
    int i = 0;
    std::string txid;

    bool operator<(const transaction &tx) const {
        return i < tx.i;
    }

    bool operator>(const transaction &tx) const {
        return i > tx.i;
    }


    friend  std::ostream &operator << (std::ostream &os, const transaction &tx){
        os << "{ " << tx.i << ", " << tx.txid << "} ";
        return  os;
    }

    std::string to_string() const {
        return "{" + std::to_string(i) + ", " + txid + "}";
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;

//    std::cout << transaction{0, "1"} << std::endl;


    std::map<int, std::string>  kk;

    Json::Value vv;
    try {
        node<transaction, 5> tree;
        for (int i = 0; i < 12; i++) {
            tree.insert({i, std::to_string(i)});

        }
        std::cout << "-------------------------\n";
        tree.debug(vv);
        std::cout << vv.toStyledString() << std::endl;
    }catch (const std::exception &e){
        std::cout << "exception e : " << e.what() << std::endl;
    }




    return 0;
}