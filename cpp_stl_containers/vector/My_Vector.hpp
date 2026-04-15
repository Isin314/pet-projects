#pragma once
#include <initializer_list>
#include <algorithm>

template<typename T>
class Reverse_iterator{
    private:
    T* _current;
    public:
    Reverse_iterator(T* ptr) : _current(ptr){}
    Reverse_iterator& base() const{
        return _current;
    }
    T& operator*() const{
        return *(_current-1);
    }
    Reverse_iterator& operator++(){
        --_current;
        return *this;
    }
    Reverse_iterator& operator--(){
        ++_current;
        return *this;
    }
    bool operator!=(const Reverse_iterator& other) const{
        return _current != other._current;
    }
    bool operator==(const Reverse_iterator& other) const{
        return _current == other._current;
    }
};

template<typename T>
class My_vector{
    private:
        T* _vector;
        size_t _size;
        size_t _capacity;
        using reverse_iterator = Reverse_iterator<T>;
        using const_reverse_iterator = Reverse_iterator<const T>;

    public:
    My_vector(): _size(0),_capacity(1){
        _vector = new T[_capacity];
    }
    My_vector(std::initializer_list<T> l): _size(l.size()),_capacity(l.size()){
        _vector = new T[_capacity];
        size_t i = 0;
        for(auto elem : l){
            _vector[i] = elem;
            ++i;
        }
    }
    T& operator[](unsigned index)
    {
        return _vector[index];
    }
    const T& operator[](unsigned index) const
    {
        return _vector[index];
    }
    ~My_vector()
    {
        delete[] _vector;
    }
    T* begin() const noexcept{
        return _vector;
    }
    const T* cbegin() const noexcept{
        return _vector;
    }
    T* end() const noexcept{
        return _vector + _size;
    }
    const T* cend() const noexcept{
        return _vector + _size;
    }
    reverse_iterator rbegin() const noexcept{
        return reverse_iterator(_vector+_size);
    }
    reverse_iterator rend() const noexcept{
        return reverse_iterator(_vector);
    }
    const const_reverse_iterator crbegin() const noexcept{
        return const_reverse_iterator(_vector+_size);
    }
    const const_reverse_iterator crend() const noexcept{
        return const_reverse_iterator(_vector);
    }
    bool empty() const noexcept{
        return !_size;
    }
    size_t size() const noexcept{
        return _size;
    }
    size_t capacity() const noexcept{
        return _capacity;
    }
    T& at(size_t index){
        if(index >= _size)
            throw std::out_of_range("index out of range");
        return _vector[index];
    }
    void push_back(const T& elem){
        if(_size >= _capacity)
            this->reserve(_capacity*2);
        _vector[_size] = elem;
        _size+=1;
    }
    void clear(){
    _size = 0;
    }
    void assign(std::initializer_list<T> l){
        _size = l.size();
        _capacity = l.size();
        delete[] _vector;
        _vector = new T[_capacity];
        size_t i = 0;
        for(auto elem : l){
            _vector[i] = elem;
            ++i;
        }
    }
    void reserve(size_t capacity){
        if (capacity == _capacity)
            return;

        T* _vector_reserve = new T[capacity];
        std::copy(_vector,_vector+_size,_vector_reserve);
        delete[] _vector;
        _vector = _vector_reserve;
        _capacity = capacity;
    }

};

