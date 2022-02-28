#include <iostream>
#include "singleton/CSingleton.h"

CSingleton CSingleton::m_Instance;

CSingleton::CSingleton() : m_flags(true) {
    std::cout << "CSingleton()" << std::endl;
}

CSingleton::~CSingleton() {
    std::cout << "~CSingleton()" << std::endl;
}

CSingleton& CSingleton::getInstance() {
    std::cout << "getInstance()" << std::endl;
    return m_Instance;
}

