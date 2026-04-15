#include "Test_Vector.hpp"
void run_tests(){
    reserve_test();
    push_back_test();
    initializer_list_test();
    size_test();
    capacity_test();
    at_test();
    at_outofrange_test();
    iterator_test();
    citerator_test();
    empty_test();
    not_empty_test();
    assign_test();
    riterator_test();
    criterator_test();
    test();
}

void test(){
    std::vector<int> a{1,2,3,4};
};

void riterator_test(){
    My_vector<int> a{1,2,3};
    std::vector<int> b{1,2,3};
    int j = 2;
    for(auto i = a.rbegin(); i != a.rend();++i)
    {
        assert(*i == b[j] && "riterator test failed");
        --j;
    }

}
void criterator_test(){
    const My_vector<int> a{1,2,3};
    std::vector<int> b{1,2,3};
    int j = 2;
    for(auto i = a.crbegin(); i != a.crend();++i)
    {
        assert(*i == b[j] && "riterator test failed");
        --j;
    }

}

void initializer_list_test(){
    My_vector<int> a{1,2,3};
    std::vector<int> b{1,2,3};
    for(size_t i=0; i < b.size(); ++i)
    {
        assert(a[i] == b[i] && "initializer list test failed");
    }
}

void size_test(){
    My_vector<int> a{1,2,2};
    std::vector<int> b{1,2,3};
    for(size_t i=0; i < b.size(); ++i)
    {
        assert(a.size() == b.size() && "size test failed");
    }
}
void capacity_test(){
    My_vector<int> a;
    assert(a.capacity() == 1 && "capacity test failed");
}

void reserve_test(){
    My_vector<int> a;
    a.reserve(3);
    assert(a.capacity() == 3 && "reserve test failed");
}
void push_back_test(){
    My_vector<int> a;
    a.push_back(1);
    a.push_back(2);
    assert(a[0] == 1 && a[1] == 2 && "push back test failed");
}
void at_test(){
    My_vector<int> a;
    a.push_back(1);

    assert(a.at(0) == 1 && "at test failed");
}

void at_outofrange_test(){
    My_vector<int> a;
    a.push_back(1);
    try{
    std::cout << a.at(1);
    }
    catch(const std::out_of_range& e){
        assert(std::string(e.what()) == "index out of range" && "trow in at test failed");
    }
    
}

void iterator_test(){
    My_vector<int> a{1,2,3};
    std::vector<int> b{1,2,3};
    int j = 0;
    for(int& i : a)
    {
        assert(i == b[j] && "iterator test failed");
        ++j;
    }
}

void citerator_test(){
    const My_vector<int> a{1,2,3};
    std::vector<int> b{1,2,3};
    int j = 0;
    for(const int& i : a)
    {
        assert(i == b[j] && "citerator test failed");
        ++j;
    }
}

void empty_test(){
    const My_vector<int> a;
    assert(a.empty() == true && "empty test failed");
}

void not_empty_test(){
    const My_vector<int> a{1};
    assert(a.empty() == false && "not empty test failed");
}
void assign_test(){
    My_vector<int> a{1,2,3};
    a.assign({4,5,6});
    std::vector<int> b{1,2,3};
    b.assign({4,5,6});
    for(size_t i=0; i < b.size(); ++i)
    {
        assert(a[i] == b[i] && "initializer list test failed");
    }
}