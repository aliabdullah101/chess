//
// Created by aaa_3 on 2/7/2026.
//
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include "chess.h"
int sign(int n);
int check=0;
int turn_valid(int x1, int y1, int x2, int y2) {
    if (empty_spot(x1,y1)) {
        //can't move a magical piece from an empty spot
        printf("Nothing was there\n");
        return 0;
    }
    if (same_color(x1,y1,x2,y2)) {
        //can't capture your own pieces
        printf("Same color\n");
        return 0;
    }
    if (out_of_bounds(x1,y1,x2,y2)==1) {
        //trying to access a piece out of bounds, or move it out of bounds
        printf("Out of bounds\n");
        return 0;
    }
    /*if (out_of_bounds(x1,y1,x2,y2)==CASTLING_KING || out_of_bounds(x1,y1,x2,y2)==CASTLING_QUEEN) {
        //if castling skip all the other checks
        return global_validity(x1,9-y1,x2,9-y2);
    }*/
    if (not_your_piece(x1,y1)) {
        //trying to move the opponents pieces
        printf("Not your piece\n");
        return 0;
    }
    if (x1>0 && y1>=0 && x1<=9 && y1<9) {
        switch (board[x1][9-y1]) {
            case 'p':
            case 'P':
                printf("Pawn\n");
                check = pawn_check(x1,9-y1,x2,9-y2);
                break;
            case 'r':
            case 'R':
                printf("Rook\n");
                check = rook_check(x1,9-y1,x2,9-y2);
                break;
            case 'n':
            case 'N':
                printf("Knight\n");
                check = knight_check(x1,9-y1,x2,9-y2);
                break;
            case 'b':
            case 'B':
                printf("Bishop\n");
                check = bishop_check(x1,9-y1,x2,9-y2);
                break;
            case 'q':
            case 'Q':
                printf("Queen\n");
                check = queen_check(x1,9-y1,x2,9-y2);
                break;
            case 'k':
            case 'K':
                printf("King\n");
                check = king_check(x1,9-y1,x2,9-y2);
                break;
            default: fprintf(stderr,"Error");
        }
    }
    //global validity
    if (!global_validity(x1,9-y1,x2,9-y2)){return 0;}
    return check;
}
int empty_spot(int x, int y) {
    if (board[x][9-y] == 'x') {
        return 1;
    }
    return 0;
}
int same_color(int x1, int y1, int x2, int y2) {
    if (isupper(board[x1][9-y1]) && isupper(board[x2][9-y2])) {
        return 1;
    }
    if (islower(board[x1][9-y1]) && islower(board[x2][9-y2]) && board[x2][9-y2] != 'x') {
        return 1;
    }
    return 0;
}
int out_of_bounds(int x1, int y1, int x2, int y2) {
    if (x1==10 && x2==10 && y1 == 10 && y2 == 10){
        return CASTLING_KING;
    }
    if (x1==0 && x2==0 && y1==0 && y2 == 0) {
        return CASTLING_QUEEN;
    }
    if (x1 > 8 || x1 < 1 || x2 > 8 || x2 < 1 || y1 > 8 || y1 < 1 || y2 > 8 || y2 < 1) {
        return 1;
    }
    return 0;
}
int not_your_piece(int x, int y) {
    if (turn==WHITE && islower(board[x][9-y])) {
        printf("That is black's piece.\n");
        return 1;
    }
    if (turn==BLACK && isupper(board[x][9-y])) {
        printf("That is white's piece.\n");
        return 1;
    }
    return 0;
}
int pawn_check(int x1,int y1,int x2,int y2) {
    //pawns cannot move forward if a friendly or enemy piece is in front of it
    if (turn==WHITE) {
        if (y1-y2==1 && x1==x2 && board[x2][y2]!='x') {
            return 0;
        }
    }
    if (turn==BLACK) {
        if (y2-y1==1 && x1==x2 && board[x2][y2]!='x') {
            return 0;
        }
    }
    //pawns normally move one space forward
    if (turn==WHITE) {
        if (y1-y2==1 && x1==x2 && y2!=1) {//y2!=1 so I can work on promotion
            return 1;
        }
    }
    if (turn==BLACK) {
        if (y2-y1==1 && x2==x1 && y2!=8) {
            return 1;
        }
    }
    //pawns can go two on the first move if unobstructed
    if (turn==WHITE) {
        if (y1-y2==2 && x1==x2 && y1==7 && board[x1][y1-1]=='x' && board[x1][y1-2]=='x') {
            return 1;
        }
    }
    if (turn==BLACK) {
        if (y2-y1==2 && x1==x2 && y1==2 && board[x1][y1+1]=='x' && board[x1][y1+2]=='x') {
            return 1;
        }
    }
    //pawns attack diagonally (when there is a piece there)
    if (turn==WHITE) {
        if (y1-y2==1 && abs(x2-x1)==1 && board[x2][y2]!='x' && y2!=1) {
            return 1;
        }
    }
    if (turn==BLACK) {
        if (y2-y1==1 && abs(x2-x1)==1 && board[x2][y2]!='x' && y2!=8) {
            return 1;
        }
    }
    //pawns can promote
    if (turn==WHITE) {
        if (y2==1) {
        return PROMOTION_WHITE; //different so can do it in the game loop
        }
    }
    if (turn==BLACK) {
        if (y2==8) {
            return PROMOTION_BLACK;
        }
    }
    //pawns can do en passant
    //flags are returned because these are necessary but not sufficient conditions for en passant
    if (turn==WHITE && y1 == 5 && y2 == 6 && board[x2][y2]=='x' && abs(x2-x1)==1 && board[x2][y2-1]=='p') {
        //return PASSANT_FLAG_WHITE;
    }
    if (turn==BLACK && y1 == 4 && y2 == 3 && board[x2][y2]=='x' && abs(x2-x1)==1 && board[x2][y2+1]=='P') {
       //return PASSANT_FLAG_BLACK;
    }

    return 0; //if pawn didn't follow any of these rules, declare it invalid
}
int rook_check(int x1, int y1, int x2, int y2) {
    //rooks can only move vertically or diagonally, not both
    if (x1!=x2 && y1!=y2) {
        return 0;
    }
    //rooks can't go beyond pieces
    int dist;
    for (dist=abs(x1-x2)+abs(y1-y2)-1; dist>0;dist--) {
        if (x1!=x2) {
            if (board[x1+sign(x2-x1)*dist][y1]!='x') {
                printf("%d\n",x1+sign(x2-x1)*dist);
                return 0;
            }
        }
        if (y1!=y2) {
            if (board[x1][y1+sign(y2-y1)*dist]!='x') {
                printf("%d\n",y1+sign(y2-y1)*dist);
                return 0;
            }
        }
    }
    return 1;
}
int knight_check(int x1, int y1, int x2, int y2) {
    if (abs(x1-x2)==2 && abs(y1-y2)==1) return 1;
    if (abs(x1-x2)==1 && abs(y1-y2)==2) return 1;
    return 0;
}
int bishop_check(int x1, int y1, int x2, int y2) {
    if (abs(y2-y1)!=abs(x2-x1)) {
    return 0; //restrict everything other than 45 degree diagonal
    }
    int dist; //same structure as the rook_check
    for (dist = 2*abs(x2-x1); dist>0;dist-=2) {
        //the for loop could be reduced, but symbolically represents both the Manhattan (|x|+|y|) distance
        if (board[x1+sign(x2-x1)*(dist/2)][y1+sign(y2-y1)*(dist/2)]!='x') {
            printf("%d\n",x1+sign(x2-x1)*(dist/2));
            return 0;
        }
    }
    return 1;
}
int queen_check(int x1, int y1, int x2, int y2) {
    return bishop_check(x1, y1, x2, y2) || rook_check(x1, y1, x2, y2);
}
int king_check(int x1, int y1, int x2, int y2) {
if (abs(x2-x1)>=2 || abs(y2-y1)>=2) {
    return 0;
}
    return 1;
}