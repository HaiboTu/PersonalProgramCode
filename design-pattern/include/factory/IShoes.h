
#ifndef __ISHOES_H
#define __ISHOES_H

#include <iostream>

class IShoes {
    public:
        virtual ~IShoes() {};
        virtual void show() = 0;
};

#endif
