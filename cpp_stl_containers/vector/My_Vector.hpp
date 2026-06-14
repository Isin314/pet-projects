#pragma once
#include <initializer_list>
#include <algorithm>

template<class T,class Allocator = std::allocator<T>>
class My_Vector{
    public:
    //types
    using value_type = T;
    using allocator_type = Allocator;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    private:
    pointer vector_;
    size_type size_;
    size_type capacity_;
    allocator_type alloc_;

    public:
    //construct/copy/move/destroy
    My_Vector(): My_Vector(Allocator())
    {}

    explicit My_Vector(const Allocator& alloc) 
    : alloc_(alloc), size_(0), capacity_(0), vector_(nullptr)
    {}

    explicit My_Vector(size_type n, const Allocator& alloc = Allocator()) 
    : alloc_(alloc), size_(n),capacity_(n)
    {
        vector_ = alloc_.allocate(capacity_);
        for(size_type i=0;i < size_;++i)
            alloc_.construct(vector_+i,value_type());
    }

    My_Vector(size_type n, const T& value, const Allocator& alloc = Allocator()) 
    : alloc_(alloc), size_(n),capacity_(n)
    {
        vector_ = alloc_.allocate(capacity_);
        for(size_type i=0;i < size_;++i)
            alloc_.construct(vector_+i,value);
    }

    template<class InputIter>
    My_Vector(InputIter first, InputIter last, const Allocator& alloc= Allocator(),
            typename std::enable_if<!std::is_integral<InputIter>::value>::type* = 0)
    : alloc_(alloc), size_(std::distance(first,last)), capacity_(std::distance(first,last)) 
    {
        vector_ = alloc_.allocate(capacity_);
        size_type i=0;
        for(InputIter it{first}; it != last;++it)
        {
            alloc_.construct(vector_+i,*it);
            ++i;
        }
    }

    // template<container-compatible-range<T> R> не реализую так как пока не понимаю (c++20)
    // My_Vector(from_range_t, R&& rg, const Allocator& = Allocator()){}

    My_Vector(const My_Vector& x)
    : alloc_(std::allocator_traits<Allocator>::select_on_container_copy_construction(x.alloc_)), 
    size_(x.size_), capacity_(x.size_)
    {
        vector_ = alloc_.allocate(capacity_);
        for(size_type i=0;i<size_;++i)
            alloc_.construct(vector_+i,x[i]);
    }

    My_Vector(My_Vector&& x) noexcept
    : alloc_(std::allocator_traits<Allocator>::select_on_container_copy_construction(x.alloc_)),
     size_(x.size_), capacity_(x.size_), vector_(x.vector_)
    {
        x.vector_ = nullptr;
        x.size_ = 0;
    }
    // My_Vector(const My_Vector&, const type_identity_t<Allocator>&){} // пока не трогаю так как c++20
    // My_Vector(My_Vector&&, const type_identity_t<Allocator>&) {} // не трогаю так как с++20
    
    My_Vector(std::initializer_list<T> l, const Allocator& alloc = Allocator())
    : size_(l.size()), capacity_(l.size()), alloc_(alloc)
    {
        vector_ = alloc_.allocate(capacity_);
        size_type i = 0; 
        for(const value_type& elem : l)
        {
            alloc_.construct(vector_+i,elem);
            ++i;
        }
    }
    private:
    void dealloc()
    {
        if(vector_ != nullptr)
        {
            #if __cplusplus >= 201703L
            std::destroy(vector_,vector_+size_);
            #else
            for(size_type i=0; i < size_;++i)
            {
                alloc_.destroy(vector_+i);
            }
            #endif
            alloc_.deallocate(vector_,capacity_);
            vector_ = nullptr;
        }
    }
    public:
    ~My_Vector()
    {
        dealloc();
    }

    My_Vector& operator=(const My_Vector& x) 
    {
        dealloc();
        size_ = x.size_;
        capacity_ = x.size_;
        alloc_ = std::allocator_traits<Allocator>::select_on_container_copy_construction(x.alloc_);
        
        vector_ = alloc_.allocate(capacity_);
        for(size_type i=0;i<size_;++i)
        {
            alloc_.construct(vector_+i,x[i]);
        }   
        return *this;
    }
    My_Vector& operator=(My_Vector&& x) noexcept 
    {
        dealloc();
        size_ = x.size_;
        capacity_ = x.size_;
        alloc_ = x.alloc_;
        vector_ = x.vector_;
        x.vector_ = nullptr;
        x.size_=0;
        return *this;
    }

    My_Vector& operator=(std::initializer_list<T> l) 
    {
        dealloc();
        size_ = l.size();
        capacity_ = l.size();
        vector_ = alloc_.allocate(capacity_);
        size_type i = 0; 
        for(const value_type& elem : l)
        {
            alloc_.construct(vector_+i,elem);
            ++i;
        }
        return *this;
    }

    template<class InputIter>
    void assign(InputIter first, InputIter last,
            typename std::enable_if<!std::is_integral<InputIter>::value>::type* = 0) 
    {
        dealloc();
        size_ = std::distance(first,last);
        capacity_ = std::distance(first,last);
        vector_ = alloc_.allocate(capacity_);
        size_type i=0;
        for(InputIter it{first}; it != last;++it)
        {
            alloc_.construct(vector_+i,*it);
            ++i;
        }
    }

    // template<container-compatible-range<T> R>
    // void assign_range(R&& rg) {} // не делаю пока потому что с++20
    
    void assign(size_type n, const T& u) 
    {
        dealloc();
        size_ = n;
        capacity_ = n;
        vector_ = alloc_.allocate(capacity_);
        for(size_type i=0;i < size_;++i)
            alloc_.construct(vector_+i,u);
    }

    void assign(std::initializer_list<T> l)
    {
        dealloc();
        vector_ = alloc_.allocate(capacity_);
        size_type i = 0; 
        for(const value_type& elem : l)
        {
            alloc_.construct(vector_+i,elem);
            ++i;
        }
    }
    // allocator_type get_allocator() const noexept {}

    //iterators
    iterator begin() noexcept
    {   
        return vector_;
    }
    const_iterator begin() const noexcept
    {
        return vector_;
    }
    iterator end() noexcept
    {
        return vector_+size_;
    }
    const_iterator end() const noexcept
    {
        return vector_+size_;
    }   
    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }
    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(cend());
    }
    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(cbegin());
    }
    const_iterator cbegin() const noexcept
    {
        return vector_;
    }
    const_iterator cend() const noexcept
    {
        return vector_ + size_;
    }   

    //capacity
    bool empty() const noexcept
    {
        return !size_;
    }
    size_type size() const noexcept
    {
        return size_;
    }
    size_type capacity() const noexcept
    {
        return capacity_;
    }
    //size_type max_size() const noexcept; не знаю как вычислить максимальный размер
    private:
    void realloc_(size_type new_cap)
    {
        if(new_cap <= capacity_)
            return;
        pointer vector_realloc = alloc_.allocate(new_cap);
        std::uninitialized_copy(vector_,vector_+size_,vector_realloc);
        dealloc();
        vector_ = vector_realloc;
        capacity_ = new_cap;
    }
    public:
    void resize(size_type sz)
    {
        if(sz < size_)
        {
            for(size_type i=sz;i < size_;++i)
            {
                alloc_.destroy(vector_+i);
            }
            size_ = sz;
        }
        else if(sz > size_ && sz <=capacity_)
        {
            for(size_type i=size_;i < sz;++i)
            {
                alloc_.construct(vector_+i, value_type());
            }
            size_ = sz;
        }
        else if (sz > capacity_)
        {
            realloc_(sz);
            for(size_type i=size_;i < sz;++i)
            {
                alloc_.construct(vector_+i, value_type());
            }
            size_ = sz;
        }
    }
    void resize(size_type sz, const T& c)
    {
        if(sz < size_)
        {
            for(size_type i=sz;i < size_;++i)
            {
                alloc_.destroy(vector_+i);
                size_=i;
            }
        }
        else if(sz > size_ && sz <=capacity_)
        {
            for(size_type i=size_;i < sz;++i)
            {
                alloc_.construct(vector_+i, c);
            }
            size_ = sz;
        }
        else if (sz > capacity_)
        {
            realloc_(sz);
            for(size_type i=size_;i < sz;++i)
            {
                alloc_.construct(vector_+i, c);
            }
            size_ = sz;
        }
    }
    void reserve(size_type new_cap)
    {
        realloc_(new_cap);
    }
    void shrink_to_fit()
    {
        realloc_(size_);
    }

    //element access
    reference operator[](unsigned index)
    {
        return vector_[index];
    }
    const_reference operator[](unsigned index) const
    {
        return vector_[index];
    }
    reference at(size_type index)
    {
        assert(index < size_ && "index out of size");
        return vector_[index];

    }
    const_reference at(size_type index) const
    {
        assert(index < size_ && "index out of size");
        return vector_[index];
    }
    reference front()
    {
        assert( size_ != 0 && "vector is empty");
        return vector_[0];
    }
    const_reference front() const
    {
        assert( size_ != 0 && "vector is empty");
        return vector_[0];
    }
    reference back()
    {
        assert( size_ != 0 && "vector is empty");
        return vector_[size_-1];
    }
    const_reference back() const
    {
        assert( size_ != 0 && "vector is empty");
        return vector_[size_-1];
    }



    // data access
    // T* data() noexcept
    // {}
    // const T* data() const noexcept;

    // modifiers
    // template<class... Args>
    // reference emplace_back(Args&&... args);
    void push_back(const T& elem)
    {}
    // void push_back(T&& elem);
    // template<container-compatible-range<T> R> эту функцию не реализовую, так как пока не понимаю
    // void append_range(RGG rg) (она добавлена в с++20)
    void emplase(T* it,T elem)
    {}
    void clear()
    {}
};