#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QPoint>
#include <QVector>
#include <tuple>
#include "men.h"
#include "status.h"

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(bool turn = true, QObject *parent = nullptr);
    ~Board();
    struct Move{
        int32_t cell_from;
        int32_t cell_to;
        int32_t cell_add1;
        int32_t cell_add2;
        int32_t status;
    };
    void rotateBoard();
private:
    bool turn;
    QVector <Men> fullBoard; // to check checks he-he 12*12
    QVector <Men> board;  // Основная доска
    QVector <Men> **rotated;  // Временная доска для поворота
    QVector<Move> moves;
    int nMove;
signals:
    void moved(QVector <Men> board, int status, bool turn);
    void promotion(bool);
    void message(QString msg);
    void sendLastMove(const std::pair<QString, Move>& move);
    void boardRotated(QVector <Men> board, int status, bool turn);
public slots:
    void move(const QPoint& from, const QPoint &to);
    void promotion(int);
    void initBoard();
private:
    struct MoveStruct{Men moved; Men beated; QPoint from; QPoint to; QPoint beatedPoint;};
    struct Point{QPoint point; Men man;};

    static const int N = 10;
    static const int mod = 13;
    bool prom{false};
    
    QPoint WhiteKing;
    QPoint BlackKing;
    bool WKMoved;
    bool BKMoved;

    bool canManMove(const QPoint &from, const QPoint &to);
    bool canMoveInTurn(const QPoint &from, const QPoint &to);

    bool canPawnMove(const QPoint &from, const QPoint &to);
    bool canKnightMove(const QPoint &from, const QPoint &to);
    bool canRookMove(const QPoint &from, const QPoint &to);
    bool canBishopMove(const QPoint &from, const QPoint &to);
    bool canQueenMove(const QPoint &from, const QPoint &to);
    bool canKingMove(const QPoint &from, const QPoint &to);

    bool canPawnMove(const QPoint &from);
    bool canKnightMove(const QPoint &from);
    bool canRookMove(const QPoint &from);
    bool canBishopMove(const QPoint &from);
    bool canQueenMove(const QPoint &from);
    bool canKingMove(const QPoint &from);
    bool canMove(const QPoint &from);

    bool canAchive(QPoint, bool);
    
    MoveStruct lastMove{Men::None, Men::None, {-1,-1}, {-1,-1}, {-1,-1}};
    QPoint checkingMen{-1,-1};
    Status status;
    Status statusRepl;
    bool hasCheck(bool isWhite);
    int nChecks(bool isWhite);
    void checkStatus();

    std::pair<QString, Move> movedMen;
private:
    QString menToStr(Men);
    QString statusToStr(Status);
};

#endif // BOARD_H
