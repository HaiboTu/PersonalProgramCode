#include <iostream>

class IBuilder {
public:
    virtual ~IBuilder() = 0;

    void buildPartA();
    void buildPartB();

    CProduct getProduct();
}
