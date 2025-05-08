/*
 * Projecr Name:        2048
 * Author:              Kelvin
 * Create Date:         2025/4/3
 * @copyright 2025
*/

#include <Arduino.h>
#include "Nokia_5110.h"

#define RST 12
#define CE 13
#define DC 11
#define DIN 10
#define CLK 9

Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);

int mapp[4][4];

void up();
void down();
void left();
void right();
void randomInt();
void outputWithFormat();
void initialRandomInt();
bool canContinue();

void setup() {
  // put your setup code here, to run once:
  //digitalWrite(7,1);
  randomSeed(analogRead(0));
  Serial.begin(115200);
  lcd.print("Beginning ...");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mapp[i][j] = 0;
    }
  }
  initialRandomInt();
  delay(500);
  outputWithFormat();
  //digitalWrite(7,0);
}

void loop() {
  // put your main code here, to run repeatedly:

  lcd.clear();

  outputWithFormat();

  delay(100);

  //randomInt();

  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  bool is_pressed = false;

  // 检测输入

  if (Serial.available()) {

    int x = Serial.read();

    Serial.println(x);

    if (x == 56) up = true;
    if (x == 50) down = true;
    if (x == 52) left = true;
    if (x == 54) right = true;

    if (x != 13) is_pressed = true;
  }

  // 执行操作

  if (up) {
    Serial.println("up");
    // 向上移动和合并
    for (int j = 0; j < 4; j++) {  // 遍历每一列
      // 移动非零元素到顶部
      int writePos = 0;

      for (int i = 0; i < 4; i++) {
        if (mapp[i][j] != 0) {
          if (writePos != i) {
            mapp[writePos][j] = mapp[i][j];
            mapp[i][j] = 0;
          }

          writePos++;
        }
      }

      // 合并相同的数字
      for (int i = 0; i < 3; i++) {
        if (mapp[i][j] != 0 && mapp[i][j] == mapp[i + 1][j]) {
          mapp[i][j] *= 2;
          mapp[i + 1][j] = 0;

          // 移动后面的元素填补空缺
          for (int k = i + 1; k < 3; k++) {
            mapp[k][j] = mapp[k + 1][j];
            mapp[k + 1][j] = 0;
          }
        }
      }
    }
  }

  if (down) {
    // 向下移动和合并
    for (int j = 0; j < 4; j++) {  // 遍历每一列
      // 移动非零元素到底部
      int writePos = 3;

      for (int i = 3; i >= 0; i--) {
        if (mapp[i][j] != 0) {
          if (writePos != i) {
            mapp[writePos][j] = mapp[i][j];
            mapp[i][j] = 0;
          }

          writePos--;
        }
      }

      // 合并相同的数字
      for (int i = 3; i > 0; i--) {
        if (mapp[i][j] != 0 && mapp[i][j] == mapp[i - 1][j]) {
          mapp[i][j] *= 2;
          mapp[i - 1][j] = 0;

          // 移动前面的元素填补空缺
          for (int k = i - 1; k > 0; k--) {
            mapp[k][j] = mapp[k - 1][j];
            mapp[k - 1][j] = 0;
          }
        }
      }
    }
  }

  if (left) {
    // 向左移动和合并
    for (int i = 0; i < 4; i++) {  // 遍历每一行
      // 移动非零元素到左侧
      int writePos = 0;

      for (int j = 0; j < 4; j++) {
        if (mapp[i][j] != 0) {
          if (writePos != j) {
            mapp[i][writePos] = mapp[i][j];
            mapp[i][j] = 0;
          }

          writePos++;
        }
      }

      // 合并相同的数字
      for (int j = 0; j < 3; j++) {
        if (mapp[i][j] != 0 && mapp[i][j] == mapp[i][j + 1]) {
          mapp[i][j] *= 2;
          mapp[i][j + 1] = 0;

          // 移动后面的元素填补空缺
          for (int k = j + 1; k < 3; k++) {
            mapp[i][k] = mapp[i][k + 1];
            mapp[i][k + 1] = 0;
          }
        }
      }
    }
  }

  if (right) {
    // 向右移动和合并
    for (int i = 0; i < 4; i++) {  // 遍历每一行
      // 移动非零元素到右侧
      int writePos = 3;

      for (int j = 3; j >= 0; j--) {
        if (mapp[i][j] != 0) {
          if (writePos != j) {
            mapp[i][writePos] = mapp[i][j];
            mapp[i][j] = 0;
          }

          writePos--;
        }
      }

      // 合并相同的数字
      for (int j = 3; j > 0; j--) {
        if (mapp[i][j] != 0 && mapp[i][j] == mapp[i][j - 1]) {
          mapp[i][j] *= 2;
          mapp[i][j - 1] = 0;

          // 移动前面的元素填补空缺
          for (int k = j - 1; k > 0; k--) {
            mapp[i][k] = mapp[i][k - 1];
            mapp[i][k - 1] = 0;
          }
        }
      }
    }
  }

  bool is_2048 = false;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (mapp[i][j] == 2048) {
        is_2048 = true;
      }
    }
  }

  if (is_2048) {
    lcd.clear();
    lcd.println("Game over");
    lcd.println("You win");
    return;
  }

  if (!canContinue()) {
    lcd.clear();
    lcd.println("Game over");
    lcd.println("You lose");

    return;
  }

  if (is_pressed) {
    bool is_empty = false;
    for (int i = 1; i < 4; i++) {
      for (int j = 1; j < 4; j++) {
        if (mapp[i][j] == 0) {
          is_empty = true;
        }
      }
    }
    if (is_empty) randomInt();
  }
}

void randomInt() {
  int A = random(16);
  int q;
  int column, line;

  if (A == 0) {
    q = 4;
  } else {
    q = 2;
  }

  while (true) {
    column = random(4);
    line = random(4);
    if (mapp[column][line] == 0) {
      mapp[column][line] = q;
      break;
    }
  }
}

void outputWithFormat() {
  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {
      int number = mapp[i][j];
      int count = 0;

      if (number == 0) {
        count = 1;
      } else {
        while (number != 0) {
          number /= 10;
          count++;
        }
      }

      for (int p = 1; p <= (5 - count); p++) {
        lcd.print(" ");
      }

      lcd.print(mapp[i][j]);
    }

    lcd.print("\n");
  }
}

void initialRandomInt() {
  const int q = 2;
  int column, line1, line2;

  column = random(4);
  line1 = random(4);
  while (true) {
    line2 = random(4);
    if (line1 != line2) {
      break;
    }
  }

  mapp[column][line1] = q;
  mapp[column][line2] = q;
}

bool canContinue() {
  // 检查是否存在空位
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (mapp[i][j] == 0) {
        return true;  // 有空位，可以继续
      }
    }
  }

  // 检查横向相邻是否有相同的数字
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (mapp[i][j] == mapp[i][j + 1]) {
        return true;  // 存在可合并的相邻块
      }
    }
  }

  // 检查纵向相邻是否有相同的数字
  for (int j = 0; j < 4; ++j) {
    for (int i = 0; i < 3; ++i) {
      if (mapp[i][j] == mapp[i + 1][j]) {
        return true;  // 存在可合并的相邻块
      }
    }
  }

  // 盘面已满且无法合并，游戏结束
  return false;
}
