#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;


class Applicition
{
    std::mutex m_mutex;
    std::condition_variable m_conVar;
    bool m_bDataLoaded;
public:
    Applicition(){
        m_bDataLoaded = false;
    }
    void loadData()
    {
        std::this_thread::sleep_for(std::chrono::microseconds(10000000));
        std::cout<<"LoadData from Xml"<<std::endl;

        std::lock_guard<std::mutex> guard(m_mutex);

        m_bDataLoaded = true;
        m_conVar.notify_one();
    }
    bool isDataLoaded()
    {
        return m_bDataLoaded;
    }

    // void mainTask()
    // {
    //     std::cout<<"Do SomeThing Handshaking"<<std::endl;
    //     m_mutex.lock();

    //     while(m_bDataLoaded != true)
    //     {
    //         m_mutex.unlock();
    //         std::this_thread::sleep_for(std::chrono::microseconds(100));
    //         std::cout<<"Do SomeThing Handshaking1111111"<<std::endl;
    //         m_mutex.lock();
    //     }
    //     m_mutex.unlock();

    //     std::cout<<"Do Process On Load Data"<<std::endl;
    // }

     void mainTask()
    {
        std::cout<<"Do SomeThing Handshaking"<<std::endl;
        std::unique_lock<std::mutex> mlock(m_mutex);

        m_conVar.wait(mlock,std::bind(&Applicition::isDataLoaded,this));
        
        std::cout<<"Do Process On Load Data"<<std::endl;
    }
    virtual ~Applicition(){};
};

#endif