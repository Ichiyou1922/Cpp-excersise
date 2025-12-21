#include <cmath>
#include <iostream>

class Vector2D {
private:
  // private指定で外部からの直接書き換えを禁止（カプセル化）
  // 意図しない値の書き換えを防ぐ
  double x;
  double y;

public:
  // 「メンバ関数（メソッド）」
  // public指定により，外部から呼び出し可能にする
  //
  // 1. コンストラクタ(Constructor)
  // クラス名と同じ名前の関数．戻り値なし．
  // 生成時に必ず呼ばれるため，ここで初期化を保証する．
  // Vector2D(double init_x, double init_y) {
  //  x = init_x;
  //  y = init_y;
  //}
  Vector2D(double init_x, double init_y) : x(init_x), y(init_y) {}
  // ↑メンバ初期化子リスト
  // コンストラクタ本体で代入するより効率的かつ推奨される記法

  // 演算子オーバーロードの実装
  // 引数：const Vector2D& other ->
  // 相手を読み取り専用の参照として受け取る(コピー回避) 末尾のconst:
  // この関数を実行しても，自分自身(x, y)は変化しないという誓約
  Vector2D operator+(const Vector2D &other) const {
    return Vector2D(x + other.x, y + other.y);
  }

  Vector2D operator-(const Vector2D &other) const {
    return Vector2D(x - other.x, y - other.y);
  }
  // 2. アクセサ(Getter)
  // privateなデータを読み取るための窓口
  double getX() const {
    return x;
  } // constは「この関数内でメンバ変数を変更しない」という誓約
  double getY() const { return y; }

  // 3. 機能の実装
  // ノルム計算
  double norm() const;

  // 情報の表示
  void print() const;
};

// クラスの外側で関数を書く場合は クラス名::関数名(スコープ解決演算子)をつかう
double Vector2D::norm() const {
  // クラス内部なので，x, yに直接アクセスできる．
  return std::sqrt(x * x + y * y);
}

void Vector2D::print() const {
  // std::coutはprintfの進化版. 型指定子など不要．
  std::cout << "Vector(" << x << ", " << y << ")" << std::endl;
}

int main() {
  Vector2D v1(10.0, 20.0);
  Vector2D v2(3.0, 5.0);

  Vector2D v_add = v1 + v2;
  std::cout << "v1 + v2 = ";
  v_add.print();

  Vector2D v_sub = v1 - v2;
  v_sub.print();

  Vector2D v3(1.0, 1.0);
  Vector2D v_result = v1 + v2 - v3;
  std::cout << "v1 + v2 - v3 = ";
  v_result.print();
  return 0;
}
