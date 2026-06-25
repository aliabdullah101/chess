//
// Created by aaa_3 on 2/7/2026.
//

#ifndef CHESS_HEADER_H
#define CHESS_HEADER_H
//variables/constants
#define WHITE 0
#define BLACK 1
#define PROMOTION_WHITE 2
#define PROMOTION_BLACK 3
#define PASSANT_FLAG_WHITE 4
#define PASSANT_FLAG_BLACK 5
#define CASTLING_KING 6
#define CASTLING_QUEEN 7
#define END_OF_ARRAY 92387
extern int turn;
extern int w_kr_flag;
extern int w_qr_flag;
extern int b_kr_flag;
extern int b_qr_flag;
extern char board[9][9];
//board generation and game setup
void generate_board();
void initialize_board();
void game_loop();
int game_end();
//general validity
int turn_valid(int x1, int y1, int x2, int y2);
int empty_spot(int x, int y);
int same_color(int x1, int y1, int x2, int y2);
int out_of_bounds(int x1, int y1, int x2, int y2);
int not_your_piece(int x, int y);
//piece validity
int pawn_check(int x1, int y1, int x2, int y2);
int rook_check(int x1, int y1, int x2, int y2);
int knight_check(int x1, int y1, int x2, int y2);
int bishop_check(int x1, int y1, int x2, int y2);
int queen_check(int x1, int y1, int x2, int y2);
int king_check(int x1, int y1, int x2, int y2);
//global validity
int global_validity(int x1, int y1, int x2, int y2);
int king_safety(int x1, int y1, int x2, int y2);
int castling(int k_rook, int q_rook, int side);
int passant_check(int pawn_flag, int board_flag);
int* scan_board(char piece);//returns coordinates of all of that piece
int safe_square(int x1, int y1, int color);
int generic_check(int attacked_x, int attacked_y ,char piece, int (*check)(int,int,int,int));
#endif //CHESS_HEADER_H