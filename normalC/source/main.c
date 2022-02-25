#define _GNU_SOURCE
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<sched.h>
#include<signal.h>
#include<unistd.h>
#include "cet.h"

#define STACK_SIZE (1024 * 1024)

struct cmd_element {
    const char *name;
};

struct cmd_element cmd_elements[] = {
    {.name = "hell"},
};

static char child_stack[STACK_SIZE];
char *const child_args[] = {
	"/bin/bash",
	NULL
};

int child_main(void *args) {
	printf("child process!\n");
	sethostname("NewNamespace", 12);
	execv(child_args[0], child_args);
	return 1;
}

int main(int argc ,char *argv[]){
    printf("%s", cmd_elements[0].name);
	printf("process start: \n");
	int child_pid = clone(child_main, child_stack + STACK_SIZE, CLONE_NEWUTS | SIGCHLD, NULL);
	waitpid(child_pid, NULL, 0);
	printf("exit\n");
	return 0;
}

