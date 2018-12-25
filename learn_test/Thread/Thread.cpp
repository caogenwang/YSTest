#include "Thread.h"
namespace YSTest
{
    Thread::Thread(/* args */)
   {
       m_thread_id = 0;
   }
   
   Thread::~Thread()
   {
   }
   void Thread::StartThread()
   {
       void CreatThread(NULL,0,StartRoutine,this,0,&m_thread_id);
   } 

}
