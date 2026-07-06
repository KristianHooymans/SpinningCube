#include <iostream>
#include <cmath>

struct Vector3D {double x, y, z;};

double A, B, C;

const int cubeWidth = 20;
const int width = 160;
const int height = 40;
char video[width * height];
double zbuffer[width * height];

double cX(int x, int y, int z) {
  return y * std::sin(A) * std::sin(B) * std::cos(C) - z * std::cos(A) * std::sin(B) * std::cos(C) + y * std::cos(A) * std::sin(C) + z * std::sin(A) * std::sin(C) + x * std::cos(B)* std::cos(C);
} 

double cY(int x, int y, int z) {
  return y * std::cos(A) * std::cos(C) + z * std::sin(A) * std::cos(C) - y * std::sin(A) * std::sin(B) * std::sin(C) + z * std::cos(A) *std::sin(B) * std::sin(C) - x * std::cos(B) * std::sin(C);
}

double cZ(int x, int y, int z) {
  return z * std::cos(A) * std::cos(B) - y * std::sin(A) * std::cos(B) + x * std::sin(B);  
}


int main() {
  std::cout << "\033[2J"; //clears terminal screen
  double x, y, z;
  x = 10;
  y = 10;
  z = 10;
  for (int i = 0; i < width * height; ++i) {
    video[i] = ' ';
  }

  int distFromCam = 100;
  int K1 = 40;
  double depth = z + distFromCam;
  double px= K1 * x/depth;
  double py = K1 * y/depth;
  int screenX = width/2 + px * 2;
  int screenY = height/2 + py * 2;

  int index = screenY * width + screenX;
  video[index] = '#';

  for ( int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      std::cout << video[row * width + col];
    }
    std::cout << '\n';
  }


  return 0;
}
