//
// Created by Administrator on 2023/3/21.
//

#ifndef DEMO_TRIANGLE_IMAGEUTIL_H
#define DEMO_TRIANGLE_IMAGEUTIL_H


class ImageUtil {
public:
    static unsigned char* _stb_image_load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
    static void _stb_image_free(unsigned char *filename);
    static void _stbi_set_flip_vertically_on_load(bool isFlip);
};


#endif //DEMO_TRIANGLE_IMAGEUTIL_H
