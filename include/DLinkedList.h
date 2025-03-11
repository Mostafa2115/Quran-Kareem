#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include <iostream>
#include <irrKlang.h>
#include <thread>
#include <chrono>
#include <conio.h>

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *pre;
    Node(T value) : data(value), next(nullptr), pre(nullptr) {}
};

template <typename T>
class DLinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;
    size_t size;

public:
    DLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~DLinkedList()
    {
        while (head)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    void InsertBeg(T value)
    {
        Node<T> *new_node = new Node<T>(value);
        if (!head)
        {
            head = tail = new_node;
        }
        else
        {
            new_node->next = head;
            head->pre = new_node;
            head = new_node;
        }
        size++;
    }

    void InsertEnd(T value)
    {
        Node<T> *new_node = new Node<T>(value);
        if (!head)
        {
            InsertBeg(value);
        }
        else
        {
            new_node->pre = tail;
            tail->next = new_node;
            tail = new_node;
            size++;
        }
    }

    Node<T> *getHead() const
    {
        return head;
    }
    size_t getSize() const { return size; }

    void RemoveNode(std::string name)
    {
        if (head == nullptr)
        {
            std::cout << "Empty List\n";
            return;
        }
        else if (head == tail && head != nullptr)
        {
            Node<T> *temp = head;
            head = nullptr;
            tail = nullptr;
            delete temp;
            size--;
        }
        else
        {
            Node<T> *temp = head;
            while (temp->data.getName() != name)
            {
                temp = temp->next;
            }
            if (temp->pre == nullptr)
            {
                head = temp->next;
                temp->next->pre = nullptr;
            }
            else if (temp->next == nullptr)
            {
                tail = temp->pre;
                temp->pre->next = nullptr;
            }
            else
            {
                temp->pre->next = temp->next;
                temp->next->pre = temp->pre;
            }
            delete temp;
            size--;
        }
    }

    void playSound(bool playAll = false)
    {
        if (!head)
        {
            std::cerr << "Playlist is empty!" << std::endl;
            return;
        }
        irrklang::ISoundEngine *engine = irrklang::createIrrKlangDevice();
        if (!engine)
        {
            std::cerr << "Error: Could not initialize irrKlang engine!" << std::endl;
            return;
        }
        Node<T> *temp = head;
        irrklang::ISound *sound = nullptr;
        bool exitPlayback = false;
        while (temp && !exitPlayback)
        {
            if (sound)
            {
                sound->stop();
                sound->drop();
                sound = nullptr;
            }
            sound = engine->play2D(temp->data.getPath().c_str(), false, false, true);
            if (!sound)
            {
                std::cerr << "Error: Could not play sound!" << std::endl;
                break;
            }
            std::cerr << "Error: Could not play sound!" << std::endl;
            break;
        }
        std::cout << "Now playing: " << temp->data.getPath() << std::endl;
        bool isPaused = false;
        while (sound->isFinished() == false && !exitPlayback)
        {
            if (_kbhit())
            {
                char ch = _getch();
                if (ch == 77)
                {
                    std::cout << "Next sound.." << std::endl;
                    temp = temp->next ? temp->next : (playAll ? head : temp);
                    break;
                }
                else if (ch == 75)
                {
                    std::cout << "Previous sound.." << std::endl;
                    temp = temp->pre ? temp->pre : temp;
                    break;
                }
                else if (ch == 72)
                {
                    if (!isPaused)
                    {
                        sound->setPaused(true);
                        isPaused = true;
                        std::cout << "Sound paused." << std::endl;
                    }
                }
                else if (ch == 80)
                {
                    if (isPaused)
                    {
                        sound->setPaused(false);
                        isPaused = false;
                        std::cout << "Sound resumed." << std::endl;
                    }
                }
                else if (ch == 'q')
                {
                    std::cout << "Exiting playback..." << std::endl;
                    exitPlayback = true;
                    break;
                }
                else if (ch == '+')
                {
                    float volume = sound->getVolume();
                    sound->setVolume(std::min(1.0f, volume + 0.1f));
                    std::cout << "Volume increased to " << sound->getVolume() << std::endl;
                }
                else if (ch == '-')
                {
                    float volume = sound->getVolume();
                    sound->setVolume(std::max(0.0f, volume - 0.1f));
                    std::cout << "Volume decreased to " << sound->getVolume() << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            if (playAll && sound && sound->isFinished())
            {
                temp = temp->next ? temp->next : head;
            }
        }
        if (sound)
            sound->drop();
        engine->drop();
    }
};
#endif
