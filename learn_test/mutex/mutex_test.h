#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;
class Wallet{
    int mMoney;
    std::mutex m;
    public:
        Wallet():mMoney(0){}
        int getMoney(){return mMoney;}
        void addMonry(int money)
        {
            std::lock_guard<std::mutex> lockGuard(m);
            for(int i = 0;i < money;i ++)
            {
                mMoney ++;
            }
        }
};

int testMultithreadWallet(){
    Wallet walletOBject;
    std::vector<std::thread> threads;
    for(int i = 0;i < 5;i ++)
    {
        threads.push_back(std::thread(&Wallet::addMonry,&walletOBject,1000));
    }

    for(int i = 0;i < threads.size();i ++)
    {
        threads.at(i).join();
    }
    int mMoney = walletOBject.getMoney();
    return mMoney;
}
int testSingleThreadWallet()
{
    Wallet walletObject;
    thread t(&Wallet::addMonry,&walletObject,500);
    t.join();
    int mMoney = walletObject.getMoney();
    return mMoney;
}