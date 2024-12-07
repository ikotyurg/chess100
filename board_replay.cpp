#include "board_replay.h"

BoardReplay::BoardReplay(QObject *parent) : QObject(parent)
{
    board = new int*[10];
    for (int i = 0; i < 10; ++i){
        board[i] = new int[10];
    }
}

void BoardReplay::initBoard(QVector<Move> moves)
{
    this->moves = QVector<Move>(moves);
    turn = true;
    status = Status::Play;
    nMove = -1;
    for (int i = 0; i < 10; ++i){
            board[i][2] = board[i][3] = board[i][4] = board[i][5] = board[i][6] =board[i][7] = Men::None;
            board[i][8] = Men::WPawn;
            board[i][1] = Men::BPawn;
    }
    board[1][0] = board[2][0] = board[7][0] = board[8][0] = Men::BKnight;
    board[1][9] = board[2][9] = board[7][9] = board[8][9] = Men::WKnight;
    board[3][0] = board[6][0] = Men::BBishop;
    board[3][9] = board[6][9] = Men::WBishop;
    board[0][0] = board[9][0] = Men::BRook;
    board[0][9] = board[9][9] = Men::WRook;
    board[4][0] = Men::BQueen;
    board[4][9] = Men::WQueen;
    board[5][0] = Men::BKing;
    board[5][9] = Men::WKing;
    emit moved(board, int(status), turn);
}

void BoardReplay::move(int nMove)
{
    if (nMove != this->nMove && nMove >= 0 && nMove < moves.count()){
        int men, x, y;
        while (nMove > this->nMove){
            ++this->nMove;
            int ms[4] = {moves[this->nMove].cell_from, moves[this->nMove].cell_to,
                         moves[this->nMove].cell_add1, moves[this->nMove].cell_add2};
            for (int i = 0; i < 4; ++i) {
                if (ms[i] == 0) continue;
                x = ms[i] % 13; ms[i] /= 13;
                y = ms[i] % 13; ms[i] /= 13;
                men = (ms[i] / 13) % 13 - 6;
                board[x][y] = men;
            }
        }
        while (nMove < this->nMove){
            int ms[4] = {moves[this->nMove].cell_from, moves[this->nMove].cell_to,
                         moves[this->nMove].cell_add1, moves[this->nMove].cell_add2};
            for (int i = 0; i < 4; ++i) {
                if (ms[i] == 0) continue;
                x = ms[i] % 13; ms[i] /= 13;
                y = ms[i] % 13; ms[i] /= 13;
                men = ms[i] % 13 - 6;
                board[x][y] = men;
            }
            --this->nMove;
        }
        status = Status(moves[this->nMove].status);
        turn = nMove % 2;
        emit moved(board, int(status), turn);
    }

}
