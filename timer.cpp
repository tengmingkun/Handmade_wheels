#include<time.h>
#include<iostream>
#include<vector>
#include<pthread.h>

//g++ -o time timer.cpp -lpthread


using namespace std;
template<class T>
class timer
{
public:
    time_t advance_time;  //预期时间；
    time_t start_time;    //定时器开始时间；             
    bool destory=0;       //判断线程池是否到期；
    T *task;              //定时器要执行的任务
    pthread_t t_pthread;  

public:
    static void* work(void *arg);  //用来线程函数的调用，传this参数；
    void start()
    {   
        start_time=time(nullptr);//设置开始的时间；
        t_pthread=pthread_create(&t_pthread,nullptr,work,this);  //开启线程；
        pthread_detach(t_pthread);  //设为分离线程

    }
    timer(T* t_task):task(t_task) //初始化函数，将任务加进定时器
    {
        cout<<"timer\n";
    }
    ~timer()  //析构函数
    {
        cout<<"~timer"<<endl;
    }
    time_t get_time()   //获取当前时间；
    {
        return time(nullptr);
    }
    void set_time(time_t time)  //设置定时器时间
    {  
        advance_time=time;
    }
    bool judg_time()     //判断定时器是否到时间；
    {  
        time_t now_time=time(nullptr);
        if((start_time+advance_time)<=now_time)  //判断开始时间+定时时间 是否>=现在时间
            {   
                return true;
            }
        return false;
    }
    void run()    //线程在此循环，不断的判断是否到达定时时间；
    {   
        for(; ;)  //循环判定时器是否到期；
        {
            if(judg_time()==true)
                break;
        }
        task->do_work();  //到了就做任务；
        delete task;        //将定时器，和任务释放；
        delete this;
    }
};
template<class T> 
void* timer<T>::work(void *arg)     //类内的线程调用函数；
    {   //cout<<"work\n";
        timer*t_timer=(timer *)arg;
        t_timer->run();
        return t_timer;
    }


class prase
{   
    public:
    int num;
    prase(int nums):num(nums)
    {
    }
    ~prase()
    {
        cout<<"~prase\n";
    }
    void do_work()
    {   
        cout<<num<<endl;
    }
};

int main()
{   
    for(int i=1;i<4;i++)
    {
        prase * myprase=new prase(i);
        timer<prase> * m_time=new timer<prase>(myprase);
        m_time->set_time(i*2);
        m_time->start();

    }
    while(1);
}
