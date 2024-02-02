#ifndef UNIQUE_PTR
#define UNIQUE_PTR

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
UniquePtr<T> make_unique(T value){
    return UniquePtr<T>{new T{value}};
}



#endif //UNIQUE_PTR