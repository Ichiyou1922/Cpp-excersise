#include <iostream>

class PhysicsObject {
private: // メンバ変数
  double x;
  double v;

public: // メンバ関数
  PhysicsObject(double initial_x, double initial_v) {
    x = initial_x;
    v = initial_v;
  }

  void update(double a, double dt) {
    v = v + a * dt;
    x = x + v * dt + 0.5 * a * dt * dt;
  }

  void print_status() const {
    std::cout << "Current x = " << x << ", Current v = " << v << std::endl;
  }
};

int main() {
  double t_max = 10.0;
  double dt = 1.0;

  PhysicsObject p1(0, 0);

  for (double t = 0.0; t < t_max; t += dt) {
    p1.update(1, dt);
    p1.print_status();
  }

  return 0;
}
