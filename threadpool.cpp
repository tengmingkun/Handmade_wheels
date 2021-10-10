// #include"threadpool.h"
// #include<sys/time.h>
// #include<cstdio>
// template<class T>
// threadpool<T>::threadpool(int t_thread_num,int t_max_task):thread_num(t_thread_num),max_task(t_max_task),
// stop(false),threads(nullptr)
// {   
//     threads=new pthread_t[thread_num];
    
// }

// template<class T>
// void threadpool<T>::start()  //启动线程池
// {
//     for(int i=0;i<thread_num;i++)
//     {
//         pthread_create(threads+1,nullptr,worker,this);
//         pthread_detach(threads[i]);
//     }
// }
// template<class T>
// threadpool<T>::~threadpool()
// {
//     stop=true;
//     delete []threads;
// }
// template<class T>
// bool threadpool<T>::task_append(T* task)
// {
//     queue_mutex.lock();
//     if(worklist.size()>max_task)
//         {
//             std::cout<<"append_error";
//             queue_mutex.unlock();
//             return false;
//         }
//     worklist.push_back(task);  //添加；
//     queue_sem.post();
//     queue_mutex.unlock();
//     return true;
// }

// template<class T>
// void* threadpool<T>::worker(void *arg)
// {
//     threadpool *pool=(threadpool*) arg;
//     pool->run();
//     return pool;
// }

// template<class T>
// void threadpool<T>::run()
// {
//     while(!stop)
//     {
//         queue_sem.wait();
//         queue_mutex.lock();
//         if(worklist.size()==0)
//             {
//                 queue_mutex.unlock();
//                 continue;
//             }
//         T* task=worklist.front();
//         worklist.pop_front();
//         queue_mutex.unlock();
//         if(task==nullptr)
//             continue;
//         task->process();

//     }

// }
