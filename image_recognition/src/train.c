// libFANN training code

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include "fann.h"

#define SAM_FACE "images.sam"
#define TAIT_FACE "images.sam"
#define ETHAN_FACE "images.sam"
#define MICHAEL_FACE "images.sam"

#define NET_SAVE "nn.shizzle"

struct img_dat{
	uint16_t num_examples;
	uint16_t img_hres;
	uint16_t img_vres;
	int bytes_per_image;
	float **data;
	float *data_handle;
};

struct nn_params{
	int num_in;
	int num_out;
	int num_hidden;
	int num_lay;
	int num_neu_p_lay;
	float desired_error;
	int max_epochs;
	int epochs_between_reports;
};

int main()
{
	int i, a, b;
	// proprocessing should result in four char arrays of various faces, load
	// shitty custom format, load into training data arrays
	FILE *input_images[4];
	struct img_dat img_dat[4];
	struct nn_params nnp;
	struct fann *net;
	float want_out[4];
	int select;
	int increment[4];
	FILE *net_save;

	input_images[0] = fopen(SAM_FACE, "r");
	input_images[1] = fopen(TAIT_FACE, "r");
	input_images[2] = fopen(ETHAN_FACE, "r");
	input_images[3] = fopen(MICHAEL_FACE, "r");

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

	// build network, this is the cool shit
	nnp.num_in = img_dat[0].bytes_per_image;
	nnp.num_out = 4;
	nnp.num_hidden = 32;
	nnp.num_lay = 3;
	nnp.num_neu_p_lay = 16;
	nnp.max_epochs = 20000;
	nnp.epochs_between_reports = 100;

	// construct network
	net = fann_create_standard(nnp.num_lay, nnp.num_in, nnp.num_hidden, nnp.num_out);

	fann_set_activation_function_hidden(net, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(net, FANN_SIGMOID_SYMMETRIC);

	// attempt to load the saved network
	net_save = fopen(NET_SAVE, "r");
	if(!net_save){
		// initialize a new network

	}else{
		// load the saved network
		net = fann_create_	
	}

	// initialize training trackers
	// this will keep track of which image to train on from a given dataset
	for(i = 0; i < 4; ++i)
		increment[i] = 0;

	// TRAINNNNN
	for(i = 0; i < nnp.max_epochs; ++i){
		srand(time(NULL));
		select = rand() % 4;
		fann_train(net, img_dat[select].data[increment[select]], want_out);
		++increment[select];
		if(increment[select] == img_dat[select].num_examples)
			increment[select] = 0;
	}

	// save the network

	return 0;
}
