#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
namespace YSTest
{
    
   class Thread
   {
        public:
            Thread(/* args */);
            virtual ~Thread();
            virtual void StartThread(void);
            virtual void OnThreadRun(void);
        private:
            int m_thread_id;
   };
   
   
}
#endif