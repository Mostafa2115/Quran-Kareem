#include "PlaylistManager.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

PlaylistManager::PlaylistManager() {}
PlaylistManager::~PlaylistManager() {}

bool PlaylistManager::findSurah(std::string pname, std::string sname) {
    Playlist* playList = findPlaylist(pname);
    if (playList) {
        if (playList->findSurah(sname)) {
            return true;
        }
    }
    return false;
}

void PlaylistManager::LoadPlaylist(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    Playlist* currentPlaylist = nullptr;

    while (std::getline(infile, line)) {
        line.erase(0, line.find_first_not_of("\t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty() || line.find("#") == 0 || line == "End of Playlist") {
            continue;
        }

        if (line.find("Playlist: ") == 0) {
            std::string playListName = line.substr(10);
            currentPlaylist = findPlaylist(playListName);
            if (!currentPlaylist) {
                currentPlaylist = new Playlist(playListName);
                playlists.add(currentPlaylist);
            }
        } else if (currentPlaylist && line.find("ID") != std::string::npos) {
            std::istringstream iss(line);
            std::string surahName, surahType, surahPath;
            iss >> surahName >> surahType >> surahPath;
            Surah newSurah(surahName, surahType, surahPath);
            currentPlaylist->addSurah(newSurah);
        } else {
            std::cerr << "Warning: Skipping malformed line: " << line << std::endl;
        }
    }

    infile.close();
    std::cout << "Playlists successfully loaded from file." << std::endl;
}

void PlaylistManager::addPlaylist(const std::string& name) {
    if (findPlaylist(name)) {
        std::cout << "Playlist already exists: " << name << std::endl;
        return;
    }
    Playlist* newPlaylist = new Playlist(name);
    playlists.InsertEnd(newPlaylist);
}
Playlist* PlaylistManager::findPlaylist(const std::string& name)
{
    Node<Playlist>* current = playlists.getHead();
    while (current) {
        if (current->data.getName() == name) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}

void PlaylistManager::addSurahToPlaylist(const std::string& playlistName, const Surah& surah)
{
    Playlist* playlist = findPlaylist(playlistName);
    playlist->addSurah(surah);
}

void PlaylistManager::displayPlaylists() const
{
    Node<Playlist>* current = playlists.getHead();
    if (!current) {
        std::cout << "No playlists available.\n";
    }

    std::cout << std::setw(10) << std::left << "Id" << std::setw(30) << std::left << "Playlist name" << std::endl;
    std::cout << "===============================================\n";
    int i = 1;
    while (current) {
        std::cout << std::setw(10) << std::left << i << std::setw(30) << std::left << current->data.getName() << std::endl;
        current = current->next;
        i++;
    }
}




void PlaylistManager::RemoveSurah(const std::string& pname, const std::string& sname)
{
    Playlist* playlist = findPlaylist(pname);
    playlist->removeSurah(sname);
}

void PlaylistManager::printTables()
{
    Node<Playlist>* temp = playlists.getHead();
    if (playlists.getHead() == nullptr) {
        std::cout << "No playlists available\n";
    }
    while (temp) {
        temp->data.printPlaylistInfo();
        temp = temp->next;
        std::cout << std::endl;
    }
}
void PlaylistManager::printspecificlist(const std::string& pname) {
    Playlist* playlist = findPlaylist(pname);
    playlist->printPlaylistInfo();
}

void PlaylistManager::RemovePlaylist(const std::string& pname) {
    Playlist* playlist = findPlaylist(pname);
    playlist->RemoveNode(pname);
}

void PlaylistManager::Savetofile(std::ofstream& outfile) {
    Node<Playlist>* current = playlists.getHead();
    while (current) {
        current->data.SavePlaylist(outfile);
        current = current->next;
    }
}

void PlaylistManager::Update(std::string name, std::string sname, int pos) {
    Playlist* playlist = findPlaylist(name);
    playlist->UpdateSurah(sname, pos);
}

void PlaylistManager::play(std::string name) {
    Playlist* playlist = findPlaylist(name);
    std::cout << "Playing playlist: " << name << std::endl;
    playlist->PlayPlaylist();
    std::cout << "Finished playing playlist: " << name << std::endl;
}
