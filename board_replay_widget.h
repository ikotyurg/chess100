#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H


#include <QWidget>
#include <QLabel>


class BoardReplayWidget : public QWidget
{
    Q_OBJECT

    int windowSize = 660;
    int nCells = 10;
    int cellSize = 55;
public:
    explicit BoardReplayWidget(QWidget *parent = nullptr);
private:
    QString getManPicPath(int m);
    QVector<QString> vLiterals = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "K"};
    QVector<QString> hLiterals = {"10", "9", "8", "7", "6", "5", "4", "3", "2", "1"};

signals:
    void sendStatus(int);
    void sendTurn(bool);
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
};


#endif // BOARDWIDGET_H
