#include "client.h"

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