#include <iostream>
#include <cstdlib>
using namespace std;

int mapp[4][4];

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
					count ++;
				}
			}
			
			for(int p = 1;p <= (5-count);p++){
				cout << " ";
			}
			
			cout << mapp[i][j];
		}

		printf("\n");
	}
}

int main() {

	mapp[2][3] = 2;
	mapp[1][3] = 2;
	mapp[0][3] = 2;
	mapp[0][0] = 4;

	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%5d", mapp[i][j]);
		}

		printf("\n");
	}

	printf("\n");

	while (true) {
		bool up = true;
		bool down = true;
		bool left = true;
		bool right = true;

		if (up) {
			// 向上移动和合并
			for (int j = 0; j < 4; j++) { // 遍历每一列
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
			for (int j = 0; j < 4; j++) { // 遍历每一列
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
			for (int i = 0; i < 4; i++) { // 遍历每一行
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
			for (int i = 0; i < 4; i++) { // 遍历每一行
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

		break;
	}

	outputWithFormat();

	return 0;
}
