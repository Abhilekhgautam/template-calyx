// created by void at 2026-09-05 19:10:20

#include <array>
#include <iostream>

// Single line buffer
// img: 3x3
// window: 2x2
class LineBuffer {
  std::array<int, 3> row0{};

  std::array<std::array<int, 2>, 2> reg_win{};

  int column_count{0};
  int row_count{0};

public:
  bool step(int pixel_in) {

    int po = row0[column_count];

    row0[column_count] = pixel_in;

    // Shift left the register.
    reg_win[0][0] = reg_win[0][1];
    reg_win[1][0] = reg_win[1][1];

    reg_win[0][1] = po;
    reg_win[1][1] = pixel_in;

    bool isValid = (row_count >= 1) && (column_count >= 1);

    column_count = (column_count + 1) % 3;

    if (column_count == 0) {
      row_count = row_count + 1;
    }

    return isValid;
  }

  void print_reg_win() {
    std::cout << "[" << reg_win[0][0] << " " << reg_win[0][1] << " " << '\n';
    std::cout << reg_win[1][0] << " " << reg_win[1][1] << " "
              << "]" << '\n';
  }
};

// img: 80x60
// window: 5x5
class BetterBuffer {
  std::array<int, 80> row0{};
  std::array<int, 80> row1{};
  std::array<int, 80> row2{};
  std::array<int, 80> row3{};

  std::array<std::array<int, 5>, 5> win_reg{};

  int col_count{0};
  int row_count{0};

public:
  bool step(int pixel_in) {
    int p0 = row0[col_count];
    int p1 = row1[col_count];
    int p2 = row2[col_count];
    int p3 = row3[col_count];

    row3[col_count] = p2;
    row2[col_count] = p1;
    row1[col_count] = p0;
    row0[col_count] = pixel_in;

    // Shift registers
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 4; ++j) {
        win_reg[i][j] = win_reg[i][j + 1];
      }
    }

    win_reg[0][4] = p0;
    win_reg[1][4] = p1;
    win_reg[2][4] = p2;
    win_reg[3][4] = p3;
    win_reg[4][4] = pixel_in;

    bool isValid = (row_count >= 4) && (col_count >= 4);

    col_count = (col_count + 1) % 80;

    if (col_count == 0) {
      row_count = row_count + 1;
    }

    return isValid;
  }

  void print_reg_win() {
    std::cout << "[" << win_reg[0][0] << " " << win_reg[0][1] << " "
              << win_reg[0][2] << " " << win_reg[0][3] << " " << win_reg[0][4]
              << '\n';

    std::cout << win_reg[1][0] << " " << win_reg[1][1] << " " << win_reg[1][2]
              << " " << win_reg[1][3] << " " << win_reg[1][4] << '\n';

    std::cout << win_reg[2][0] << " " << win_reg[2][1] << " " << win_reg[2][2]
              << " " << win_reg[2][3] << " " << win_reg[2][4] << '\n';

    std::cout << win_reg[3][0] << " " << win_reg[3][1] << " " << win_reg[3][2]
              << " " << win_reg[3][3] << " " << win_reg[3][4] << '\n';

    std::cout << win_reg[4][0] << " " << win_reg[4][1] << " " << win_reg[4][2]
              << " " << win_reg[4][3] << " " << win_reg[4][4] << "]" << '\n';
  }
};

int main() {
  BetterBuffer lb;
  std::array<int, 4800> img;
  for (int i = 0; i < 4800; i++) {
    img[i] = i;
  }
  int count = 0;
  for (const int px : img) {
    auto val = lb.step(px);
    if (val) {
      lb.print_reg_win();
      count++;
    }

    if (count > 20)
      break;
  }
}
