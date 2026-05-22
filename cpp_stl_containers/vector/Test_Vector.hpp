#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include "My_Vector.hpp"


void run_tests();
//construct/copy/move/destroy
void vector_n_test();
void vector_n_value_test();
void vector_iter_test();
void vector_copy_test();
void vector_move_test();
void initializer_list_test();
void destructor_test();
void operator_copy_test();
void operator_move_test();
void operator_init_list_test();


void size_test();
void capacity_test();
void reserve_test();
void push_back_test();
void at_test();
void at_outofrange_test();
void iterator_test();
void citerator_test();
void empty_test();
void not_empty_test();
void assign_test();
void riterator_test();
void criterator_test();
void resize_test();

void test();
