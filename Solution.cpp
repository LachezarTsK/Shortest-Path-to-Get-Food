
#include <array>
#include <queue>
#include <vector>
using namespace std;

class Solution {

    struct Point {
        int row{};
        int column{};
        Point(int row, int column) : row {row}, column {column} {}

        Point() = default;
        virtual ~Point() = default; //virtual: no derived structs but for the sake of good practice.

        Point(const Point& p) = default;
        Point& operator=(const Point& p) = default;

        Point(Point&& p) noexcept = default;
        Point& operator=(Point&& p) noexcept = default;
    };

    inline static const array<array<int, 2>, 4> moves{ {{-1, 0}, {1, 0}, {0, -1}, {0, 1}} };
    inline static const char START = '*';
    inline static const char FOOD = '#';
    inline static const char FREE_SPACE = 'O';
    inline static const char OBSTACLE = 'X';
    inline static const int NO_PATH_FOUND = -1;

    size_t rows;
    size_t columns;

public:
    int getFood(vector<vector<char>>&matrix) {
        rows = matrix.size();
        columns = matrix[0].size();
        return findShortestPathByBreadthFirstSearch(matrix);
    }

private:
    int findShortestPathByBreadthFirstSearch(const vector<vector<char>>& matrix) {

        queue<Point> queue;
        Point start = findStartPoint(matrix);
        queue.push(start);

        vector < vector<bool>> visited(rows, vector<bool>(columns));
        visited[start.row][start.column] = true;
        int distanceFromStart = 0;

        while (!queue.empty()) {

            for (int i = queue.size(); i > 0; --i) {

                Point point = queue.front();
                queue.pop();
                if (matrix[point.row][point.column] == FOOD) {
                    return distanceFromStart;
                }

                for (const auto& move : moves) {
                    int nextRow = point.row + move[0];
                    int nextColumn = point.column + move[1];

                    if (isInMatrix(nextRow, nextColumn) && !visited[nextRow][nextColumn] && matrix[nextRow][nextColumn] != OBSTACLE) {
                        visited[nextRow][nextColumn] = true;
                        queue.push(Point(nextRow, nextColumn));
                    }
                }
            }
            ++distanceFromStart;
        }
        return NO_PATH_FOUND;
    }

    Point findStartPoint(const vector<vector<char>>& matrix) {
        Point point{}; //start point is guaranteed to exist.
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                if (matrix[r][c] == START) {
                    point = Point(r, c);
                    break;
                }
            }
        }
        return point;
    }

    bool isInMatrix(int row, int column) {
        return row >= 0 && row < rows && column >= 0 && column < columns;
    }
};
