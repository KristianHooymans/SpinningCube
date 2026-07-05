#include <iostream>
#include <cmath>

const int width = 80;
const int height = 40;
const int video[width * height];


void normalise(double x, double y, double z) {
  double norm = std::sqrt(x * x + y * y + z * z);
  if (norm > 0.00000001) {
    x /= norm;
    y /= norm;
    z /= norm;
  }
}


int main() {
  double x, y, z;
  std::cout << "Input x y z ";
  std::cin >> x >> y >> z;

  std::vector<double> rotationalAxis(2);
  rotationalAxis[0] = x;
  rotationalAxis[1] = y;
  rotationalAxis[2] = z;

  double angle = 0.0;
  double diffAngle = 0.05;



  return 0;
}
