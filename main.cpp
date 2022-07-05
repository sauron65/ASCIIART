#include <iostream>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

static const char CHARS[] {
  ' ', '`', '.', '_', '-', '|', 'L', 'I', '+', '=', '*', 'G', 'S', '&', '#', '@', 'M', 'W'
};

char getChar(unsigned char pixel) {
  size_t p {0};
  for (size_t i {0}; i < sizeof(CHARS); i++) {
    if (pixel >= p && pixel <= (i + 1) * 16 - 1) {
      return CHARS[i];
    }
    p = (i + 1) * 16;
  }
  return ' ';
}

template <class T> T avg(std::initializer_list<T> list) {
  unsigned int len {0};
  unsigned int count {0};
  for (auto elem : list) {
    count += elem;
    len++;
  }
  if (len > 0) {
    return count / len;
  }
  return 0;
}

int main(int argc, char ** argv) {
  int width, height, nrChannels;
  unsigned char * img {nullptr};
  if (argc > 1) {
    img = stbi_load(argv[1], &width, &height, &nrChannels, 0);
  } else {
    img = stbi_load("./test.png", &width, &height, &nrChannels, 0);
  }
  std::cout << "width: " << width << " height: " << height << " channels: " << nrChannels << std::endl;
  if (width > 128) {
    unsigned char * newImg {new unsigned char[128 * (int) (((float) width / (float) height) * 128.0f) * nrChannels]};
    int code {stbir_resize_uint8(
      img, width, height, 0, newImg, 128,
      (int) (((float) width / (float) height) * 128.0f), 0, nrChannels)};
    if (code != 1) {
      std::cout << "resize error " <<  code << std::endl;
      return !code;
    }
    height = (int) (((float) width / (float) height) * 128.0f);
    width = 128;
    std::cout << "new width: " << width << " new height: " << height << std::endl;
    switch (nrChannels) {
      case 1:
        for (size_t i {0}; i < width * height; i++) {
          if (i % (width) == 0) {
            std::cout << std::endl;
          }
          std::cout << getChar(newImg[i]);
        }
        break;
      case 3:
        for (size_t i {0}; i < width * height * 3; i += 3) {
          if (i % (width * 3) == 0) {
            std::cout << std::endl;
          }
          std::cout << getChar(avg({newImg[i], newImg[i + 1], newImg[i + 2]}));
        }
        break;
      case 4:
        for (size_t i {0}; i < width * height * 4; i += 4) {
          if (i % (width * 4) == 0) {
            std::cout << std::endl;
          }
          std::cout << getChar(avg({newImg[i], img[i + 1], img[i + 2]}));
        }
        break;
    }
    std::cout << std::endl;
    return 0;
  }
  switch (nrChannels) {
    case 1:
      for (size_t i {0}; i < width * height; i++) {
        if (i % (width) == 0) {
          std::cout << std::endl;
        }
        std::cout << getChar(img[i]);
      }
      break;
    case 3:
      for (size_t i {0}; i < width * height * 3; i += 3) {
        if (i % (width * 3) == 0) {
          std::cout << std::endl;
        }
        std::cout << getChar(avg({img[i], img[i + 1], img[i + 2]}));
      }
      break;
    case 4:
      for (size_t i {0}; i < width * height * 4; i += 4) {
        if (i % (width * 4) == 0) {
          std::cout << std::endl;
        }
        std::cout << getChar(avg({img[i], img[i + 1], img[i + 2]}));
      }
      break;
  }
  std::cout << std::endl;
}