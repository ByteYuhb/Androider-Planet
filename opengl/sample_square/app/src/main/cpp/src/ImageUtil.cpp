//
// Created by Administrator on 2023/3/21.
//


#include "../include/ImageUtil.h"
#define STB_IMAGE_IMPLEMENTATION

#include "../include/stb/stb_image.h"


unsigned char* ImageUtil::_stb_image_load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels){
    return stbi_load(filename,x,y,channels_in_file,desired_channels);
}
void ImageUtil::_stb_image_free(unsigned char *filename){
    stbi_image_free(filename);
}
void ImageUtil::_stbi_set_flip_vertically_on_load(bool isFlip) {
    stbi_set_flip_vertically_on_load(isFlip);
}
