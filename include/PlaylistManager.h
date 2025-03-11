#pragma once
#include "Playlist.h"
#include <irrKlang.h>
#include <iostream>
#include <conio.h>
#include "DLinkedList.h"

class PlaylistManager {
private:
    DLinkedList<Playlist> playlists;
    std::string n;

public:
    PlaylistManager();
    ~PlaylistManager();
    void addPlaylist(const std::string& name);
    void displayPlaylists() const;
    Playlist* findPlaylist(const std::string& name);
    void addSurahToPlaylist(const std::string& playListName, const Surah& surah);
    void RemoveSurah(const std::string& pname, const std::string& sname);
    void printTables() const;
    void printSpecificList(const std::string& pname);
    void RemovePlaylist(const std::string& pname);
    void SaveToFile(std::ofstream& outfile);
    void Update(const std::string& pname, std::string sname, int pos);
    void LoadPlaylist(const std::string& filename);
    void play(const std::string name);
    bool findSurah(const std::string pname, std::string sname);
};

