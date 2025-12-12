# Cpp-excersise
Cppの練習用リポジトリ

## 入出力ライブラリ
- `<iostream>`，`std::cout`など
- C++のI/Oは「ストリーム」と「演算子オーバーロード」を使う設計

## 名前空間
- 例えば`std::cout`の`std`は名前空間
- `std`という名前空間を指定し，その中の機能を使う
- `std::cout`，`name::cout`のようにして区別できる

## コンパイラ
- `.cpp`を`g++`あるいは`clang++`でコンパイルする
```bash
g++ -std=c++17 main.cpp -o main
```

