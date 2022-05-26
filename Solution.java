
import java.util.LinkedList;
import java.util.Queue;

public class Solution {

    private static record Point(int row, int column){}
    private static int[][] moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    private static final char START = '*';
    private static final char FOOD = '#';
    private static final char FREE_SPACE = 'O';
    private static final char OBSTACLE = 'X';
    private static final int NO_PATH_FOUND = -1;

    private int rows;
    private int columns;

    public int getFood(char[][] matrix) {
        rows = matrix.length;
        columns = matrix[0].length;
        return findShortestPathByBreadthFirstSearch(matrix);
    }

    private int findShortestPathByBreadthFirstSearch(char[][] matrix) {

        Queue<Point> queue = new LinkedList<>();
        Point start = findStartPoint(matrix);
        queue.add(start);

        boolean[][] visited = new boolean[rows][columns];
        visited[start.row][start.column] = true;
        int distanceFromStart = 0;

        while (!queue.isEmpty()) {

            for (int i = queue.size(); i > 0; --i) {

                Point point = queue.poll();
                if (matrix[point.row][point.column] == FOOD) {
                    return distanceFromStart;
                }

                for (int[] move : moves) {
                    int nextRow = point.row + move[0];
                    int nextColumn = point.column + move[1];

                    if (isInMatrix(nextRow, nextColumn) && !visited[nextRow][nextColumn] && matrix[nextRow][nextColumn] != OBSTACLE) {
                        visited[nextRow][nextColumn] = true;
                        queue.add(new Point(nextRow, nextColumn));
                    }
                }
            }
            ++distanceFromStart;
        }
        return NO_PATH_FOUND;
    }

    private Point findStartPoint(char[][] matrix) {
        Point point = null; //start point is guaranteed to exist.
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                if (matrix[r][c] == START) {
                    point = new Point(r, c);
                    break;
                }
            }
        }
        return point;
    }

    private boolean isInMatrix(int row, int column) {
        return row >= 0 && row < rows && column >= 0 && column < columns;
    }
}
