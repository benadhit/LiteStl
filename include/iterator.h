#ifndef LITESTL_ITERATOR_H_
#define LITESTL_ITERATOR_H_

// 这个头文件用于迭代器设计，包含了一些模板结构体与全局函数，
#include<cstddef>

#include"type_traits.h"

namespace LiteStl{

// 五种迭代器类型
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};


//iterator 模板
template<typename Category,typename T,typename Distance = ptrdiff_t,
        typename Pointer = T*,typename Reference = T&>
struct iterator
{
    using iterator_category = Category;
    using value_type        = T;
    using reference         = Reference;
    using diference_type    = Distance;
};


//iterator traits
template<typename T>
struct has_iterator_cat
{
private:
    struct two
    {
        char a;
        char b;
    };

    template<typename U>
    static two test(...);
    template<typename U>
    static char test(typename U::iterator_category* =0);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(char);
};


template<typename Iterator,bool>
struct iterator_traits_impl
{
};

template<typename Iterator>
struct iterator_traits_impl<Iterator,true>
{
    using iterator_category     = typename Iterator::iterator_category;
    using value_type            = typename Iterator::value_type;
    using pointer               = typename Iterator::pointer;
    using reference             = typename Iterator::reference;
    using differnce_type        = typename Iterator::difference_type;
};

template<typename Iterator,bool>
struct iterator_traits_helper{}

template<typename Iterator>
struct iterator_traits_helper<Iterator,true>
:public iterator_traits_impl<Iterator,
    std::is_covertiable<typename Iterator::iterator_category,input_iterator_tag>::value||
    std::is_covertiable<typename Iterator::iterator_category,output_iterator_tag>::value>
    {}


//萃取迭代器的特性
template<typename Iterator>
struct iterator_traits
:public iterator_traits_helper<Iterator,has_iterator_cat<Iterator>::value>
{

}

// 针对原生指针的偏特化版本
template <typename T>
struct iterator_traits<T*>
{
using iterator_category     = random_access_iterator_tag ;
using value_type            = T  ;
using  pointer              = T*;  
using reference             = T&;
using  difference_type      = ptrdiff_t;
};

    



}


#endif