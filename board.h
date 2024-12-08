﻿#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QPoint>
#include <QVector>
#include <tuple>
#include "gamewindow.h"
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

private:
    bool turn;
    Men **fullBoard; // to check checks he-he 12*12
    Men **board; // just a part of fullBoard 10*10

signals:
    void moved(int *const *const board, int status, bool turn);
    void promotion(bool);
    void message(QString msg);
    void sendLastMove(const std::pair<QString, Move>& move);
    void rotatedBoard(int *const *const board, int status, bool turn);
public slots:
    void move(const QPoint& from, const QPoint &to);
    void promotion(int);
    void initBoard();
    void rotated();
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
    bool hasCheck(bool isWhite);
    int nChecks(bool isWhite);
    void checkStatus();
    void rotateBoard(Men *const *const board);

    std::pair<QString, Move> movedMen;
private:
    QString menToStr(Men);
    QString statusToStr(Status);
};

#endif // BOARD_H
