#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include<memory>
#include<iostream>
using std::make_unique;

template<typename T>
class UniquePtr
{
private:
    /* data */
    T* _p = nullptr;
    
public:
    UniquePtr(): _p(nullptr){}
    UniquePtr(T* p): _p(p){}
    UniquePtr(std::unique_ptr<T> ptr): _p(ptr.release()){}
    UniquePtr(UniquePtr<T>& p){};
    UniquePtr operator=(const UniquePtr& p){};

    ~UniquePtr(){
        delete _p;
        _p = nullptr;
    }

    T* get(){
        return _p;
    }

    T& operator*(){
        return *_p;
    }

    T* operator->(){
        return _p;
    }

    void reset(){
        delete _p;
        _p = nullptr;
    }

    void reset(T* t){
        delete _p;
        _p = t;
    }

    T* release(){
        auto tmp = _p;
        _p = nullptr;
        return tmp;
    }

    operator bool()const{return _p != nullptr;}
    
};











#endif //UNIQUE_PTR