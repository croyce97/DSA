#include <iostream>
#include <vector>

using namespace std;

const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

void floodFillDFS(vector<vector<int>>& image, int x, int y, int oldColor, int newColor) {
    if (x < 0 || x >= image.size() || y < 0 || y >= image[0].size() || image[x][y] != oldColor) {
        return;
    }

    image[x][y] = newColor;

    for (int i = 0; i < 8; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        floodFillDFS(image, newX, newY, oldColor, newColor);
    }
}

void floodFill(vector<vector<int>>& image, int x, int y, int newColor) {
    int oldColor = image[x][y];

    if (oldColor != newColor) {
        floodFillDFS(image, x, y, oldColor, newColor);
    }
}

int main() {
    vector<vector<int>> image = {
        {1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1}
    };

    cout << "Ban dau:" << endl;
    for (const auto& row : image) {
        for (int pixel : row) {
            cout << pixel << " ";
        }
        cout << endl;
    }
    floodFill(image, 1, 1, 2);

    cout << "Sau khi thuc hien flood fill:" << endl;
    for (const auto& row : image) {
        for (int pixel : row) {
            cout << pixel << " ";
        }
        cout << endl;
    }

    return 0;
}
