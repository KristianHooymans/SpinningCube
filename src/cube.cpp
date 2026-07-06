#include <iostream>
#include <cmath>

double A, B, C;

const int width = 80;
const int height = 60;
char video[width * height];
double zbuffer[width * height];

double cX(int x, int y, int z) {
  return y * std::sin(A) * std::sin(B) * std::cos(C) - z * std::cos(A) * std::sin(B) * std::cos(C) + y * std::cos(A) * std::sin(C) + z * std::sin(A) * std::sin(C) + x * std::cos(B)* std::cos(C);
} 

double cY(int x, int y, int z) {
  return y * std::cos(A) * std::cos(C) + z * std::sin(A) * std::cos(C) - y * std::sin(A) * std:sin(B) * std::sin(C) + z * std::cos(A) *std::sin(B) * std::sin(C) - x * std::cos(B) * std::sin(C);
}

double cZ(int x, int y, int z) {
  return z * std::cos(A) * std::cos(B) - y * std::sin(A) * std::cos(B) + x * std::sin(B);  
}


int main() {

}
