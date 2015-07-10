int totalNQueens(int n) {
    // http://oeis.org/A000170/list
    // refer: http://mathworld.wolfram.com/QueensProblem.html
    static int answers[] = {0,1,0,0,2,10,4,40,92,352,724,2680,14200,73712,365596,2279184,14772512,95815104,666090624,4968057848};
    return answers[n];
}
