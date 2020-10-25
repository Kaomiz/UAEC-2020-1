// this file will contain functions to be compiled into object binaries
// and exposed to the app via a JNI java interface (TODO)

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "fann.h"

#define NET_SAVE "nn.shizzle"

unsigned long int setup_env(){
	// load execution
	struct fann *net;
	int addr_of_net;
	net = fann_create_from_save(NET_SAVE);
	addr_of_net = net;
	return addr_of_net;
}

int recognize_face(void *env, char *img_data)
{
	
}
