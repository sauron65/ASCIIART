#include <iostream>

int main() {
  int width {2000}, height {4000};
  int x {(int) (((float) width / (float) height) * 128.0f)};
  std::cout << (int) (((float) width / (float) height) * 128.0f) << std::endl;
}