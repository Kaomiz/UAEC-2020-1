#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <fann.h>

#define NET_SAVE "nn.shizzle"

int main(){
	struct fann *net;
	static const char *processed_img_files[] = {
		"sam.img",
		"tait.img",
		"ethan.img",
		"michael.img"
	};
	int select;
	int i;

	net = fann_create_from_file(NET_SAVE);

	srand(time(NULL));
	select = rand() % 4;
	FILE *test_data = fopen(processed_img_files[select], "r");

	printf("loading a picture of: %d\n", select);

	// trash header data
	for(i = 0; i < 6; ++i)
		fgetc(test_data);

	float data[256*256];

	select = rand() % 50;
	// jump to the start of a random pic
	fseek(test_data, 256 * 256 * select, SEEK_CUR);
	for(i = 0; i < 256 * 256; ++i)
		data[i] = fgetc(test_data);
	
	float *output = fann_run(net, data);

	for(i = 0; i < 4; ++i)
		printf("%f\n", output[i]);

	return -1;
}
