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
  double m_getter() { return m; }

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
  double t_max = 10.0;
  double dt = 1.0;
  double initial_force = 1.0;
  double k = 0.5;
  double gamma = 0.0;

  std::vector<PhysicsObject> particles;
  std::vector<double> current_forces;

  ForceRule damped_oscillator = [k, gamma](double x, double v, double t) {
    return -k * x - gamma * v;
  };

  auto compute_energy = [k](double m, double x, double v) {
    return 0.5 * m * v * v + 0.5 * k * x * x;
  };

  PhysicsObject p1(0, 0, 1.0);
  particles.push_back(p1);
  PhysicsObject p2(10.0, -1, 2.0);
  particles.push_back(p2);
  current_forces.push_back(1.0);
  current_forces.push_back(2.0);
  particles[0].print_status();
  particles[1].print_status();

  for (double t = 0.0; t < t_max; t += dt) {
    for (size_t i = 0; i < particles.size(); ++i) {
      particles[i].pre_step(current_forces[i], dt);
      double next_force = damped_oscillator(particles[i].x_getter(),
                                            particles[i].v_getter(), t + dt);
      particles[i].post_step(next_force, dt);
      current_forces[i] = next_force;
      double E =
          compute_energy(particles[i].m_getter(), particles[i].x_getter(),
                         particles[i].v_getter());
      std::cout << "p" << i << ": x=" << particles[i].x_getter() << " E=" << E
                << std::endl;
    }
  }
  return 0;
}
