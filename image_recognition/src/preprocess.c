#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

// imagemagick magickcore
#include <ImageMagick-7/MagickCore/MagickCore.h>

struct dir_info
{
	int num_files;
	char **file_names;
};

struct out_props
{
	int h_res;
	int v_res;
};

int index_dir(const char *file_dir, struct dir_info *dir_info)
{
	// stores same directory info in dir_info
	// returns -1 on failure
	DIR *raw_img_dir;
	struct dirent *dirent;
	char **tmp_p;
	int num_files = 0;
	int i = 0;
	
	if(!(raw_img_dir = opendir(file_dir))){
		perror("cannot read raw image directory");
		return -1;
	}

	while((dirent = readdir(raw_img_dir))){
		if(dirent->d_type == DT_REG){
			++num_files;

			tmp_p = malloc(sizeof(char *) * num_files);
			if(!tmp_p){
				fprintf(stderr, "fatal: malloc() failed, exiting\n");
				return -1;
			}
			memcpy(tmp_p, dir_info->file_names, sizeof(char *) * (num_files - 1));
			if(num_files > 1)
				free(dir_info->file_names);
			dir_info->file_names = tmp_p;

			i = 0;
			while(dirent->d_name[i++] != '\0')
				;
			dir_info->file_names[num_files - 1] = malloc(sizeof(char) * i);
			strncpy(dir_info->file_names[num_files - 1], dirent->d_name, i);
		}
	}

	closedir(raw_img_dir);

	dir_info->num_files = num_files;

	return 0;
}

Image *convert_img(ImageInfo *img_info, ExceptionInfo *exception, struct out_props *out_props)
{
	Image *img_in, *img_out;

	if(IsMagickCoreInstantiated() == MagickFalse){
		fprintf(stderr, "the magickcore environment must be ititalized"
				"before calling convert_img()\n");
		return NULL;
	}

	img_in = ReadImage(img_info, exception);

	if(exception->severity != UndefinedException)
		CatchException(exception);
	if(img_in == (Image *) NULL){
		fprintf(stderr, "failed to read image %s, exiting\n",
				img_info->filename);
		return NULL;
	}

	// resize
	img_out = SampleImage(img_in, out_props->h_res, out_props->v_res, exception);
	DestroyImage(img_in);

	// convert to greyscale
	TransformImageColorspace(img_out, GRAYColorspace, exception);

	return img_out;
}

int main(int argc, const char **argv)
{
	int i, a;

	int write_pos;
	int n_write_success;

	struct out_props out_props;
	struct dir_info dir_info;

	Image *img;
	ImageInfo *image_info;
	ExceptionInfo *exception;
	char *img_pixels;

	FILE *output_data;

	if(argc != 5){
		printf("%s <input_image_dir> <output_file> <out_h_res> <out_v_res>\n", argv[0]);
		return EXIT_FAILURE;
	}
	if((output_data = fopen(argv[2], "w+b")) == NULL){
		perror("cannot write output data");
		return EXIT_FAILURE;
	}

	sscanf(argv[3], "%d", &out_props.h_res);
	sscanf(argv[4], "%d", &out_props.v_res);

	// index images
	if(index_dir(argv[1], &dir_info)){
		fprintf(stderr, "image dir indexing failed, exiting\n");
		return EXIT_FAILURE;
	}

	n_write_success = dir_info.num_files;

	// allocate memory to hold image pixels
	img_pixels = NULL;
	img_pixels = malloc(sizeof(char) * out_props.h_res * out_props.v_res);
	if(!img_pixels){
		fprintf(stderr, "failed to allocate memory for image data, exiting\n");
		return EXIT_FAILURE;
	}

	// write outputfile header data
	// *could* implement an actual file format, like idx or something
	for(i = 0; i < 2; ++i)
		fputc((unsigned char)(dir_info.num_files >> 8 * i), output_data);
	for(i = 0; i < 2; ++i)
		fputc((unsigned char)(out_props.h_res >> 8 * i), output_data);
	for(i = 0; i < 2; ++i)
		fputc((unsigned char)(out_props.v_res >> 8 * i), output_data);

	// initialize the magickcore environment
	MagickCoreGenesis(NULL, MagickTrue);
	exception = AcquireExceptionInfo();
	image_info = CloneImageInfo((ImageInfo *) NULL);

	// this shouldn't fail as this dir was opened and read earlier
	// thus not bothering with an error message
	if(chdir(argv[1]))
		return EXIT_FAILURE;

	for(i = 0; i < dir_info.num_files; ++i){
		strcpy(image_info->filename, dir_info.file_names[i]);
		// read and convert image to generalized format
		img = convert_img(image_info, exception, &out_props);
		if(!img){
			printf("an error occured, proceeding to next image");
			goto process_loop_fail;
		}
		// extract and store new pixel values
		if(ExportImagePixels(img, 0, 0, out_props.h_res, out_props.v_res,
				"I", CharPixel, img_pixels, exception) == MagickFalse){
			printf("pixel export failed, moving onto next image without writing\n");
			goto process_loop_fail;
		}
		// write pixels to datafile
		for(a = 0; a < out_props.h_res * out_props.v_res; ++a)
			fputc(img_pixels[a], output_data);
		goto process_loop_cleanup;
process_loop_fail:
		// decrement num of images written
		--n_write_success;
		// apply new img_count header
		write_pos = ftell(output_data);
		fseek(output_data, 0, SEEK_SET);
		for(i = 0; i < 2; ++i)
			fputc((unsigned char)(n_write_success >> 8 * i), output_data);
		// return filepointer
		fseek(output_data, write_pos, SEEK_SET);
process_loop_cleanup:
		DestroyImage(img);
	}

	if(chdir(".."))
		return EXIT_FAILURE;

	// image conversion and extraction done, dismantle magickcore env
	DestroyImageInfo(image_info);
	DestroyExceptionInfo(exception);
	MagickCoreTerminus();

	// cleanup
	fclose(output_data);
	for(i = 0; i < dir_info.num_files; ++i)
		free(dir_info.file_names[i]);
	free(img_pixels);

	return EXIT_SUCCESS;
}
