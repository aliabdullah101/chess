#include <stdio.h>
#include "chess.h"
int turn = WHITE;
char board[9][9];
int w_kr_flag=0;
int w_qr_flag=0;
int b_kr_flag=0;
int b_qr_flag=0;
int main() {
    initialize_board();
    generate_board();
    printf("Move format: xpos1 ypos1 xpos2 ypos2\n");
    printf("To Castle Kingside please type 10 10 10 10\n");
    printf("To Castle Queenside please type 0 0 0 0\n");
    printf("White's move:");
    int i=1;
    while (i) {
      if (game_end()) {
          i--;
      }
        game_loop();
    }
    printf("game over\n");
    return 0;
}
void generate_board() {
    int i,j;
    for (j = 0; j <= 8; j++) {
        for (i = 0; i <= 8; i++) {
            if (i==0&&j==0) {
                printf("  ");
                continue;
            }
                printf("%c ",board[i][j]);
        }
        printf("\n");
    }
}
void initialize_board() {
    int i;
    for (i = 0; i <= 8; i++) {
        board[i][2]='p';//black pieces are lowercase
        int j;
        for (j=3; j<=6;j++) {
            board[i][j]='x'; //middle of the board is blank for now
        }
        board[i][7]='P';//white pieces are uppercase
        board[0][i]='9'-i;
        board[i][0]='0'+i;
    }
    board[1][1]=board[8][1]='r';
    board[1][8]=board[8][8]='R';

    board[2][1]=board[7][1]='n';
    board[2][8]=board[7][8]='N';

    board[3][1]=board[6][1]='b';
    board[3][8]=board[6][8]='B';

    board[4][1]='q';
    board[4][8]='Q';

    board[5][1]='k';
    board[5][8]='K';

    //board[2][2]='P'; //here in case I want to test promotion
}
void game_loop() {
    int xpos1, ypos1, xpos2, ypos2;
    scanf("%d%d%d%d",&xpos1,&ypos1,&xpos2,&ypos2);
    if (turn_valid(xpos1,ypos1,xpos2,ypos2)) {
        char promotion = 1;
        if (turn_valid(xpos1, ypos1, xpos2, ypos2)==PROMOTION_WHITE) {
            printf("Promote the pawn to a Queen (Q), Rook (R), Bishop (B), or Knight (N): ");
            scanf("%c",&promotion);
            while (promotion!='Q' && promotion!='R'&& promotion!='B' && promotion!='N') {
                printf("Invalid choice please enter Q, R, B, or N");
                scanf("%c",&promotion);
            }
            board[xpos2][9-ypos2] = promotion;
        }
        if (turn_valid(xpos1, ypos1, xpos2, ypos2)==PROMOTION_BLACK) {
            printf("Promote the pawn to a queen (q), Rook (r), Bishop (b), or Knight (n): ");
            scanf("%c",&promotion);
            while (promotion!='q'&& promotion!='r' && promotion!='b' && promotion!='n') {
                printf("Invalid choice please enter q, r, b, or n");
                scanf("%c",&promotion);
            }
            board[xpos2][9-ypos2] = promotion;
        }
        if (out_of_bounds(xpos1,ypos1,xpos2,ypos2)==CASTLING_KING) {
            if (turn == WHITE) {
                board[7][8]='K';
                board[6][8]='R';
                board[5][8]='x';
                board[8][8]='x';
            }
            if (turn == BLACK) {
                board[7][1]='k';
                board[6][1]='r';
                board[5][1]='x';
                board[8][1]='x';
            }
            generate_board();
            turn=(turn+1)%2;
            if (turn==WHITE) {
                printf("\nWhite's move: ");
            }
            if (turn==BLACK) {
                printf("\nBlack's move: ");
            }
            return;
        }
        if (out_of_bounds(xpos1,ypos1,xpos2,ypos2)==CASTLING_QUEEN) {
            //same thing.
        }
        turn=(turn+1)%2;
        char tmp = board[xpos1][9-ypos1];
        board[xpos1][9-ypos1]='x';
        if (board[xpos2][9-ypos2]!=promotion) {
            board[xpos2][9-ypos2]=tmp;
        }
        if (board[1][1]!='r'){b_qr_flag=1;}
        if (board[8][1]!='r'){b_kr_flag=1;}
        if (board[1][8]!='R'){w_qr_flag=1;}
        if (board[8][8]!='R'){w_kr_flag=1;}
        if (board[5][1]!='k'){b_qr_flag=1;b_kr_flag=1;}//if the king moves then it can't castle with either rook
        if (board[5][8]!='K'){w_qr_flag=1;w_kr_flag=1;}
        //so far for castling have put the set-up efforts into it, but haven't actually moved the pieces yet.
        generate_board();
        if (turn==WHITE) {
            printf("\nWhite's move: ");
        }
        if (turn==BLACK) {
            printf("\nBlack's move: ");
        }
    }
    else {
        printf("\nInvalid move \nMake a different move: ");
    }
}
int game_end() {
    return 0;
    //add game ending conditions later
}
int sign(int n) {
    if (n>0) return 1;
    if (n<0) return -1;
    return 0;
}