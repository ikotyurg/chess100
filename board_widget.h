﻿#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QLabel>


class BoardWidget : public QWidget
{
    Q_OBJECT

    QPoint movePoint;
    int windowSize = 500;
    int nCells = 10;
    int cellSize = 50;
public:
    explicit BoardWidget(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private:
    QString getManPicPath(int m);
signals:
    void sendStatus(int);
    void sendTurn(bool);
    void sendMove(const QPoint &from, const QPoint &to);
public slots:
    void setBoard(int *const *const men = nullptr, int status = 0, bool turn = true);
public:
    QLabel **cells;
    int matrix[10][10]{
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };

    private:
        int defMenPosition[10][10]{
            {-4, -1,  0, 0, 0, 0, 0, 0,  1,  4},
            {-2, -1,  0, 0, 0, 0, 0, 0,  1,  2},
            {-2, -1,  0, 0, 0, 0, 0, 0,  1,  2},
            {-3, -1,  0, 0, 0, 0, 0, 0,  1,  3},
            {-5, -1,  0, 0, 0, 0, 0, 0,  1,  5},
            {-6, -1,  0, 0, 0, 0, 0, 0,  1,  6},
            {-3, -1,  0, 0, 0, 0, 0, 0,  1,  3},
            {-2, -1,  0, 0, 0, 0, 0, 0,  1,  2},
            {-2, -1,  0, 0, 0, 0, 0, 0,  1,  2},
            {-4, -1,  0, 0, 0, 0, 0, 0,  1,  4}
        };
        int defMenRotatedPosition[10][10]{
            {4, 1,  0, 0, 0, 0, 0, 0,  -1,  -4},
            {2, 1,  0, 0, 0, 0, 0, 0,  -1,  -2},
            {2, 1,  0, 0, 0, 0, 0, 0,  -1,  -2},
            {3, 1,  0, 0, 0, 0, 0, 0,  -1,  -3},
            {5, 1,  0, 0, 0, 0, 0, 0,  -1,  -5},
            {6, 1,  0, 0, 0, 0, 0, 0,  -1,  -6},
            {3, 1,  0, 0, 0, 0, 0, 0,  -1,  -3},
            {2, 1,  0, 0, 0, 0, 0, 0,  -1,  -2},
            {2, 1,  0, 0, 0, 0, 0, 0,  -1,  -2},
            {4, 1,  0, 0, 0, 0, 0, 0,  -1,  -4}
        };
    bool moveByClick{true};
};



#endif // CHESSBOARD_H
