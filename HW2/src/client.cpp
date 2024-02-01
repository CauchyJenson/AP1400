#include "client.h"
#include <random>

Client::Client(std::string id, const Server& server):
    id(id), server(&server){
    crypto::generate_key(this->public_key, this->private_key);
}

std::string Client::get_id(){
    return this->id;
}
std::string Client::get_publickey()const{
    return this->public_key;
}

double Client::get_wallet() const{
    return server->get_wallet(this->id);
}

std::string Client::sign(std::string txt) const{
    return crypto::signMessage(this->private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value){
    std::string trx = this->id + "-" + receiver + "-" + std::to_string(value);
    std::string signature = this->sign(trx);
    return server->add_pending_trx(trx, signature);
}

size_t Client::generate_nonce(){
    static std::default_random_engine e;
    static std::uniform_int_distribution u(size_t(0), size_t(INT_MAX));
    return u(e);
}
