#include "Test_Vector.hpp"
void run_tests(){
    //тесты функций используемыех в других тестах
    initializer_list_test();


    //тесты независимые от порядка
    //construct/copy/move/destroy
    vector_n_test();
    vector_n_value_test();
    vector_iter_test(); 
    vector_copy_test();
    vector_move_test();
    destructor_test();
    operator_copy_test();
    operator_move_test();
    operator_init_list_test();

    // reserve_test();
    // push_back_test();
    
    // size_test();
    // capacity_test();
    // at_test();
    // at_outofrange_test();
    // iterator_test();
    // citerator_test();
    // empty_test();
    // not_empty_test();
    // assign_test();
    // riterator_test();
    // criterator_test();
    // resize_test();

    test();
}

void test(){
    // std::vector<int> a{1,2,3};
    // std::vector<int> b{1};
    // a = b;
    // a[0] = 2;
    // std::cout << b[0];
};
//construct/copy/move/destroy

void vector_n_test()
{
    My_Vector<int> a(3);
    std::vector<int> b(3);
    assert(a.size() == 3 && "vector_n_test test failed");
    assert(a.capacity() == 3 && "vector_n_test test failed");
    for(size_t i=0; i < b.size(); ++i)
    {
        assert(a[i] == b[i] && "vector_n_test test failed");
    }
}
void vector_n_value_test() 
{
    My_Vector<int> a(3,5);
    std::vector<int> b(3,5);
    assert(a.size() == 3 && "vector_n_value_test test failed");
    assert(a.capacity() == 3 && "vector_n_value_test test failed");
    for(size_t i=0; i < b.size(); ++i)
    {
        assert(a[i] == b[i] && "vector_n_value_test test failed");
    }
}
void vector_iter_test()
{
    std::vector<int> b{1,2,3};
    My_Vector<int> a(b.begin(),b.end());
    assert(a.size() == 3 && "vector_iter_test test failed");
    assert(a.capacity() == 3 && "vector_iter_test test failed");
    for(size_t i=0; i < b.size(); ++i)
    {
        assert(a[i] == b[i] && "vector_iter_test test failed");
    }
}
void vector_copy_test()
{
    My_Vector<int> b{1,2,3};
    My_Vector<int> a(b);
    assert(a.size() == 3 && "vector_copy_test test failed");
    assert(a.capacity() == 3 && "vector_copy_test test failed");
    for(size_t i=0; i < b.size(); ++i)
    {
        assert(a[i] == b[i] && "vector_copy_test test failed");
    }
}
void vector_move_test()
{
    My_Vector<int> b{1,2,3};
    My_Vector<int> a(std::move(b));
    assert(a.size() == 3 && "vector_move_test test failed");
    assert(a.capacity() == 3 && "vector_move_test test failed");
    for(size_t i=0; i < b.size(); ++i)
    {
        assert(a[i] == b[i] && "vector_move_test test failed");
    }
}

void initializer_list_test()
{
    My_Vector<int> a{1,2,3};
    std::vector<int> b{1,2,3};
    assert(a.size() == 3 && "initializer list test failed");
    assert(a.capacity() == 3 && "initializer list test failed");
    for(size_t i=0; i < b.size(); ++i)
    {
        assert(a[i] == b[i] && "initializer list test failed");
    }
}

void destructor_test()
{
    {
    My_Vector<int> a{1,2,3};
    }
}

void operator_copy_test()
{
    
    My_Vector<int> b{1,2,3};
    My_Vector<int> a{1};
    a = b;
    assert(a.size() == 3 && "operator_copy_test test failed");
    assert(a.capacity() == 3 && "operator_copy_test test failed");
    for(size_t i=0; i < b.size(); ++i)
    {
        assert(a[i] == b[i] && "operator_copy_test test failed");
    }
}

void operator_move_test()
{
    My_Vector<int> b{1,2,3};
    My_Vector<int> a{1};
    a = std::move(b);
    assert(a.size() == 3 && "operator_move_test test failed");
    assert(a.capacity() == 3 && "operator_move_test test failed");
    assert(b.size() == 0 && "operator_move_test test failed");
    assert(b.capacity() == 3 && "operator_move_test test failed");
    assert(a[0] == 1 && "operator_move_test test failed");
    assert(a[1] == 2 && "operator_move_test test failed");
    assert(a[2] == 3 && "operator_move_test test failed");
}

void operator_init_list_test()
{
    My_Vector<int> a{1};
    a = {1,2,3};
    assert(a.size() == 3 && "operator_init_list_test test failed");
    assert(a.capacity() == 3 && "operator_init_list_test test failed");
    assert(a[0] == 1 && "operator_init_list_test test failed");
    assert(a[1] == 2 && "operator_init_list_test test failed");
    assert(a[2] == 3 && "operator_init_list_test test failed");

}


// void riterator_test(){
//     My_Vector<int> a{1,2,3};
//     std::vector<int> b{1,2,3};
//     int j = 2;
//     for(auto i = a.rbegin(); i != a.rend();++i)
//     {
//         assert(*i == b[j] && "riterator test failed");
//         --j;
//     }

// }
// void criterator_test(){
//     const My_Vector<int> a{1,2,3};
//     std::vector<int> b{1,2,3};
//     int j = 2;
//     for(auto i = a.crbegin(); i != a.crend();++i)
//     {
//         assert(*i == b[j] && "riterator test failed");
//         --j;
//     }
// }



// void size_test(){
//     My_Vector<int> a{1,2,2};
//     std::vector<int> b{1,2,3};
//     for(size_t i=0; i < b.size(); ++i)
//     {
//         assert(a.size() == b.size() && "size test failed");
//     }
// }
// void capacity_test(){
//     My_Vector<int> a;
//     assert(a.capacity() == 1 && "capacity test failed");
// }

// void reserve_test(){
//     My_Vector<int> a;
//     a.reserve(3);
//     assert(a.capacity() == 3 && "reserve test failed");
// }
// void push_back_test(){
//     My_Vector<int> a;
//     a.push_back(1);
//     a.push_back(2);
//     assert(a[0] == 1 && a[1] == 2 && "push back test failed");
// }
// void at_test(){
//     My_Vector<int> a;
//     a.push_back(1);

//     assert(a.at(0) == 1 && "at test failed");
// }

// void at_outofrange_test(){
//     My_Vector<int> a;
//     a.push_back(1);
//     try{
//     std::cout << a.at(1);
//     }
//     catch(const std::out_of_range& e){
//         assert(std::string(e.what()) == "index out of range" && "trow in at test failed");
//     }
    
// }

void iterator_test(){
    My_Vector<int> a{1,2,3};
    std::vector<int> b{1,2,3};
    int j = 0;
    for(int& i : a)
    {
        assert(i == b[j] && "iterator test failed");
        ++j;
    }
}

void citerator_test(){
    const My_Vector<int> a{1,2,3};
    std::vector<int> b{1,2,3};
    int j = 0;
    for(const int& i : a)
    {
        assert(i == b[j] && "citerator test failed");
        ++j;
    }
}

void empty_test(){
    const My_Vector<int> a;
    assert(a.empty() == true && "empty test failed");
}

void not_empty_test(){
    const My_Vector<int> a{1};
    assert(a.empty() == false && "not empty test failed");
}
// void assign_test(){
//     My_Vector<int> a{1,2,3};
//     a.assign({4,5,6});
//     std::vector<int> b{1,2,3};
//     b.assign({4,5,6});
//     for(size_t i=0; i < b.size(); ++i)
//     {
//         assert(a[i] == b[i] && "initializer list test failed");
//     }
// }

// void resize_test()
// {
//     My_Vector<int> a{1,2};
//     a.resize(4);
//     for(auto i : a)
//     {
//         std::cout << i << ' ';
//     }
// }

