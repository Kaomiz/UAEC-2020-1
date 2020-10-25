// libFANN training code

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "fann.h"

#define SAM_FACE "images.sam"
#define TAIT_FACE "images.sam"
#define ETHAN_FACE "images.sam"
#define MICHAEL_FACE "images.sam"

struct img_dat{
	uint16_t num_examples;
	uint16_t img_hres;
	uint16_t img_vres;
	int bytes_per_image;
	unsigned char **data;
	unsigned char *data_handle;
};

struct nn_params{
	int num_input;
	int num_output;
	int num_layers;
	int num_neurons_per_layer;
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
				img_dat[i].data[b][a] = fgetc(input_images[i]);
	}

	// data sdoulh be loaded now
	

	return 0;
}
