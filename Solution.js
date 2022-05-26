
/**
 * @param {character[][]} matrix
 * @return {number}
 */
var getFood = function (matrix) {
    this.START = '*';
    this.FOOD = '#';
    this.FREE_SPACE = 'O';
    this.OBSTACLE = 'X';
    this.NO_PATH_FOUND = -1;
    this.moves = [[-1, 0], [1, 0], [0, -1], [0, 1]];

    this.rows = matrix.length;
    this.columns = matrix[0].length;

    return findShortestPathByBreadthFirstSearch(matrix);

};

/**
 * @param {character[][]} matrix
 * @return {number}
 */
function findShortestPathByBreadthFirstSearch(matrix) {

    const queue = new Queue();
    let start = findStartPoint(matrix);
    queue.enqueue(start);

    const visited = Array.from(new Array(this.rows), () => new Array(this.columns));
    visited[start.row][start.column] = true;
    let distanceFromStart = 0;

    while (!queue.isEmpty()) {

        for (let i = queue.size(); i > 0; --i) {

            let point = queue.dequeue();
            if (matrix[point.row][point.column] === this.FOOD) {
                return distanceFromStart;
            }

            for (let move of this.moves) {
                let nextRow = point.row + move[0];
                let nextColumn = point.column + move[1];

                if (isInMatrix(nextRow, nextColumn) && !visited[nextRow][nextColumn] && matrix[nextRow][nextColumn] !== this.OBSTACLE) {
                    visited[nextRow][nextColumn] = true;
                    queue.enqueue(new Point(nextRow, nextColumn));
                }
            }
        }
        ++distanceFromStart;
    }
    return this.NO_PATH_FOUND;
}

/**
 * @param {character[][]} matrix
 * @return {Point}
 */
function findStartPoint(matrix) {
    let point = null; //start point is guaranteed to exist.
    for (let r = 0; r < this.rows; ++r) {
        for (let c = 0; c < this.columns; ++c) {
            if (matrix[r][c] === this.START) {
                point = new Point(r, c);
                break;
            }
        }
    }
    return point;
}

/**
 * @param {number} row
 * @param {number} column 
 * @return {boolean}
 */
function isInMatrix(row, column) {
    return row >= 0 && row < this.rows && column >= 0 && column < this.columns;
}

/**
 * @param {number} row
 * @param {number} column 
 */
function Point(row, column) {
    this.row = row;
    this.column = column;
}
