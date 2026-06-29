//
// Created by aaa_3 on 5/19/2026.
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "chess.h"
int global_validity(int x1, int y1, int x2, int y2) {
    if (!king_safety(x1, y1, x2, y2)) {
        return 0;
    }
    int pc = pawn_check(x1, y1, x2, y2);
    if (pc==PASSANT_FLAG_WHITE||pc==PASSANT_FLAG_BLACK) {
        int result = passant_check(pc,0xb0a4d);//potential board flag
        if (!result) {
            return 0;
        }
    }
    if (out_of_bounds(x1,9-y1,x2,9-y2)==CASTLING_KING) {
        if (turn == WHITE) {
            return castling(w_kr_flag,w_qr_flag,CASTLING_KING);
        }
        if (turn == BLACK) {
            return castling(b_kr_flag,b_qr_flag,CASTLING_KING);
        }
    }
    if (out_of_bounds(x1,9-y1,x2,9-y2)==CASTLING_QUEEN) {
        if (turn==WHITE) {
            return castling(w_kr_flag,w_qr_flag,CASTLING_QUEEN);
        }
        if (turn==BLACK) {
            return castling(b_kr_flag,b_qr_flag,CASTLING_QUEEN);
        }
    }
    return 1;
}
int castling(int k_rook, int q_rook, int side) {
    if (side==CASTLING_KING) {
        if (k_rook) {return 0;}
        if (turn==WHITE && board[7][8]!='x' && board[6][8]!='x'){return 0;}
        if (turn==BLACK && board[7][1]!='x' && board[6][1]!='x'){return 0;}
        if (!safe_square(7,8,WHITE)||!safe_square(6,8,WHITE)||!safe_square(5,8,WHITE)){return 0;}
        if (!safe_square(7,1,BLACK)||!safe_square(6,1,BLACK)||!safe_square(5,1,BLACK)){return 0;}
    }
    if (side==CASTLING_QUEEN) {
        if (q_rook){return 0;}
        if (turn==WHITE && board[2][8]!='x' && board[3][8]!='x' && board[4][8]!='x'){return 0;}
        if (turn==BLACK && board[2][1]!='x' && board[3][1]!='x' && board[4][1]!='x'){return 0;}
        if (!safe_square(2,8,WHITE)||!safe_square(3,8,WHITE)||!safe_square(4,8,WHITE)||!safe_square(5,8,WHITE)){return 0;}
        if (!safe_square(2,1,BLACK)||!safe_square(3,1,BLACK)||!safe_square(4,1,BLACK)||!safe_square(5,1,BLACK)){return 0;}
    }
    printf("1\n");
    return 1;
}
int king_safety(int x1, int y1, int x2, int y2) {
    return 1;
}
int passant_check(int pawn_flag, int board_flag) {
    return 1;
}
int* scan_board(char piece) {
    int* coordinates = (int*) malloc(21*sizeof(int));
    int i,j,k=0;
    for (i=1; i<8; i++) {
        for (j=1; j<8; j++) {
            if (board[i][j]==piece) {
                coordinates[k++]=i;
                coordinates[k++]=j;
            }
        }
    }
    coordinates[k]=END_OF_ARRAY;
    return coordinates;
}
int safe_square(int x1, int y1, int color) {
    //note start finishing castling
    if (color == WHITE) {
        //Pawn check is special
        int* pawns = scan_board('p');
        int i = 0, x2, y2;
        while (pawns[i] != END_OF_ARRAY) {
            x2 = pawns[i++];
            y2 = pawns[i++];
            if (y1 - y2 == 1 && abs(x2 - x1) == 1) {
                free(pawns);
                return 0;
            }
        }
        free(pawns);

        if (!generic_check(x1, y1, 'b', bishop_check)) {return 0;}
        if (!generic_check(x1, y1, 'r', rook_check))   {return 0;}
        if (!generic_check(x1, y1, 'n', knight_check)) {return 0;}
        if (!generic_check(x1, y1, 'q', queen_check))  {return 0;}
        if (!generic_check(x1, y1, 'k', king_check))   {return 0;}
    }
    if (color == BLACK) {
        int* pawns = scan_board('P');
        int i = 0, x2, y2;
        while (pawns[i] != END_OF_ARRAY) {
            x2 = pawns[i++];
            y2 = pawns[i++];
            if (y2 - y1 == 1 && abs(x2 - x1) == 1) {
                free(pawns);
                return 0;
            }
        }
        free(pawns);

        if (!generic_check(x1, y1, 'B', bishop_check)) {return 0;}
        if (!generic_check(x1, y1, 'R', rook_check))   {return 0;}
        if (!generic_check(x1, y1, 'N', knight_check)) {return 0;}
        if (!generic_check(x1, y1, 'Q', queen_check))  {return 0;}
        if (!generic_check(x1, y1, 'K', king_check))   {return 0;}
    }
    return 1;
}
int generic_check(int attacked_x, int attacked_y, char piece, int (*check)(int,int,int,int)) {
    int x2;
    int y2;
    int* array = scan_board(piece);
    int i=0;
    while (array[i]!=END_OF_ARRAY) {
        x2=array[i++];
        y2=array[i++];
        if (check(attacked_x,attacked_y,x2,y2)) {
            free(array);
            return 0;
        }
    }
    free(array);
    return 1;
}