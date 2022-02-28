#include <iostream>
#include "builder/IBuilder.h"
#include "builder/CDirector.h"
#include "builder/CProduct.h"
#include "builder/CBuilderA.h"
#include "builder/CBuilderB.h"

int main(int argc ,char *argv[]){
    IBuilder *pBuilder = new CBuilderA();
    CDirector *pDirector = new CDirector(pBuilder);
    CProduct *pProduct;

    pDirector->construct();

    pProduct = pBuilder->getProduct();

    pBuilder = new CBuilderB();
    pDirector = new CDirector(pBuilder);

    pDirector->construct();

    pProduct = pBuilder->getProduct();
	return 0;
}

