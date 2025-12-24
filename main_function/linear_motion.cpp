#include <iostream>

int main() {
  double x0;
  // \n:
  // 直前のログがバッファに残ったまま消滅->どこまで計算が進んだのかわからないかも
  // std::endl->改行を出力＋バッファをフラッシュ->デバッグや進捗表示で観測の同時性を保証
  // std::endlは便利だが，ループで使ったりするとフラッシュ処理により速度が低下する
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

  double x = x0 + v0 * t +
             0.5 * a * t * t; // 0.5fのほうが明示的な型(自動でfloatになるけど)
  std::cout << "Position at t = " << t << " is " << x << std::endl;

  return 0;
}
