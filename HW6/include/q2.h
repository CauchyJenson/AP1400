#ifndef Q2_H
#define Q2_H
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using std::vector;
using std::string;
using std::ifstream;
using std::cout;
using std::endl;


namespace q2{
    struct Patient
    {
        string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    std::vector<Patient> read_file(std::string filename){
        vector<Patient> patients;
        ifstream f(filename);
        if(!f){
            cout << "file not found" << endl;
            throw "file not found";
        }
        string line;
        int i = 0;
        while(getline(f, line)){
            if(i < 2){
                i++;
                line.clear();
                continue;
            }
            Patient p;
            size_t pos = 0;
            pos = line.find(",");
            p.name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            if(p.name[p.name.length() - 1] != ' ')p.name += " ";
            p.name += line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            p.age = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(",");
            p.smokes = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(",");
            p.area_q = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("\n");
            p.alkhol = stoi(line.substr(0, pos));
            patients.push_back(p);
        }
        f.close();
        return patients;
    }


void sort(std::vector<q2::Patient>& patients){
    std::sort(patients.begin(), patients.end(), [](q2::Patient a, q2::Patient b){
        auto v1 = 3 * a.age + 5 * a.smokes + 2 * a.area_q + 4 * a.alkhol;
        auto v2 = 3 * b.age + 5 * b.smokes + 2 * b.area_q + 4 * b.alkhol;
        return v1 > v2;
    });
}

}
#endif //Q2_H