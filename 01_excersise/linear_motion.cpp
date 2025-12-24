#include <iostream>

int main() {
  double x0;
  std::cout << "Put the x0" << std::endl;
  std::cin >> x0;

  double v0;
  std::cout << "Put the v0" << std::endl;
  std::cin >> v0;

  double a;
  std::cout << "Put the a" << std::endl;
  std::cin >> a;

  double t;
  std::cout << "Put the t" << std::endl;
  std::cin >> t;

  double x = x0 + v0 * t + 0.5 * a * t * t;
  std::cout << "Position at t = " << t << " is " << x << std::endl;

  return 0;
}
