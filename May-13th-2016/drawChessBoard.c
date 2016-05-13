#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum ChessPieceType {
    ChessPieceType_None,
    ChessPieceType_Pawn,
    ChessPieceType_Knight,
    ChessPieceType_Bishop,
    ChessPieceType_Rook,
    ChessPieceType_Queen,
    ChessPieceType_King
};

enum Color {
    Color_None,
    Color_Black,
    Color_White
};

enum ChessBoardRow {
    ChessBoardRow_One, 
    ChessBoardRow_Two, 
    ChessBoardRow_Three, 
    ChessBoardRow_Four,
    ChessBoardRow_Five, 
    ChessBoardRow_Six, 
    ChessBoardRow_Seven, 
    ChessBoardRow_Eight
};

const char* CHESS_BOARD_ROW_STRING_TABLE[] = {
    [ChessBoardRow_One]     = "1",
    [ChessBoardRow_Two]     = "2",
    [ChessBoardRow_Three]   = "3",
    [ChessBoardRow_Four]    = "4",
    [ChessBoardRow_Five]    = "5",
    [ChessBoardRow_Six]     = "6",
    [ChessBoardRow_Seven]   = "7",
    [ChessBoardRow_Eight]   = "8",
};

enum ChessBoardColumn {
    ChessBoardColumn_A, 
    ChessBoardColumn_B,
    ChessBoardColumn_C,
    ChessBoardColumn_D,
    ChessBoardColumn_E,
    ChessBoardColumn_F,
    ChessBoardColumn_G,
    ChessBoardColumn_H
};

const char* CHESS_BOARD_COLUMN_STRING_TABLE[] = {
    [ChessBoardColumn_A] = "A",
    [ChessBoardColumn_B] = "B",
    [ChessBoardColumn_C] = "C",
    [ChessBoardColumn_D] = "D",
    [ChessBoardColumn_E] = "E",
    [ChessBoardColumn_F] = "F",
    [ChessBoardColumn_G] = "G",
    [ChessBoardColumn_H] = "H",
};

struct ChessPiece {
    enum ChessPieceType type;
    enum Color color;
};

int ChessPieceNew(struct ChessPiece* chessPiece, enum ChessPieceType type, enum Color color);

int ChessPieceMakePawn(struct ChessPiece* chessPiece, enum Color color);

int ChessPieceMakeKnight(struct ChessPiece* chessPiece, enum Color color);

int ChessPieceMakeBishop(struct ChessPiece* chessPiece, enum Color color);

int ChessPieceMakeRook(struct ChessPiece* chessPiece, enum Color color);

int ChessPieceMakeQueen(struct ChessPiece* chessPiece, enum Color color);

int ChessPieceMakeKing(struct ChessPiece* chessPiece, enum Color color);

int ChessPieceMakeNone(struct ChessPiece* chessPiece);

int ChessPieceDraw(const struct ChessPiece* chessPiece, FILE* stream);

struct ChessSquare {
    struct ChessPiece piece;
    enum ChessBoardRow row;
    enum ChessBoardColumn col;
};

int ChessSquareNew(
    struct ChessSquare* chessSquare,
    enum ChessBoardRow row, 
    enum ChessBoardColumn col,
    const struct ChessPiece* chessPiece);

typedef struct ChessSquare ChessBoard[ChessBoardRow_Eight + 1][ChessBoardColumn_H + 1];

int ChessBoardNew(ChessBoard chessBoard);

int ChessBoardDraw(ChessBoard chessBoard, FILE* stream);

int main(void) {
    
    ChessBoard chessBoard = { 0 };
    (void) ChessBoardNew(chessBoard);
    (void) ChessBoardDraw(chessBoard, stdout);
    
    (void) getchar();

    return EXIT_SUCCESS;
}

int ChessBoardNew(ChessBoard chessBoard) {
    if (!chessBoard) {
        return 1;
    }
    struct ChessPiece chessPiece = { 0 };
    
    // ROW ONE

    (void) ChessPieceMakeRook(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_One][ChessBoardColumn_A], ChessBoardRow_One, ChessBoardColumn_A, &chessPiece);

    (void) ChessPieceMakeKnight(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_One][ChessBoardColumn_B], ChessBoardRow_One, ChessBoardColumn_B, &chessPiece);

    (void) ChessPieceMakeBishop(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_One][ChessBoardColumn_C], ChessBoardRow_One, ChessBoardColumn_C, &chessPiece);    

    (void) ChessPieceMakeQueen(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_One][ChessBoardColumn_D], ChessBoardRow_One, ChessBoardColumn_D, &chessPiece);

    (void) ChessPieceMakeKing(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_One][ChessBoardColumn_E], ChessBoardRow_One, ChessBoardColumn_E, &chessPiece);

    (void) ChessPieceMakeBishop(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_One][ChessBoardColumn_F], ChessBoardRow_One, ChessBoardColumn_F, &chessPiece);    

    (void) ChessPieceMakeKnight(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_One][ChessBoardColumn_G], ChessBoardRow_One, ChessBoardColumn_G, &chessPiece);    

    (void) ChessPieceMakeRook(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_One][ChessBoardColumn_H], ChessBoardRow_One, ChessBoardColumn_H, &chessPiece);    

    // ROW TWO

    (void) ChessPieceMakePawn(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Two][ChessBoardColumn_A], ChessBoardRow_Two, ChessBoardColumn_A, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Two][ChessBoardColumn_B], ChessBoardRow_Two, ChessBoardColumn_B, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Two][ChessBoardColumn_C], ChessBoardRow_Two, ChessBoardColumn_C, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Two][ChessBoardColumn_D], ChessBoardRow_Two, ChessBoardColumn_D, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Two][ChessBoardColumn_E], ChessBoardRow_Two, ChessBoardColumn_E, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Two][ChessBoardColumn_F], ChessBoardRow_Two, ChessBoardColumn_F, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Two][ChessBoardColumn_G], ChessBoardRow_Two, ChessBoardColumn_G, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_White);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Two][ChessBoardColumn_H], ChessBoardRow_Two, ChessBoardColumn_H, &chessPiece);    

    // ROW THREE

    (void) ChessPieceMakeNone(&chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Three][ChessBoardColumn_A], ChessBoardRow_Three, ChessBoardColumn_A, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Three][ChessBoardColumn_B], ChessBoardRow_Three, ChessBoardColumn_B, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Three][ChessBoardColumn_C], ChessBoardRow_Three, ChessBoardColumn_C, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Three][ChessBoardColumn_D], ChessBoardRow_Three, ChessBoardColumn_D, &chessPiece);    
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Three][ChessBoardColumn_E], ChessBoardRow_Three, ChessBoardColumn_E, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Three][ChessBoardColumn_F], ChessBoardRow_Three, ChessBoardColumn_F, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Three][ChessBoardColumn_G], ChessBoardRow_Three, ChessBoardColumn_G, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Three][ChessBoardColumn_H], ChessBoardRow_Three, ChessBoardColumn_H, &chessPiece);    

    // ROW FOUR

    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Four][ChessBoardColumn_A], ChessBoardRow_Four, ChessBoardColumn_A, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Four][ChessBoardColumn_B], ChessBoardRow_Four, ChessBoardColumn_B, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Four][ChessBoardColumn_C], ChessBoardRow_Four, ChessBoardColumn_C, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Four][ChessBoardColumn_D], ChessBoardRow_Four, ChessBoardColumn_D, &chessPiece);    
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Four][ChessBoardColumn_E], ChessBoardRow_Four, ChessBoardColumn_E, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Four][ChessBoardColumn_F], ChessBoardRow_Four, ChessBoardColumn_F, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Four][ChessBoardColumn_G], ChessBoardRow_Four, ChessBoardColumn_G, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Four][ChessBoardColumn_H], ChessBoardRow_Four, ChessBoardColumn_H, &chessPiece);    

    // ROW FIVE

    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Five][ChessBoardColumn_A], ChessBoardRow_Five, ChessBoardColumn_A, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Five][ChessBoardColumn_B], ChessBoardRow_Five, ChessBoardColumn_B, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Five][ChessBoardColumn_C], ChessBoardRow_Five, ChessBoardColumn_C, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Five][ChessBoardColumn_D], ChessBoardRow_Five, ChessBoardColumn_D, &chessPiece);    
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Five][ChessBoardColumn_E], ChessBoardRow_Five, ChessBoardColumn_E, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Five][ChessBoardColumn_F], ChessBoardRow_Five, ChessBoardColumn_F, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Five][ChessBoardColumn_G], ChessBoardRow_Five, ChessBoardColumn_G, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Five][ChessBoardColumn_H], ChessBoardRow_Five, ChessBoardColumn_H, &chessPiece);    

    // ROW SIX

    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Six][ChessBoardColumn_A], ChessBoardRow_Six, ChessBoardColumn_A, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Six][ChessBoardColumn_B], ChessBoardRow_Six, ChessBoardColumn_B, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Six][ChessBoardColumn_C], ChessBoardRow_Six, ChessBoardColumn_C, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Six][ChessBoardColumn_D], ChessBoardRow_Six, ChessBoardColumn_D, &chessPiece);    
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Six][ChessBoardColumn_E], ChessBoardRow_Six, ChessBoardColumn_E, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Six][ChessBoardColumn_F], ChessBoardRow_Six, ChessBoardColumn_F, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Six][ChessBoardColumn_G], ChessBoardRow_Six, ChessBoardColumn_G, &chessPiece);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Six][ChessBoardColumn_H], ChessBoardRow_Six, ChessBoardColumn_H, &chessPiece);    

    // ROW SEVEN

    (void) ChessPieceMakePawn(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Seven][ChessBoardColumn_A], ChessBoardRow_Seven, ChessBoardColumn_A, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Seven][ChessBoardColumn_B], ChessBoardRow_Seven, ChessBoardColumn_B, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Seven][ChessBoardColumn_C], ChessBoardRow_Seven, ChessBoardColumn_C, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Seven][ChessBoardColumn_D], ChessBoardRow_Seven, ChessBoardColumn_D, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Seven][ChessBoardColumn_E], ChessBoardRow_Seven, ChessBoardColumn_E, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Seven][ChessBoardColumn_F], ChessBoardRow_Seven, ChessBoardColumn_F, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Seven][ChessBoardColumn_G], ChessBoardRow_Seven, ChessBoardColumn_G, &chessPiece);    

    (void) ChessPieceMakePawn(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Seven][ChessBoardColumn_H], ChessBoardRow_Seven, ChessBoardColumn_H, &chessPiece);

    // ROW EIGHT

    (void) ChessPieceMakeRook(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Eight][ChessBoardColumn_A], ChessBoardRow_Eight, ChessBoardColumn_A, &chessPiece);    

    (void) ChessPieceMakeKnight(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Eight][ChessBoardColumn_B], ChessBoardRow_Eight, ChessBoardColumn_B, &chessPiece);    

    (void) ChessPieceMakeBishop(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Eight][ChessBoardColumn_C], ChessBoardRow_Eight, ChessBoardColumn_C, &chessPiece);    

    (void) ChessPieceMakeQueen(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Eight][ChessBoardColumn_D], ChessBoardRow_Eight, ChessBoardColumn_D, &chessPiece);    

    (void) ChessPieceMakeKing(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Eight][ChessBoardColumn_E], ChessBoardRow_Eight, ChessBoardColumn_E, &chessPiece);

    (void) ChessPieceMakeBishop(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Eight][ChessBoardColumn_F], ChessBoardRow_Eight, ChessBoardColumn_F, &chessPiece);    

    (void) ChessPieceMakeKnight(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Eight][ChessBoardColumn_G], ChessBoardRow_Eight, ChessBoardColumn_G, &chessPiece);    

    (void) ChessPieceMakeRook(&chessPiece, Color_Black);
    (void) ChessSquareNew(&chessBoard[ChessBoardRow_Eight][ChessBoardColumn_H], ChessBoardRow_Eight, ChessBoardColumn_H, &chessPiece);

    return 0;
}

int ChessPieceNew(struct ChessPiece* chessPiece, enum ChessPieceType type, enum Color color) {
    if (!chessPiece) {
        return 1;
    }
    if (type < ChessPieceType_None || type > ChessPieceType_King) {
        return 2;
    }
    if (color != Color_Black && color != Color_White && color != Color_None) {
        return 3;
    }
    chessPiece->type = type;
    chessPiece->color = color;

    return 0;
}

int ChessPieceMakePawn(struct ChessPiece* chessPiece, enum Color color) {
    if (!chessPiece) {
        return 1;
    }
    if (color != Color_Black && color != Color_White && color != Color_None) {
        return 2;
    }
    (void) ChessPieceNew(chessPiece, ChessPieceType_Pawn, color);
    
    return 0;
}

int ChessPieceMakeKnight(struct ChessPiece* chessPiece, enum Color color) {
    if (!chessPiece) {
        return 1;
    }
    if (color != Color_Black && color != Color_White && color != Color_None) {
        return 2;
    }
    (void) ChessPieceNew(chessPiece, ChessPieceType_Knight, color);

    return 0;
}

int ChessPieceMakeBishop(struct ChessPiece* chessPiece, enum Color color) {
    if (!chessPiece) {
        return 1;
    }
    if (color != Color_Black && color != Color_White && color != Color_None) {
        return 2;
    }
    (void) ChessPieceNew(chessPiece, ChessPieceType_Bishop, color);

    return 0;
}

int ChessPieceMakeRook(struct ChessPiece* chessPiece, enum Color color) {
    if (!chessPiece) {
        return 1;
    }
    if (color != Color_Black && color != Color_White && color != Color_None) {
        return 2;
    }
    (void) ChessPieceNew(chessPiece, ChessPieceType_Rook, color);

    return 0;
}

int ChessPieceMakeQueen(struct ChessPiece* chessPiece, enum Color color) {
    if (!chessPiece) {
        return 1;
    }
    if (color != Color_Black && color != Color_White && color != Color_None) {
        return 2;
    }
    (void) ChessPieceNew(chessPiece, ChessPieceType_Queen, color);

    return 0;
}

int ChessPieceMakeKing(struct ChessPiece* chessPiece, enum Color color) {
    if (!chessPiece) {
        return 1;
    }
    if (color != Color_Black && color != Color_White && color != Color_None) {
        return 2;
    }
    (void) ChessPieceNew(chessPiece, ChessPieceType_King, color);

    return 0;
}

int ChessPieceMakeNone(struct ChessPiece* chessPiece) {
    if (!chessPiece) {
        return 1;
    }
    (void) ChessPieceNew(chessPiece, ChessPieceType_None, Color_None);

    return 0;
}

int ChessSquareNew(
    struct ChessSquare* chessSquare,
    enum ChessBoardRow row, 
    enum ChessBoardColumn col,
    const struct ChessPiece* chessPiece)
{
    if (!chessSquare) {
        return 1;
    }
    if (col < ChessBoardColumn_A || col > ChessBoardColumn_H) {
        return 2;
    }
    if (row < ChessBoardRow_One || row > ChessBoardRow_Eight) {
        return 3;
    }
    if (!chessPiece) {
        return 4;
    }
    chessSquare->col = col;
    chessSquare->row = row;

    chessSquare->piece.color = chessPiece->color;
    chessSquare->piece.type = chessPiece->type;

    return 0;
}

int ChessBoardDraw(ChessBoard chessBoard, FILE* stream) {
    if (!chessBoard) {
        return 1;
    }
    if (!stream) {
        return 2;    
    }

    const static char* SEPARATOR = "|";

    for (enum ChessBoardRow row = ChessBoardRow_Eight; row >= ChessBoardRow_One; --row) {
        (void) fprintf(stream, "%s%s", CHESS_BOARD_ROW_STRING_TABLE[row], SEPARATOR);
        for (enum ChessBoardColumn col = ChessBoardColumn_A; col <= ChessBoardColumn_H; ++col) {
            (void) ChessPieceDraw(&chessBoard[row][col].piece, stream);
            (void) fprintf(stream, "%s", SEPARATOR);
        }
        (void) putchar('\n');
    }
    
    (void) fprintf(stream, "  ");
    for (enum ChessBoard col = ChessBoardColumn_A; col <= ChessBoardColumn_H; ++col) {
        (void) fprintf(stream, "%s ", CHESS_BOARD_COLUMN_STRING_TABLE[col]);
    }

    return 0;
}

int ChessPieceDraw(const struct ChessPiece* chessPiece, FILE* stream) {
    if (!chessPiece) {
        return 1;
    }
    if (!stream) {
        return 2;
    }
    if (chessPiece->type < ChessPieceType_None || chessPiece->type > ChessPieceType_King) {
        return 3;
    }
    if (chessPiece->color != Color_White 
        && chessPiece->color != Color_Black 
        && chessPiece->color != Color_None) {
        return 4;
    }
    
    const static char* WHITE_CHESS_PIECE_STRING_TABLE[] = {
        [ChessPieceType_None]       = "_",
        [ChessPieceType_Pawn]       = "p",
        [ChessPieceType_Knight]     = "k",
        [ChessPieceType_Bishop]     = "b",
        [ChessPieceType_Rook]       = "r",
        [ChessPieceType_Queen]      = "q",
        [ChessPieceType_King]       = "k"
    };

    const static char* BLACK_CHESS_PIECE_STRING_TABLE[] = {
        [ChessPieceType_None]       = "_",
        [ChessPieceType_Pawn]       = "P",
        [ChessPieceType_Knight]     = "K",
        [ChessPieceType_Bishop]     = "B",
        [ChessPieceType_Rook]       = "R",
        [ChessPieceType_Queen]      = "Q",
        [ChessPieceType_King]       = "K"
    };

    const static char* NONE_CHESS_PIECE_STRING_TABLE[] = {
        [ChessPieceType_None]       = "_",
        [ChessPieceType_Pawn]       = "?",
        [ChessPieceType_Knight]     = "?",
        [ChessPieceType_Bishop]     = "?",
        [ChessPieceType_Rook]       = "?",
        [ChessPieceType_Queen]      = "?",
        [ChessPieceType_King]       = "?"
    };

    const char* str = NULL;
    
    if (chessPiece->color == Color_None) {
        str = NONE_CHESS_PIECE_STRING_TABLE[chessPiece->type];
    } else if (chessPiece->color == Color_Black) {
        str = BLACK_CHESS_PIECE_STRING_TABLE[chessPiece->type];
    } else if (chessPiece->color == Color_White) {
        str = WHITE_CHESS_PIECE_STRING_TABLE[chessPiece->type];
    } else {
        str = " ";
    }

    (void) fprintf(stream, "%s", str);

    return 0;
}
