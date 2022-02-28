#include <iostream>
#include "builder/IBuilder.h"
#include "builder/CDirector.h"
#include "builder/CProduct.h"
#include "builder/CBuilderA.h"
#include "builder/CBuilderB.h"
#include "prototype/CPrototype.h"

int main(int argc ,char *argv[]){
    CPrototypeA *pA = new CPrototypeA("CProductA");
    CPrototypeB *pB = (CPrototypeB *)pA->Clone();

    pA->show();

    delete pA;

    pB->show();

	return 0;
}

