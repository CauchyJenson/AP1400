#include "server.h"
#include "client.h"

std::vector<std::string> pending_trxs;

Server::Server() {
}

std::shared_ptr<Client> Server::add_client(std::string id){
    // set random number
    std::default_random_engine e;
    std::uniform_int_distribution<int> p(0,9);
    e.seed(time(0));
    std::string end = "";
    for(int i = 0; i < 4; ++i){
        end += std::to_string(p(e));
    }
    for(auto &c: clients){
        if(c.first->get_id() == id){id += end;}
    }
    auto ptr = std::make_shared<Client>(id, *this);
    clients[ptr] = 5;
    return ptr;
}

std::shared_ptr<Client> Server::get_client(std::string id)const{
    for(auto &c: clients){
        if(c.first->get_id() == id){return c.first;}
    }
    return nullptr;
}

double Server::get_wallet(std::string id) const {
    for(auto &c: clients){
        if(c.first->get_id() == id){return c.second;}
    }
    return 0;
}

bool Server::parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value){
    std::string pattern = "(\\w+)-(\\w+)-(\\d+\\.\\d+)";
    std::regex r(pattern);
    std::smatch res;
    if(std::regex_match(trx, res, r)){
        sender = res.str(1);
        receiver = res.str(2);
        value = std::stod(res.str(3)); 
        return true;
    }else{
        throw std::runtime_error("trx is not format");
    }
    return false;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const{
    std::string sender, receiver;
    double value;
    Server::parse_trx(trx, sender, receiver, value);
    auto p_sneder = get_client(sender);
    auto p_receiver = get_client(receiver);
    if(p_receiver == nullptr)return false;
    bool authentic = crypto::verifySignature(p_sneder->get_publickey(), trx, signature);
    if(authentic && clients.at(p_sneder) >= value){
        pending_trxs.push_back(trx);
        return true;
    }
    return false;
}
size_t Server::mine() {
	std::string mempool{};
	for (const auto& trx : pending_trxs) {
		mempool += trx;
	}
	size_t nonce = 0;
	bool flag = false;  //not mined
	while (!flag) {
		for (auto& c_w : clients) {
			nonce = c_w.first->generate_nonce();
			if (crypto::sha256(mempool + std::to_string(nonce)).substr(0, 10).find("000") != std::string::npos) {   //mined
                flag = true;
				c_w.second += 6.25;
				for (auto& trx : pending_trxs) {
					std::string sender, receiver;
					double value;
					Server::parse_trx(trx, sender, receiver, value);
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

using MPD = std::map<std::shared_ptr<Client>, double>;
void show_wallets(const Server& server) {
	std::cout << std::string(20, '*') << std::endl;
    /*
        * a hack way to visit the private member varible of server
        * constrained by the rule, which doesn't allow us to modify `class Server`
    */
	for (const auto& client : *((MPD*)&server)) 
		std::cout << client.first->get_id() << " : " << client.second << std::endl;
	std::cout << std::string(20, '*') << std::endl;
}