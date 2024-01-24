#include "client.h"

Client::Client(std::string id, const Server& server):
    id(id), server(&server){
    crypto::generate_key(this->public_key, this->private_key);
}

std::string Client::get_id(){
    return this->id;
}
std::string Client::get_publickey(){
    return this->public_key;
}