#ifndef SHARED_PTR
#define SHARED_PTR
#include<memory>
using std::make_shared;


template<typename T>
class SharedPtr
{

public:
    T* _p;
    size_t* p_counter;
    //Constructor
    SharedPtr():_p(nullptr){p_counter = new size_t(0);}
    SharedPtr(T* p):_p(p){p_counter = new size_t(1);}
    SharedPtr(std::shared_ptr<T> p){
        _p = new T(*p.get());
        p_counter = new size_t(1);
    }
    SharedPtr(SharedPtr& p){
        ++(*p.p_counter);
        p_counter = p.p_counter;
        _p = p._p;
    }

    ~SharedPtr()
    {
        if(*p_counter > 0){
            _p = nullptr;
            --(*p_counter);
            return;
        }
    }
    
    size_t use_count(){
        return *p_counter;
    }
    T* get(){
        return _p;
    }

    SharedPtr& operator=(SharedPtr& sp){
        if(_p != sp.get()){
            _p = sp.get();
            ++ (*sp.p_counter);
            p_counter = sp.p_counter;
        }
        return *this;
        
    }

    T& operator*(){return *_p;}

    T* operator->(){return _p;}

    void reset(){
        delete _p;
        _p = nullptr;
        *p_counter = 0;
    }

    void reset(T* p){
        delete _p;
        _p = p;
        *p_counter = 1;
    }
    
    operator bool(){return _p != nullptr;}
};



#endif //SHARED_PTR