#include <functional>
#include <iostream>

class PhysicsObject {
private:
  double x;
  double v;
  double const m;

public:
  PhysicsObject(double initial_x, double initial_v, double initial_m)
      : x(initial_x), v(initial_v), m(initial_m) {}

  void pre_step(double force_current, double dt) {
    double a = force_current / m;
    x = x + v * dt + 0.5 * a * dt * dt;
    v = v + 0.5 * a * dt;
  }

  double x_getter() { return x; }
  double v_getter() { return v; }

  void post_step(double force_next, double dt) {
    double a_next = force_next / m;
    v = v + 0.5 * a_next * dt;
  }

  void print_status() {
    std::cout << "Current x = " << x << ", Current v = " << v << std::endl;
  }
};

using ForceRule = std::function<double(double, double, double)>;

int main() {
  double t_max = 20.0;
  double dt = 0.5;
  double initial_force = 1.0;
  double k = 0.5;
  double gamma = 0.1;

  ForceRule damped_oscillator = [k, gamma](double x, double v, double t) {
    return -k * x - gamma * v;
  };

  PhysicsObject p1(0, 0, 1.0);
  double current_force = initial_force;
  p1.print_status();

  for (double t = 0.0; t < t_max; t += dt) {
    p1.pre_step(current_force, dt);

    double next_force = damped_oscillator(p1.x_getter(), p1.v_getter(), t + dt);

    p1.post_step(next_force, dt);

    current_force = next_force;

    p1.print_status();
  }
  return 0;
}
