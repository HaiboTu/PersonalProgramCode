#ifndef __CSHOESLINING_H
#define __CSHOESLINING_H

#include <iostream>
#include "IShoes.h"

class CLining : public IShoes {
    public:
        void show() {
            std::cout << "Lining" << std::endl;
        }
};

#endif
