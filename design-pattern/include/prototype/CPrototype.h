#ifndef __CPROTYPE_H
#define __CPROTYPE_H

#include <iostream>
#include <string>

class IPrototype {
public:
    virtual IPrototype* Clone() = 0;
};

class CPrototypeA : public IPrototype {
public:
    CPrototypeA(std::string name) {
        m_name = name;
    }

    IPrototype* Clone() {
        return new CPrototypeA(m_name);
    }

    void show() {
        std::cout << m_name << std::endl;
    }
private:
    std::string m_name;
};

class CPrototypeB : public IPrototype {
public:
    CPrototypeB(std::string name) {
        m_name = name;
    }

    IPrototype* Clone() {
        return new CPrototypeB(m_name);
    }

    void show() {
        std::cout << m_name << std::endl;
    }
private:
    std::string m_name;
};
#endif
