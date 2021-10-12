#include<vector>
#include<string>
#include<iostream>
#include<memory>
//g++ -o shread_ptr shread_ptr.cpp 

using namespace std;
template<class T>
class M_shread_ptr
{
private:
    T * data;
    int *count;
public:
    M_shread_ptr(T *t_data=nullptr)  //构造；
    {   
        data=t_data;
        if(data==nullptr)
        {
            count=new int(0);
        }
        else 
        {
            count=new int(1);
        }
    }
    ~M_shread_ptr()  //析构；
    {
        if(data!=nullptr)
        {
            (*count)--;
            if((*count)==0)
            {   
                delete this->data;
                delete this->count;
                this->data=nullptr;
                this->count=nullptr;
            }
        }
    }
    M_shread_ptr(const M_shread_ptr &rhs)  //复制构造
    {       
            if(this!=&rhs)
            {
                count=rhs.count;
                data=rhs.data;
                (*count)++;
            }
        

    }
    M_shread_ptr& operator=(const M_shread_ptr &rhs)
    {
        if(this==&rhs)
        {
            return *this;
        }
        if(this->data!=nullptr)
        {
            if((*count)--==0)
            {
                delete data;
                delete count;
                data=nullptr;
                count=nullptr;
            }

        }
        data=rhs.data;
        count=rhs.count;
        (*count)++;
        return *this;
        
    }
    T& operator->()
    {
        if(data)
            return *data;
    }

    int use_count()
    {
        return *count;
    }
};
class node
{
private:
    /* data */
public:
    node(/* args */);
    ~node();
};

node::node(/* args */)
{
}

node::~node()
{
    cout<<"I was deleted"<<endl;
}

int main()
{
   {
    M_shread_ptr<node> ptr;
    cout<<ptr.use_count()<<endl;
    M_shread_ptr<node> ptr2(new node);
    cout<<ptr2.use_count()<<endl;
    M_shread_ptr<node> ptr3(ptr2);
    cout<<ptr2.use_count()<<endl;
    cout<<ptr3.use_count()<<endl;

    ptr3=ptr;
    cout<<ptr2.use_count()<<endl;
    cout<<ptr3.use_count()<<endl;
   }
    //shared_ptr<string> ptr(new string("123"));

    while(1);

}