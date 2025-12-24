#include <iostream>
#include <string>
// 物理シミュレーションにおいて，どう「参照渡し」と「値渡し」を分ける？
// 状態更新など書き換えのあるもの->戻り値voidで，引数は参照渡しdouble&
// 純粋計算など値を算出するだけのもの->戻り値doubleで，引数は値渡し(またはconst参照)

void get_input(double &target, const std::string name) {
  std::cout
      << name
      << std::
             endl; // constにすることで表示するだけで書き換えない設定に->関数を呼ぶたびに文字列のコピーが発生しない
  std::cin >> target;
}

double compute_position(double x0, double v0, double a, double t) {
  return x0 + v0 * t + 0.5 * a * t * t;
}

int main() {
  double x0, v0, a, t;
  get_input(x0, "Input x0: ");
  get_input(v0, "Input v0: ");
  get_input(a, "Input a: ");
  get_input(t, "Input t: ");

  std::cout << "Result is " << compute_position(x0, v0, a, t) << std::endl;

  return 0;
}
