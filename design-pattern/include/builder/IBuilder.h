#ifndef __IBUILDER_H
#define __IBUILDER_H

#include <iostream>
#include "CProduct.h"

class IBuilder {
public:
    virtual ~IBuilder() {};

    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;

    virtual CProduct* getProduct() = 0;
};

#endif

