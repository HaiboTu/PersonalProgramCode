#ifndef __CBUILDERA_H
#define __CBUILDERA_H

#include <iostream>
#include "IBuilder.h"

class CBuilderA : public IBuilder {
public:
    CBuilderA() {
        m_product = new CProduct();
    }

    void buildPartA() {
        std::cout << "CBuilderA partA" << std::endl;
    }
    void buildPartB() {
        std::cout << "CBuilderA partB" << std::endl;
    }

    CProduct* getProduct() {
        std::cout << "CBuilderA getProduct" << std::endl;

        return m_product;
    }

private:
    CProduct *m_product;
};

#endif

