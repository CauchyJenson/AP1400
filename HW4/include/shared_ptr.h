#ifndef SHARED_PTR
#define SHARED_PTR

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

    T& operator*();
    T* operator->();

    T* get();
    int use_count();
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
T& SharedPtr<T>::operator*(){
    return *_p;
}

template <typename T>
T* SharedPtr<T>::operator->(){
    return _p;
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
SharedPtr<T> make_shared(T val){
    return SharedPtr<T>(new T{val});
}

#endif //SHARED_PTR