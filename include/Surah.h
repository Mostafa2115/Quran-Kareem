#ifndef SURAH_H
#define SURAH_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

class Surah {
private:
    std::string sname;
    std::string type;
    std::string path;
public:
    Surah(std::string sname = "", std::string type = "", std::string path = "");
    ~Surah();
    std::string getName() const;
    std::string getPath() const;
    std::string getType() const;
    void printSurahInfo() const;
    void SaveSurahData(std::ofstream& outfile);
    Surah& operator=(const Surah& other) {
        if (this != &other) {
            sname = other.sname;
            type = other.type;
            path = other.path;
        }
        return *this;
    }
};

#endif


