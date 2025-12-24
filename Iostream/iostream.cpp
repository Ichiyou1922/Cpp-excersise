#include <iostream>

int main() {
  // 変数宣言（C++では使用直前の宣言が推奨）
  double val;

  // 出力: std名前空間にあるcoutを使用
  // std::endl は改行＋フラッシュ(バッファの吐き出し)を行うマニピュレータ
  std::cout << "Eenter value: ";

  // 入力: std名前空間にあるcinを使用
  std::cin >> val;

  // 計算と出力の連鎖
  std::cout << "The value is " << val << std::endl;

  // 正常終了
  return 0;
}
