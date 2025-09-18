#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

#define ASSERT(Expression) if(!(Expression)) {*(int *)0 = 0;}

#define BOARD_SIZE 64
#define BOARD_SIDE_LENGTH 8

typedef uint32_t u32;
typedef int32_t s32;

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

void PrintBoard(piece_type board_state[BOARD_SIZE])
{
    for(s32 i = 0; i < BOARD_SIDE_LENGTH; i++)
    {
        for(s32 j = 0; j < BOARD_SIDE_LENGTH; j++)
        {
            piece_type piece = board_state[i * BOARD_SIDE_LENGTH + j];
            char piece_char;
            switch(piece)
            {
                case(PieceType_WhitePawn):
                {
                    piece_char = 'p';
                } break;
                case(PieceType_WhiteKnight):
                {
                    piece_char = 'n';
                } break;
                case(PieceType_WhiteBishop):
                {
                    piece_char = 'b';
                } break;
                case(PieceType_WhiteRook):
                {
                    piece_char = 'r';
                } break;
                case(PieceType_WhiteQueen):
                {
                    piece_char = 'q';
                } break;
                case(PieceType_WhiteKing):
                {
                    piece_char = 'k';
                } break;
                case(PieceType_BlackPawn):
                {
                    piece_char = 'P';
                } break;
               case(PieceType_BlackKnight):
                {
                    piece_char = 'N';
                } break;
                case(PieceType_BlackBishop):
                {
                    piece_char = 'B';
                } break;
                case(PieceType_BlackRook):
                {
                    piece_char = 'R';
                } break;
                case(PieceType_BlackQueen):
                {
                    piece_char = 'Q';
                } break;
                case(PieceType_BlackKing):
                {
                    piece_char = 'K';
                } break;
                case(PieceType_Empty):
                {
                    piece_char = '-';
                } break;
            }
            printf("%c ", piece_char);
        }
        printf("\n");
    }
}

int main(void)
{
    piece_type board_state[BOARD_SIZE] =
    {
        PieceType_BlackRook, PieceType_BlackKnight, PieceType_BlackBishop, PieceType_BlackQueen, PieceType_BlackKing,
                             PieceType_BlackBishop, PieceType_BlackKnight, PieceType_BlackRook,
        PieceType_BlackPawn, PieceType_BlackPawn, PieceType_BlackPawn, PieceType_BlackPawn, PieceType_BlackPawn,
                             PieceType_BlackPawn, PieceType_BlackPawn, PieceType_BlackPawn,   
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        PieceType_WhitePawn, PieceType_WhitePawn, PieceType_WhitePawn, PieceType_WhitePawn, PieceType_WhitePawn,
                             PieceType_WhitePawn, PieceType_WhitePawn, PieceType_WhitePawn,
        PieceType_WhiteRook, PieceType_WhiteKnight, PieceType_WhiteBishop, PieceType_WhiteQueen, PieceType_WhiteKing,
                             PieceType_WhiteBishop, PieceType_WhiteKnight, PieceType_WhiteRook,
    };
    PrintBoard(board_state);

    return(0);
}

