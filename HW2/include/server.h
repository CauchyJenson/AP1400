#ifndef SERVER_H
#define SERVER_H
#include <memory>
#include <string>
#include <map>
#include <random>
#include "client.h"

class Client;

class Server
{
public:
	Server();
	std::shared_ptr<Client> add_client(std::string id);
	std::shared_ptr<Client> get_client(std::string id) const;
	double get_wallet(std::string id) const;
	bool parse_trx(std::string trx, std::string sender, std::string receiver, double value);
	bool add_pending_trx(std::string trx, std::string signature);
	size_t mine();
private:
	std::map<std::shared_ptr<Client>, double> clients;
};

void show_wallets(const Server& server);
#endif //SERVER_H