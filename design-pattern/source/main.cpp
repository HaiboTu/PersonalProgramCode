#include <iostream>
#include "CShoesFactory.h"
#include "IShoes.h"

int main(int argc ,char *argv[]){
    CShoesFactory shoesFactory;
    IShoes *shoes;

    shoes = shoesFactory.CreateShoes(LINING);
    shoes->show();

    shoes = shoesFactory.CreateShoes(NIKE);
    shoes->show();

	return 0;
}

