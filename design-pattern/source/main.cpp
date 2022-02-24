#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include "CSingleton.h"
#include <iostream>

int main(int argc ,char *argv[]){
    class CSingleton& p = CSingleton::getInstance();

    std::cout << "main" << std::endl;

	return 0;
}

