#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <thread>
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

class AsciiRenderer {
private:
  int width, height;
  double world_scale; // 1文字が物理空間の何メートルに相当するか

public:
  AsciiRenderer(int w, int h, double scale)
      : width(w), height(h), world_scale(scale) {}

  void render(const std::vector<Body> &bodies) {
    // 1. 画面クリア (ANSIエスケープシーケンス)
    // \033[2J: 画面全体をクリア
    // \033[H: カーソルを左上(Home)に戻す
    std::cout << "\033[2J\033[H";

    // 2. フレームバッファの準備 (空白で埋める)
    // y座標が外側、x座標が内側の二次元配列(文字列のリスト)
    std::vector<std::string> buffer(height, std::string(width, ' '));

    // 3. ラスタライズ (物体をバッファに配置)
    for (const auto &body : bodies) {
      Vec2 pos = body.get_pos();

      // 座標変換: 物理座標(中心0,0) -> 画面座標(左上が0,0)
      // アスペクト比補正: 文字は縦長なので、x座標を広げると円に見える
      int screen_x = static_cast<int>(pos.x / world_scale * 2.0 + width / 2.0);
      int screen_y = static_cast<int>(pos.y / world_scale * 1.0 + height / 2.0);

      // 画面外チェック (セグメンテーション違反防止)
      if (screen_x >= 0 && screen_x < width && screen_y >= 0 &&
          screen_y < height) {
        // 太陽なら '@', それ以外(地球)なら 'O'
        char symbol = (body.get_mass() > 100.0) ? '@' : 'O';
        buffer[screen_y][screen_x] = symbol;
      }
    }

    // 4. バッファの出力 (描画)
    for (const auto &line : buffer) {
      std::cout << line << "\n";
    }
  }
};

int main() {
  double G = 1.0;
  double t_max = 200.0;
  double dt = 0.1;

  std::vector<Body> bodies;

  bodies.push_back(Body("Sun", 1000.0, Vec2(0.0, 0.0), Vec2(0.0, 0.0)));
  bodies.push_back(Body("Earth", 1.0, Vec2(0, 100), Vec2(3.0, 0)));

  AsciiRenderer renderer(80, 40, 5.0);

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
    renderer.render(bodies);
    for (auto &b : bodies) {
      b.update_post(dt);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  return 0;
}
