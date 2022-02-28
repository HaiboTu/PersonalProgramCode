#ifndef __CBUILDERB_H
#define __CBUILDERB_H

#include <iostream>
#include "IBuilder.h"
#include "CProduct.h"

class CBuilderB : public IBuilder {
public:
    CBuilderB() {
        m_product = new CProduct();
    }
    void buildPartA() {
        std::cout << "CBuilderB partA" << std::endl;
    }
    void buildPartB() {
        std::cout << "CBuilderB partB" << std::endl;
    }

    CProduct* getProduct() {
        std::cout << "CBuilderB getProduct" << std::endl;

        return m_product;
    }

private:
    CProduct *m_product;
};

#endif

