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


template <typename T>
class SharedPtr{
private:
    T* _p;
    int* _count;

public:
    SharedPtr(T* p = nullptr);
    SharedPtr(SharedPtr& other);
    ~SharedPtr(){
        _p = nullptr;
        if(_count){
            --(*_count);
            if(*_count == 0)
                delete _count;
        }
    }
    SharedPtr& operator=(SharedPtr& other);

    T& operator*();
    T* operator->();
    operator bool() const;

    T* get();
    int use_count();
    void reset(T* p = nullptr);
};


template <typename T>
SharedPtr<T>::SharedPtr(T* p){
    _p = p;
    if(_p)
        _count = new int{1};
    else
        _count = new int{0};
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr& other){
    if(&other == this)return;
    if(other._p == nullptr){
        _p = nullptr;
        _count = new int{0};
        return;
    }
    _p = other._p;
    _count = other._count;
    (*_count)++;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>& other){
    if(&other == this)return *this;
    this->~SharedPtr();
    _p = other._p;
    _count = other._count;
    (*_count)++;
    return *this;
}

template <typename T>
T& SharedPtr<T>::operator*(){
    return *_p;
}

template <typename T>
T* SharedPtr<T>::operator->(){
    return _p;
}

template <typename T>
SharedPtr<T>::operator bool() const{
    return _p != nullptr;
}

template <typename T>
T* SharedPtr<T>::get(){
    return _p;
}

template <typename T>
int SharedPtr<T>::use_count(){
    return *_count;
}

template <typename T>
void SharedPtr<T>::reset(T *p){
    if(_p){
        --(*_count);
        if(*_count == 0){
            this->~SharedPtr();
        }
    }
    _p = p;
    if(_p)
        _count = new int{1};
    else
        _count = new int{0};
}


template <typename T>
SharedPtr<T> make_shared(T val){
    return SharedPtr<T>(new T{val});
}

#endif //SHARED_PTR