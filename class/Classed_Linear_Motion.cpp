#include <iostream>

class PhysicsObject {
private: // メンバ変数
  double x;
  double v;
  double const m;

public: // メンバ関数
  PhysicsObject(double initial_x, double initial_v, double initial_m)
      : x(initial_x), v(initial_v), m(initial_m) {
    // x = initial_x;
    // 上を初期化子リストという->中身が入った状態で箱を製造するという操作 v =
    // initial_v; こっちの場合は？->からの箱を作ってから，中身を入れる操作
  } // 生成時に値を確定させておきたい->初期化子リストを使おう

  void update(double force, double dt) {
    double a = force / m;
    x = x + v * dt + 0.5 * a * dt * dt;
    v = v + a * dt;
  }

  void print_status() const {
    std::cout << "Current x = " << x << ", Current v = " << v << std::endl;
  }
};

int main() {
  double t_max = 10.0;
  double dt = 1.0;
  double force = 1.0;

  PhysicsObject p1(0, 0, 1);
  p1.print_status();

  for (double t = 0.0; t < t_max; t += dt) {
    p1.update(1, dt);
    p1.print_status();
  }

  return 0;
}
