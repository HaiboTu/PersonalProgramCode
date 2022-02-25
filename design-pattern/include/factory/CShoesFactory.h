#ifndef __CSHOESFACTORY_H
#define __CSHOESFACTORY_H

#include "IShoes.h"
#include "CShoesLining.h"
#include "CShoesNike.h"

enum SHOES_TYPE {
    LINING,
    NIKE,
};

class CShoesFactory {
    public:
        IShoes *CreateShoes(SHOES_TYPE showType) {
            switch (showType)
            {
                case LINING:
                    return new CLining();
                case NIKE:
                    return new CNike();
                default:
                    return NULL;
            }
        }
};

#endif

