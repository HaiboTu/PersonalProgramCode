#ifndef __CDIRECTOR_H
#define __CDIRECTOR_H

#include <iostream>

class CDirector {
public:
    CDirector(IBuilder *builder) {
        m_builder = builder;
    }

    void construct() {
        m_builder->buildPartA();
        m_builder->buildPartB();
    }

private:
    IBuilder *m_builder;
};

#endif
