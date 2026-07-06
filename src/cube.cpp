#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

struct Vector3D {double x, y, z;};

double A, B, C; 
int distFromCam = 100;
int K1 = 40;
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

void plot(double fx, double fy, double fz, char ch) {
  Vector3D p = {cX(fx, fy, fz), cY(fx, fy, fz), cZ(fx, fy, fz) };
  double depth = p.z + distFromCam;
  int screenX = width/2 + K1 * p.x / depth * 2;
  int screenY = height/2 + K1 * p.y / depth;
  int index = screenY * width + screenX; //flatten from 3D to 2D
  if (index >= 0 && index < width * height) {
    video[index] = ch;
  }

}

int main() {
  double x, y, z;
  x = 10;
  y = 10;
  z = 10;
  while(true){  
    std::cout << "\033[2J"; //clears terminal screen 

    for (int i = 0; i < width * height; ++i) {
      video[i] = ' ';
    }
  
    for (double cx = -cubeWidth; cx < cubeWidth; cx += 0.15) {
      for (double cy = -cubeWidth; cy < cubeWidth; cy += 0.15) {
        plot(cx, cy, cubeWidth, '#');
        plot(cx, cy, -cubeWidth, '.');
        plot(cubeWidth, cy, cx, '?');
        plot(-cubeWidth, cy, cx, '$');
        plot(cx, cubeWidth, cy, '!');
        plot(cx, cubeWidth, cy, '@');
      }
    }
  
    for ( int row = 0; row < height; ++row) {
      for (int col = 0; col < width; ++col) {
        
        std::cout << video[row * width + col];
      }
      std::cout << '\n';
    }
    A+= 0.05; B += 0.05; C += 0.05;
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  

  return 0;
}
