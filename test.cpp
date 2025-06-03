#include <iostream>
#include <string.h>
void boardmod(int xind, int yind, int bw, int bh, int val, long* board){
    board[xind + yind * bh] = val;
}
void printarr(long* board, int bw, int bh){
    for(int i=0;i<bh;i++){
        for(int j=0;j<bw;j++){
            std::cout << board[j + i * bw] << ' ';
        }
        std::cout << '\n';
    }
}
int main(){
    long board[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    printarr(board, 3, 3);
    boardmod(1, 1, 3, 3, 200, board);
    printarr(board, 3, 3);
}
