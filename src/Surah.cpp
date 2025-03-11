
#include "Surah.h"

Surah::Surah(std::string sname, std::string type, std::string path)
    : sname(sname), type(type), path(path) {}

Surah::~Surah() {}

std::string Surah::getName() const { return sname; }

std::string Surah::getPath() const { return path; }

std::string Surah::getType() const { return type; }

void Surah::printSurahInfo() const {
    std::cout << std::setw(20) << std::setfill(' ') << std::left << sname
              << std::setw(20) << std::setfill(' ') << std::left << type
              << std::setw(40) << std::setfill(' ') << std::left << path << std::endl;
}

void Surah::SaveSurahData(std::ofstream& outfile) {
    if (!outfile.is_open()) {
        throw std::runtime_error("Error: Unable to write to the file. Ensure the file is open.");
    }
    outfile << std::setw(20) << std::setfill(' ') << std::left << sname
            << std::setw(20) << std::setfill(' ') << std::left << type
            << std::setw(40) << std::setfill(' ') << std::left << path << std::endl;
}




