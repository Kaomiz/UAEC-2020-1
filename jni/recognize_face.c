// this file will contain functions to be compiled into object binaries
// and exposed to the app via a JNI java interface (TODO)

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "fann_src/include/fann.h"
// #include </usr/lib64/openjdk-8/include/jni.h>

#include "recognize_face.h"

#define NET_SAVE "nn.shizzle"

JNIEXPORT unsigned long int JNICALL Java_recognize_1face_alloc_1nn(JNIEnv *env, jobject this_obj)
{
	// call once to create an instance of the neural network in memory
	struct fann *net;
	int addr_of_net;
	// this should load the weights and etc
	net = fann_create_from_file(NET_SAVE);
	addr_of_net = (unsigned long int)net;
	// store the address of the memory as an integer so java can deal with it
	return addr_of_net;
}

JNIEXPORT int JNICALL Java_recognize_1face_run_1data(JNIEnv *env, jobject this_obj, unsigned long int nn_ptr, char *img_data)
{
	int i;
	struct fann *net;
	fann_type input[256 * 256], *output;
	int guess;

	for(i = 0; i < 256 * 256; ++i)
		input[i] = img_data[i] / UCHAR_MAX;

	net = (struct fann *)nn_ptr;

	output = fann_run(net, input);

	guess = 0;

	for(i = 0; i < 4; ++i)
		if(output[i] > guess)
			guess = i;
	return guess;
}
