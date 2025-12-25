#include <cmath>
#include <iostream>
#include <string>
#include <vector>

struct Vec2 {
  double x, y;

  Vec2(double _x = 0, double _y = 0) : x(_x), y(_y) {}

  // vector + vector
  Vec2 operator+(const Vec2 &other)
      const { // const&
              // を使用するのはオリジナルの変数を読むだけにとどめ，新しいメモリへのコピーを防ぐため
    return Vec2(x + other.x, y + other.y);
  }

  // vector - vector
  Vec2 operator-(const Vec2 &other) const {
    return Vec2(x - other.x, y - other.y);
  }

  // vector * scalar
  Vec2 operator*(double scalar) const { return Vec2(scalar * x, scalar * y); }

  // 長さの2乗
  double length_sq() const { return x * x + y * y; }

  // 長さ(sqrt)
  double length() const { return std::sqrt(length_sq()); }

  // dot product
  double dot(const Vec2 &other) const { return x * other.x + y * other.y; }
}; // オブジェクトは基本的にconst&で受け取る

Vec2 operator*(double scalar, const Vec2 &v) { return v * scalar; }

class Body {
private:
  std::string name;
  double m;
  Vec2 pos;
  Vec2 vel;
  Vec2 force;

public:
  Body(std::string _name, double _m, Vec2 _pos, Vec2 _vel)
      : name(_name), m(_m), pos(_pos), vel(_vel) {}

  Vec2 get_pos() const { return pos; }
  Vec2 get_vel() const { return vel; }
  double get_mass() const { return m; }
  std::string get_name() const { return name; }

  void clear_force() { force = 0.0; }

  void add_force(const Vec2 &f) { force = force + f; }

  // 速度を半歩進める
  void update_pre(double dt) {
    Vec2 a = force * (1.0 / m);
    pos = pos + vel * dt + 0.5 * a * dt * dt;
    vel = vel + 0.5 * a * dt;
  }

  // 新しい力を使って速度を仕上げる
  void update_post(double dt) {
    Vec2 a = force * (1.0 / m);
    vel = vel + 0.5 * a * dt;
  }
};

int main() {
  double G = 1.0;
  double t_max = 200.0;
  double dt = 0.1;

  std::vector<Body> bodies;

  bodies.push_back(Body("Sun", 1000.0, Vec2(0.0, 0.0), Vec2(0.0, 0.0)));
  bodies.push_back(Body("Earth", 1.0, Vec2(0, 100), Vec2(3.0, 0)));

  std::cout << "time, x, y, vx, vy" << std::endl;

  for (double t = 0.0; t < t_max; t += dt) {
    // pre_step
    for (auto &b : bodies) {
      b.update_pre(dt);
    }

    // force calculation
    for (auto &b : bodies) {
      b.clear_force();
    }

    for (size_t i = 0; i < bodies.size(); ++i) {
      for (size_t j = i + 1; j < bodies.size(); ++j) {
        Vec2 r_vec = bodies[j].get_pos() - bodies[i].get_pos();
        double dist = r_vec.length();
        double dist_sq = r_vec.length_sq();

        if (dist < 1e-4)
          continue;

        double f_mag =
            G * bodies[i].get_mass() * bodies[j].get_mass() / dist_sq;

        Vec2 f_vec = r_vec * (f_mag / dist);

        bodies[i].add_force(f_vec);        // 作用
        bodies[j].add_force(f_vec * -1.0); // 反作用
      }
    }

    for (auto &b : bodies) {
      b.update_post(dt);
    }

    std::cout << t << ", " << bodies[1].get_pos().x << ", "
              << bodies[1].get_pos().y << ", " << bodies[1].get_vel().x << ", "
              << bodies[1].get_vel().y << std::endl;
  }

  return 0;
}
