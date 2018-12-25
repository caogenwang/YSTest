

#include "con_prodce.h"

mutex mtx;
condition_variable con_produce,con_consume;

queue<int> q;
int maxSize = 1000;
// bool shipment() 
// {
//     return q.size() != 0;
// }
void consumer()
{
    while(true)
    {
       
        this_thread::sleep_for(chrono::milliseconds(3000));
        cout<<"consumer start"<<endl;
        unique_lock<mutex> lck(mtx);
        con_consume.wait(lck,[]{return q.size() != 0;});

        cout<<"consumer:"<<this_thread::get_id()<<":";
        cout<<"num:"<<q.front()<<endl;
        q.pop();
        cout<<"size:"<<q.size()<<endl;
        con_produce.notify_all();
    }
}

void producer(int id)
{
    cout<<q.size()<<endl;
    while(true)
    {
        
        this_thread::sleep_for(chrono::milliseconds(1500));
        cout<<"produce start"<<endl;
        unique_lock<mutex> lck(mtx);

        con_produce.wait(lck,[]{return q.size() == 0;});
        cout<<"procuce:"<<this_thread::get_id()<<":";
        q.push(id);
        cout<<q.size()<<endl;
        con_consume.notify_all();
    }
}
