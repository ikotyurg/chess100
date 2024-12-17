#include "board_replay.h"

BoardReplay::BoardReplay(QObject *parent) : QObject(parent)
{
    board.resize(100); // Установим необходимый размер вектора
    std::fill(board.begin(), board.end(), Men::None); // Заполняем вектор значением Men::None
}

void BoardReplay::initBoard(QVector<Move> moves)
{
    this->moves = QVector<Move>(moves);
    turn = true;
    status = Status::Play;
    nMove = -1;
    for (int i = 0; i < 10; ++i){
        board[i  + 20]  = Men::None;
        board[i + 30] = Men::None;
        board[i + 40] = Men::None;
        board[i + 50] = Men::None;
        board[i + 60] = Men::None;
        board[i + 70] = Men::None;
                       board[i + 80] = Men::WPawn;
                       board[i + 10] = Men::BPawn;
               }
               board[1] = board[7] = board[2] = board[8] = Men::BKnight;
               board[91] = board[92] = board[97] = board[98] = Men::WKnight;
               board[3] = board[6] = Men::BBishop;
               board[93] = board[96] = Men::WBishop;
               board[0] = board[9] = Men::BRook;
               board[90] = board[99] = Men::WRook;
               board[4] = Men::BQueen;
               board[94] = Men::WQueen;
               board[5] = Men::BKing;
               board[95] = Men::WKing;
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
                board[x + 10 * y] = static_cast<Men>(men);
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
                board[x + 10 * y] = static_cast<Men>(men);
            }
            --this->nMove;
        }
        status = Status(moves[this->nMove].status);
        turn = nMove % 2;
        emit moved(board, int(status), turn);
    }

}
