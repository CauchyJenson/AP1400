#include "server.h"
#include "crypto.h"
#include <cstddef>
#include <regex>
#include <stdexcept>
#include <string>
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

bool Server::add_pending_trx(std::string trx, std::string signature) const{
    std::string sender{}, receiver{};
    double value;
    if(parse_trx(trx, sender, receiver, value)){
        auto p_sender = get_client(sender);
        auto p_receiver = get_client(receiver);
        if(p_sender == nullptr || p_receiver == nullptr){
            return false;
        }
        auto authentic = crypto::verifySignature(p_sender->get_publickey(), trx, signature);
        if(authentic && clients.at(p_sender) >= value){
            pending_trxs.emplace_back(trx);
            return true;
        }
    }
    return false;
}

size_t Server::mine(){
    std::string mempool = {};
    for(auto trx: pending_trxs){
        mempool += trx;
    }
    size_t nonce = 0;
    bool flag = false;
    while(!flag){
        for(auto &c: clients){
            nonce = c.first->generate_nonce();
            if(crypto::sha256(mempool + std::to_string(nonce)).substr(0, 10).find("000") != std::string::npos){
                flag = true;
                c.second += 6.25;
                for(auto trx: pending_trxs){
                    std::string sender{}, receiver{};
                    double value;
                    parse_trx(trx, sender, receiver, value);
                    clients[get_client(sender)] -= value;
                    clients[get_client(receiver)] += value;
                }
                pending_trxs.clear();
                return nonce;
            }
        }
    }
    return nonce;
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
