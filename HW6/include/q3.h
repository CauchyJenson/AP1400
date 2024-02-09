#ifndef Q3_H
#define Q3_H
#include <queue>
#include <string>
#include <fstream>
#include <regex>


struct Flight
{
	std::string flight_number;
	size_t duration;
	size_t connections;
	size_t connection_times;
	size_t price;
    size_t weight;
};

std::priority_queue<Flight> gather_flights(std::string filename){
    std::priority_queue<Flight> flights;
    std::ifstream f(filename);
    if(!f){
        throw "file not found";
    }
    std::string line;
    int i = 0;
    while(getline(f, line)){
        Flight fl;

    }
}

#endif //Q3_H