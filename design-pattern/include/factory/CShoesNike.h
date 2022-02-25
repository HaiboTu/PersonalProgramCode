#ifndef __CSHOESNIKE_H
#define __CSHOESNIKE_H

#include <iostream>
#include "IShoes.h"

class CNike : public IShoes {
    public:
        void show() {
            std::cout << "Nike" << std::endl;
        }
};

#endif

