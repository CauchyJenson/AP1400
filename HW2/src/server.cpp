#include "server.h"
#include <regex>
#include <stdexcept>
std::vector<std::string> pending_trxs;

Server::Server(){}

std::shared_ptr<Client>  Server::add_client(std::string id){
    // tail: if id exists, add 4 digits to the end
    std::default_random_engine e;
    std::uniform_int_distribution<int> u(0, 9);
    std::string tail = "";
    for(int i = 0; i < 4; ++i){
        tail += std::to_string(u(e));
    }
    // search
    for(auto it = clients.begin(); it != clients.end(); ++it){
        if(it->first->get_id() == id){
            id += tail;
        }
    }
    // add
    auto now_client = std::make_shared<Client>(id,*this);
    clients.insert(std::make_pair(now_client, 5));
    return now_client;
}

std::shared_ptr<Client> Server::get_client(std::string id) const{
    for(auto it = clients.begin(); it != clients.end(); ++it){
        if(it->first->get_id() == id){
            return it->first;
        }
    }
    return nullptr;
}

double Server::get_wallet(std::string id) const{
    for(auto it = clients.begin(); it != clients.end(); ++it){
        if(it->first->get_id() == id){
            return it->second;
        }
    }
    return -1;
}

bool Server::parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value){
    std::string pattern{"(\\w+)-(\\w+)-(\\d+\\.\\d+)"};
    std::regex reg(pattern);
    std::smatch res;
    if(std::regex_match(trx, res, reg)){
        sender = res[1];
        receiver = res[2];
        value = std::stod(res[3]);
        return true;
    }else{
        throw std::runtime_error("invalid transaction");
    }
}

//reference: https://www.cnblogs.com/magicsoar/p/3676071.html
using MSD = std::map<std::shared_ptr<Client>, double>; // simplify
void show_wallets(const Server& server){
    std::cout << std::string(20, '*') << std::endl;
    for(const auto &cli: *(MSD*)&server){
        std::cout << cli.first->get_id() << ": " << cli.second << std::endl;
    }
    std::cout << std::string(20, '*') << std::endl;
}