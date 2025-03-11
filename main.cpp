#include <string>
#include "DLinkedList.h"
#include "PlayList.h"
#include "PlayListManager.h"
#include "Surah.h"
int main()
{
    PlayListManager manager;
    while (true)
    {
        std::cout << "\t\t\t\t";
        for (int i = 0; i < 63; i++)
        {
            std::cout << "=";
        }
        std::cout << "<" << std::endl
                  << "\t\t\t\tQuraan PlayList manager menu\t\t\t\n";
        std::cout << "\t\t\t\t";
        for (int i = 0; i < 63; i++)
        {
            std::cout << "=";
        }
        std::cout << "\n\t\t\t\t 1. Add a new playlist\t\t\t\t\n"
                  << "\t\t\t\t 2. Add Surah to an existing playlist\t\t\t\n"
                  << "\t\t\t\t 3. Remove Surah from an existing playlist\t\t\t\n"
                  << "\t\t\t\t 4. Update the order of an existing playlist\t\t\t\n"
                  << "\t\t\t\t 5. Display all current playlists names\t\t\t\n"
                  << "\t\t\t\t 6. Display All playlists surah\t\t\t\n"
                  << "\t\t\t\t 7. Display Surah in a specific playlist\t\t\t\n"
                  << "\t\t\t\t 8. Play Surah from a specific playlist\t\t\t\n"
                  << "\t\t\t\t 9. Use Left arrow (<-) to play the previous surah\t\t\t\n"
                  << "\t\t\t\t 10. Use right arrow (->) to play the next surah\t\t\t\n"
                  << "\t\t\t\t 11. Use up arrow (^) to pause the current surah\t\t\t\n"
                  << "\t\t\t\t 12. Use down arrow (v) to resume the current surah\t\t\t\n"
                  << "\t\t\t\t 13. Press q to exit current playlist & return back to menu\t\t\t\n"
                  << "\t\t\t\t 14. Save playlists to a file\t\t\t\n"
                  << "\t\t\t\t 15. Load playlists from a file\t\t\t\n"
                  << "\t\t\t\t 16. Remove an existing playlist\t\t\t\n"
                  << "\t\t\t\t 17. Exit\t\t\t\t\n";
        std::cout << "\t\t\t\t";
        for (int i = 0; i < 63; i++)
        {
            std::cout << "=";
        }
        std::cout << "\n";

        int choice;
        std::cout << "\n";
        std::cout << "\t\t\t\tYour choise: ";
        std::cin >> choice;
        if (choice == 1)
        {
            std::string pname;
            std::cout << "Enter a playlist name: ";
            std::cin >> pname;
            manager.addPlayList(pname);
            if (manager.findPlayList(pname))
            {
                std::cout << "Playlist of name: " << pname << " added successfully\n";
            }
            else
            {
                std::cout << "Can not add this playlist\n";
            }
        }
        else if (choice == 2)
        {
            std::string pname, sname, stype, spath;
            std::cout << "The current playlists are:\n";
            manager.displayPlayLists();
            std::cout << std::endl;
            std::cout << "Enter playlist name: ";
            std::cin >> pname;
            if (manager.findPlayList(pname))
            {
            here:
                std::cout << "Enter Surah name: ";
                std::cin >> sname;
                std::cout << "Enter Surah type: ";
                std::cin >> stype;
                std::cout << "Enter Surah path: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(std::cin, spath);
                std::cout << std::endl;
                Surah newSurah(sname, stype, spath);
                manager.addSurahToPlayList(pname, newSurah);
                if (manager.findSurah(pname, sname))
                {
                    std::cout << "Surah of name: " << sname << " added successfully\n";
                    std::cout << "Do you want to add another surah to the current playlist (y/n): ";
                    char again;
                    std::cin >> again;
                    if (again == 'y')
                        goto here;
                }
                else
                {
                    std::cout << "Can not add this Surah\n";
                }
            }
            else
            {
                std::cout << "PlayList not founded\n";
            }
        }

        else if (choice == 3)
        {
            std::string pname, sname;
            std::cout << "The current playlists are:\n";
            manager.displayPlayLists();
            std::cout << std::endl;
            std::cout << "Enter playlist name: ";
            std::cin >> pname;
            std::cout << std::endl;
            if (manager.findPlayList(pname))
            {
                manager.printspecificlist(pname);
                std::cout << "Enter Surah name: ";
                std::cin >> sname;
                manager.RemoveSurah(pname, sname);
                std::cout << std::endl;
                if (!manager.findSurah(pname, sname))
                {
                    std::cout << "Surah of name: " << sname << " Removed successfully\n\n";
                    manager.printspecificlist(pname);
                }
                else
                {
                    std::cout << "Can not remove this Surah\n";
                }
            }
            else
            {
                std::cout << "PlayList not founded\n";
            }
        }
        else if (choice == 4)
        {
            int position;
            std::string pname, sname;
            std::cout << "The current playlists are:\n";
            manager.displayPlayLists();
            std::cout << std::endl
                      << "Enter PList name: ";
            std::cin >> pname;
            std::cout << std::endl;
            if (manager.findPlayList(pname))
            {
                manager.printspecificlist(pname);
                std::cout << "Enter Surah name: ";
                std::cin >> sname;
                std::cout << "Enter new position: ";
                std::cin >> position;
                std::cout << std::endl;
                manager.Update(pname, sname, position);
                manager.printspecificlist(pname);
            }
            else
            {
                std::cout << "PlayList not founded\n";
            }
        }

        else if (choice == 5)
        {
            std::cout << "The current playlists are:\n";
            std::cout << std::endl;
            manager.displayPlayLists();
        }

        else if (choice == 6)
        {
            manager.printTables();
        }

        else if (choice == 7)
        {
            std::string pname;
            std::cout << "The current playlists are:\n";
            std::cout << std::endl;
            manager.displayPlayLists();
            std::cout << std::endl
                      << "Enter PList name: ";
            std::cin >> pname;
            std::cout << std::endl;
            if (manager.findPlayList(pname))
            {
                manager.printspecificlist(pname);
            }
            else
            {
                std::cout << "PlayList not founded\n";
            }
        }

        else if (choice == 8)
        {
        hi:
            std::string pname;
            std::cout << "The current playlists are:\n";
            manager.displayPlayLists();
            std::cout << "Enter the playlist name to play: ";
            std::cin >> pname;
            if (manager.findPlayList(pname))
            {
                manager.play(pname);
                std::cout << "Do you want to display another playlist? (y/n): ";
                char again;
                std::cin >> again;
                if (again == 'y' || again == 'Y')
                {
                    goto hi;
                }
            }
        }
        char again;
        std::cin >> again;
        if (again == 'y' || again == 'Y')
        {
            goto hi;
        }
        else
        {
            std::cout << "Returning to the main menu." << std::endl;
        }

        else
        {
            std::cout << "Playlist not founded\n";
        }

        else if (choice == 9)
        {
            std::ofstream datafile("Quran.txt");
            if (datafile.is_open())
            {
                manager.SaveToFile(datafile);
                datafile.close();
                std::cout << "P\\laylist Saved\n";
            }
        }

        else if (choice == 10)
        {
            try
            {
                manager.LoadPlaylist("Quran.txt");
                std::cout << "Now! The current playlists are:\n";
                std::cout << std::endl;
                manager.displayPlaylists();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }

        else if (choice == 11)
        {
            std::string pname;
            std::cout << "The current playlists are:\n";
            std::cout << std::endl;
            manager.displayPlaylists();
            std::cout << "Enter Playlist name: ";
            std::cin >> pname;
            if (manager.findPlaylist(pname))
            {
                manager.RemovePlaylist(pname);
                std::cout << "Playlist of name: " << pname << " Removed successfully\n\n";
                if (manager.findPlaylist(pname))
                {
                    std::cout << "Now! The current playlists are:\n";
                    std::cout << std::endl;
                    manager.displayPlaylists();
                }
            }
            else
            {
                std::cout << "Playlist not founded\n";
            }
        }

        else if (choice == 12)
        {
            std::cout << "Thanks for your visit";
            break;
        }
        else
        {
            std::cout << "Invalid choice, try again.\n";
        }
        return 0;
    }
}
