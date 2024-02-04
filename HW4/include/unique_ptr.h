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

template <typename T>
class UniquePtr{
private:
    T* _p;

public:
    // default constructor
    UniquePtr(T* p = nullptr): _p(p){};
    // destructor
    ~UniquePtr(){
        if(_p)
            delete _p;
    };

    void reset(T* p = nullptr);
    T* release();

    T* get();
    T& operator*();
    T* operator->();
    operator bool() const;
    
};

template <typename T>
T* UniquePtr<T>::get(){
    return _p;
}

template <typename T>
T& UniquePtr<T>::operator*(){
    return *_p;
}

template <typename T>
T* UniquePtr<T>::operator->(){
    return _p;
}

template <typename T>
UniquePtr<T>::operator bool() const{
    return _p != nullptr;
}

template <typename T>
void UniquePtr<T>::reset(T* p){
    if(_p)delete _p;
    _p = p;
}

template <typename T>
T* UniquePtr<T>::release(){
    auto p = this->_p;
    this->_p = nullptr;
    return p;
}


template <typename T>
UniquePtr<T> make_unique(T value){
    return UniquePtr<T>{new T{value}};
}



#endif //UNIQUE_PTR