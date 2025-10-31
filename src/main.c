#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

#define ASSERT(Expression) if(!(Expression)) {*(int *)0 = 0;}

typedef uint32_t u32;
typedef int32_t s32;
typedef uint64_t u64;

#define BOARD_SQUARE_COUNT 120
#define MAX_GAME_MOVES 2048

typedef enum
{
    PieceType_Empty = 0,
    PieceType_WhitePawn = 1,
    PieceType_WhiteKnight = 2,
    PieceType_WhiteBishop = 3,
    PieceType_WhiteRook = 4,
    PieceType_WhiteQueen = 5,
    PieceType_WhiteKing = 6,
    PieceType_BlackPawn = 7,
    PieceType_BlackKnight = 8,
    PieceType_BlackBishop = 9,
    PieceType_BlackRook = 10,
    PieceType_BlackQueen = 11,
    PieceType_BlackKing = 12,
} piece_type;

enum
{
    File_A = 0,
    File_B = 1,
    File_C = 2,
    File_D = 3,
    File_E = 4,
    File_F = 5,
    File_G = 6,
    File_H = 7,
    File_None = 8,
};

enum
{
    Rank_1 = 0,
    Rank_2 = 1,
    Rank_3 = 2,
    Rank_4 = 3,
    Rank_5 = 4,
    Rank_6 = 5,
    Rank_7 = 6,
    Rank_8 = 7,
    Rank_None = 8,
};

enum
{
    Color_White = 0,
    Color_Black = 1,
    Color_Both = 2,
};

enum
{
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    No_Square
};

enum
{
    Castle_WhiteKing = 1,
    Castle_WhiteQueen  = 2,
    Castle_BlackKing = 4,
    Castle_BlackQueen = 8,
};

typedef struct
{
    int move;
    int castle_perms;
    int en_passant_square;
    int fifty_move_counter;
    u64 position_key;

} undo_move_info;

typedef struct
{
    s32 pieces[BOARD_SQUARE_COUNT];

    // represents each of the 64 squares on the board with 1 bit
    // if there's a pawn of that color there, the bit is 1
    u64 pawns[3];

    s32 king_square[2];
    s32 side_to_move;
    s32 en_passant_square;
    s32 fifty_move_counter;
    s32 ply;
    s32 his_ply;
    s32 castle_perms;

    u64 position_key;

    // how many pieces are there on the board for each type
    s32 piece_count[13];

    // anything that isn't a pawn, for each color
    s32 big_pieces_count[3];

    // rooks and queens
    s32 major_pieces_count[3];

    // bishops and knights
    s32 minor_pieces_count[3];

    undo_move_info move_history[MAX_GAME_MOVES];

    s32 piece_list[13][10];

} board;

static s32 Global_Square120To64[BOARD_SQUARE_COUNT];
static s32 Global_Square64To120[64];

#define FILE_AND_RANK_TO_SQUARE_120(f, r) ( (21 + (f)) + ((r) * 10))
#define SQUARE_64(square120) (Global_Square120To64[square120]) 

void InitSquare120To64()
{
    for(s32 i = 0; i < BOARD_SQUARE_COUNT; i++)
    {
        Global_Square120To64[i] = 65;
    }

    for(s32 i = 0; i < 64; i++)
    {
        Global_Square64To120[i] = 120;
    }

    s32 square64 = 0;
    for(s32 rank = Rank_1; rank <= Rank_8; rank++)
    {
        for(s32 file = File_A; file <= File_H; file++)
        {
            s32 square = FILE_AND_RANK_TO_SQUARE_120(file, rank);
            Global_Square64To120[square64] = square;
            Global_Square120To64[square] = square64;
            square64++;
        }
    }
}

void PrintBitBoard(u64 bit_board)
{
    printf("\n");
    for(s32 rank = Rank_8; rank >= Rank_1; rank--)
    {
        for(s32 file = File_A; file <= File_H; file++)
        {
            s32 square = FILE_AND_RANK_TO_SQUARE_120(file, rank);
            s32 square64 = SQUARE_64(square);

            u64 shift = 1ULL << square64;
            if(shift & bit_board)
            {
                printf(" X ");
            }
            else
            {
                printf(" - ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    InitSquare120To64();

    for(s32 i = 0; i < BOARD_SQUARE_COUNT; i++)
    {
        if(i % 10 == 0) printf("\n");
        printf("%5d", Global_Square120To64[i]);
    }

    printf("\n");
    printf("\n");
    for(s32 i = 0; i < 64; i++)
    {
        if(i % 8 == 0) printf("\n");
        printf("%5d", Global_Square64To120[i]);
    }

    u64 bit_board = 0ULL;
    bit_board = bit_board | (1ULL << SQUARE_64(B2));
    bit_board = bit_board | (1ULL << SQUARE_64(F6));
    PrintBitBoard(bit_board);

    return(0);
}

