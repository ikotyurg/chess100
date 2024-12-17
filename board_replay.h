#ifndef BOARD_REPLAY_H
#define BOARD_REPLAY_H

#include <QObject>
#include <QPoint>
#include <QVector>
#include <tuple>
#include "men.h"
#include "status.h"

class BoardReplay : public QObject
{
    Q_OBJECT
public:
    explicit BoardReplay(QObject *parent = nullptr);

    struct Move{
        int32_t cell_from;
        int32_t cell_to;
        int32_t cell_add1;
        int32_t cell_add2;
        int32_t status;
    };
private:
    QVector<Men> board;
    QVector<Move> moves;
    Status status;
    bool turn;
    int nMove;
public slots:
    void initBoard(QVector<Move> moves);
    void move(int nMove);
signals:
    void moved(QVector <Men> board, int status, bool turn);
};


#endif // BOARD_REPLAY_H
