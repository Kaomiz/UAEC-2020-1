// libFANN training code

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include "fann.h"

#define NET_SAVE "nn.shizzle"

struct img_dat{
	uint16_t num_examples;
	uint16_t img_hres;
	uint16_t img_vres;
	int bytes_per_image;
	float **data;
	float *data_handle;
};

int main(int argc, char **argv)
{
	int i, a, b;
	// proprocessing should result in four char arrays of various faces, load
	// shitty custom format, load into training data arrays
	FILE *input_images[4];
	struct img_dat img_dat[4];
	struct fann *net;
	float want_out[4];
	int select;
	int increment[4];
	FILE *net_save;
	int training_epochs;

	static const char *processed_img_files[] = {
		"sam.img",
		"tait.img",
		"ethan.img",
		"michael.img"
	};

	// check to make sure the user passed us a number of training epochs to run
	if(argc != 2){
		printf("%s <training_epochs>\n", argv[0]);
	}
	training_epochs = atoi(argv[1]);
	printf("running %d training epochs\n", training_epochs);

	for(i = 0; i < 4; ++i)
		input_images[i] = fopen(processed_img_files[i], "r");

	for(i = 0; i < 4; ++i){
		if(!input_images[i]){
			printf("failed to read file: %s\n",
					processed_img_files[i]);
			return -1;
		}
	}
	// initialize
	for(i = 0; i < 4; ++i){
		img_dat[i].num_examples = 0;
		img_dat[i].img_hres = 0;
		img_dat[i].img_vres = 0;
	}

	for(i = 0; i < 4; ++i){
		// proprocess stores the header info as two byte ints
		for(a = 0; a < 2; ++a)
			img_dat[i].num_examples |= fgetc(input_images[i]) << 8 * a;
		for(a = 0; a < 2; ++a)
			img_dat[i].img_hres |= fgetc(input_images[i]) << 8 * a;
		for(a = 0; a < 2; ++a)
			img_dat[i].img_vres |= fgetc(input_images[i]) << 8 * a;
		img_dat[i].bytes_per_image = img_dat[i].img_hres *
			img_dat[i].img_vres;
		if(i > 0)
			assert(img_dat[i].bytes_per_image ==
					img_dat[i - 1].bytes_per_image);
	}

	// allocate memory
	for(i = 0; i < 4; ++i){
		img_dat[i].data_handle = malloc(sizeof(*img_dat[i].data_handle) *
				img_dat[i].num_examples *
				img_dat[i].bytes_per_image);
		img_dat[i].data = malloc(sizeof(*img_dat[i].data) *
				img_dat[i].num_examples);
		for(a = 0; a < img_dat[i].num_examples; ++a)
			img_dat[i].data[a] = &img_dat[i].data_handle[a *
				img_dat[i].bytes_per_image];

	}
	
	// all images should have the same number of bytes per image
	for(i = 0; i < 4; ++i){
		for(b = 0; b < img_dat[i].num_examples; ++b)
			for(a = 0; a < img_dat[i].bytes_per_image; ++a)
				img_dat[i].data[b][a] = fgetc(input_images[i]) / UCHAR_MAX;
	}

	// attempt to load the saved network
	net_save = fopen(NET_SAVE, "r");
	if(!net_save){
		fclose(net_save);
		// initialize a new network
		// construct network
		// number of layers,
		// 	nodes_in, nodes_hidden, nodes_out [VA nodes in each layer]
		net = fann_create_standard(3, 
				img_dat[0].bytes_per_image, 32, 4);
		fann_set_activation_function_hidden(net, FANN_SIGMOID_SYMMETRIC);
		fann_set_activation_function_output(net, FANN_SIGMOID_SYMMETRIC);
		fann_randomize_weights(net, 0.5, -0.5);
	}else{
		// fann takes a char * not a file *, so close filestream here
		fclose(net_save);
		// load the saved network
		net = fann_create_from_file(NET_SAVE);
	}

	// initialize training trackers
	// this will keep track of which image to train on from a given dataset
	for(i = 0; i < 4; ++i)
		increment[i] = 0;

	// TRAINNNNN
	for(i = 0; i < training_epochs; ++i){
		// which dataset are we gonna pull from
		srand(time(NULL));
		select = rand() % 4;

		// prepare the wanted output activations
		for(a = 0; a < 4; ++a)
			want_out[a] = 0;
		want_out[select] = 1;

		// train
		fann_train(net, img_dat[select].data[increment[select]], want_out);

		// increment dataset series selection pointer
		++increment[select];
		if(increment[select] == img_dat[select].num_examples)
			increment[select] = 0;
	}

	// save the network
	fann_save(net, NET_SAVE);

	// cleanup
	for(i = 0; i < 4; ++i){
		free(img_dat[i].data_handle);
		free(img_dat[i].data);
	}

	return 0;
}
