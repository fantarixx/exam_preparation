#include <iostream>

#include "../intornot.h"
#include "../vector/template_vector.h"

#include "tasks.h"

void IntOrNotTest() {
    IntOrNot::IntOrNot v;

    print(v); // no value

    v = 10;
    print(v); // 10
}
/*void IntVectorTest() {
    Vector vec1;
    Vector vec2 = (2);
    Vector vec5 = vec1;

    std::cout << vec2 << std::endl;      // 2


    vec1.push_back(1);

    std::cout << vec1 << std::endl;     // 1

    vec2.push_back(3);
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);
    vec2.push_back(7);

    std::cout << vec2 << std::endl;      // 2 1 3 4 5 6 7

    vec2.pop_back();

    std::cout << vec2 << std::endl;     // 2 1 3 4 5 6

    std::cout << vec2.size << ' ' << vec2.capacity << std::endl;        // 6 ..
    
    const Vector vec3(vec2);
    
    std::cout << vec3 << std::endl;     // 2 1 3 4 5 6
    
    vec4 = vec1 + vec2;
    std::cout << vec4 << std::endl;     // 1 2 1 3 4 5 6
}*/
/*
void TemplateVectorTest() {
    Template_Vector<int> vec1;
    Template_Vector<int> vec2 = {2};
    Template_Vector<int> vec5 = vec1;

    std::cout << vec2 << std::endl;      // 2


    vec1.push_back(1);

    std::cout << vec1 << std::endl;     // 1

    vec2.push_back(3);
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);
    vec2.push_back(7);

    std::cout << vec2 << std::endl;      // 2 1 3 4 5 6 7

    vec2.pop_back();

    std::cout << vec2 << std::endl;     // 2 1 3 4 5 6

    std::cout << vec2.size << ' ' << vec2.capacity << std::endl;        // 6 ..
    
    const Template_Vector vec3(vec2);
    
    std::cout << vec3 << std::endl;     // 2 1 3 4 5 6
    
    vec4 = vec1 + vec2;
    std::cout << vec4 << std::endl;     // 1 2 1 3 4 5 6
}*/