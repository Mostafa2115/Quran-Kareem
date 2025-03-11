#pragma once
#include "Surah.h"
#include "DLinkedList.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <irrKlang.h>
using namespace irrklang;

class Playlist {
private:
    std::string name;
    DLinkedList<Surah> surahList;

public:
    Playlist(std::string pname);
    std::string getName() const;
    void addSurah(const Surah& surah);
    Surah* findSurah(const std::string& name);
    void removeSurah(std::string sname);
    ~Playlist();
    void printHead() const;
    void printPlaylistInfo();
    void SavePlaylist(std::ofstream& outfile);
    void UpdateSurah(std::string name, int pos);
    void PlayPlaylist();
};

