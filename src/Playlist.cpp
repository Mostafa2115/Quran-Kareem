#include "Surah.h"
#include "Dlinkedlist.h"
#include "Playlist.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <istream>
#include <iomanip>
#include <irrKlang.h>
using namespace irrKlang;

PlayList::PlayList(std::string pname){
    name = pname;
}

PlayList::~PlayList() {}

std::string PlayList::getName() const {
    return name;
}

void PlayList::addSurah(const Surah& surah){
    if (findSurah(surah.getName())) {
        std::cout << "Surah already exists: " << std::endl;
        return;
    }
    surahList.InsertEnd(surah);
}

Surah* PlayList::findSurah(const std::string& name){
    Node<Surah>* temp = surahList.getHead();
    while (temp) {
        if (temp->data.getName() == name) {
            return &temp->data;
        }
        temp = temp->next;
    }
    return nullptr;
}

void PlayList::removeSurah(std::string sname) {
    if (!surahList.getHead()) {
        std::cout << "Error: Cannot remove from an empty playlist.\n";
        return;
    }
    Surah* S1 = findSurah(sname);
    if (S1) {
        surahList.RemoveNode(sname);
        std::cout << "Surah " << sname << " removed from the playlist.\n";
    } else {
        std::cout << "Error: Surah " << sname << " not found in the playlist.\n";
    }
}

void PlayList::printHead() const {
    std::cout << "\nPlayList: " << name << std::endl;
    for (int i = 0; i <= 70; i++) {
        std::cout << "*";
    }
    std::cout << std::endl;
    std::cout << std::setw(10) << std::left << "ID"
              << std::setw(20) << std::left << "Surah Name"
              << std::setw(20) << std::left << "Type"
              << std::setw(40) << std::left << "Path" << std::endl;
    for (int i = 0; i <= 70; i++) {
        std::cout << "*";
    }
    std::cout << std::endl;
}


void Playlist::printPlaylistInfo(){
    Node<Surah>* current = surahList.getHead();
    if (surahList.getHead() == nullptr) {
        std::cout << "No surah available\n";
    }
    else {
        printHead();
        for (int i = 0; i < surahList.getSize(); i++) {
            std::cout << std::setw(10) << std::setfill(' ') << std::left << i + 1;
            current->data.printSurahInfo();
            current = current->next;
        }
        std::cout << std::string(70, '-') << "\n";
        std::cout << std::endl;
    }
}

void Playlist::SavePlaylist(std::ofstream& outfile){
    Node<Surah>* current = surahList.getHead();
    outfile << "\t\tPlaylist: " << name << std::endl;
    outfile << std::string(70, '-') << "\n";
    outfile << std::endl;
    outfile << std::setw(10) << std::setfill(' ') << std::left << "ID";
    outfile << std::setw(20) << std::setfill(' ') << std::left << "Surah Name";
    outfile << std::setw(10) << std::setfill(' ') << std::left << "Type";
    outfile << std::setw(40) << std::setfill(' ') << std::left << "Path";
    outfile << std::endl;
    outfile << std::string(70, '-') << "\n";
    outfile << std::endl;
    for (int i = 0; i < surahList.getSize(); i++) {
        outfile << std::setw(10) << std::setfill(' ') << std::left << i + 1;
        current->data.SaveSurahData(outfile);
        current = current->next;
    }
    outfile << std::endl;
    outfile << "End of Playlist\n\n";
}

void Playlist::UpdateSurah(std::string name, int pos){
    if (pos < 1 || pos > surahList.getSize()) {
        std::cout << "Invalid position. Position should be between 1 and " << surahList.getSize() << ".\n";
    }
    else {
        Node<Surah>* current = surahList.getHead();
        Node<Surah>* temp = surahList.getHead();
        while (current && current->data.getName() != name) {
            current = current->next;
        }
        for (int i = 0; i < pos - 1 && temp; i++) {
            temp = temp->next;
        }
        if (current && temp) {
            std::swap(temp->data, current->data);
        }
        else {
            std::cout << "Surah not found.\n";
        }
    }
}
void PlayList::PlayPlaylist()
{
    Node<Surah>* current = surahList.getHead();
    if (current==nullptr)
    {
        std::cout << "Playlist is empty. Add some Surahs to Play."<<std::endl;
        return;
    }
    else
    {
        surahList.playSound(true);
    }
}





