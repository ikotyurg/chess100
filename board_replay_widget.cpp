#include "board_replay_widget.h"
#include <QMouseEvent>
#include <QCursor>

BoardReplayWidget::BoardReplayWidget(QWidget *parent) : QWidget(parent) // turn == true - white
{
    this->setFixedSize(windowSize, windowSize);
    // Инициализация шахматной доски
    cells = new QLabel*[nCells];
    for (auto i = 0; i < nCells; ++i)
        cells[i] = new QLabel[nCells];

    for (int i = 0; i < nCells; ++i){
        for (int j = (1 + i) % 2; j < nCells; j += 2)
            cells[i][j].setStyleSheet("QLabel { background-color : sienna; }");
        for (int j = (i) % 2; j < nCells; j += 2)
            cells[i][j].setStyleSheet("QLabel { background-color : white; }");
    }
    for (int i = 0; i < nCells; ++i){
        for (int j = 0; j < nCells; ++j){
            cells[i][j].setParent(this);
            cells[i][j].setGeometry((i) * cellSize, (j) * cellSize, cellSize, cellSize); // Смещения нет
            cells[i][j].setPixmap(QPixmap(getManPicPath(defMenPosition[i][j])));
        }
    }
    // for (int i = 0; i < nCells; ++i){
    //     for (int j = 0; j < nCells; ++j){
    //         cells[i][j].setParent(this);
    //         cells[i][j].setGeometry((i + 1) * cellSize, (j + 1) * cellSize, cellSize, cellSize); // Смещение на 1 ячейку
    //         cells[i][j].setPixmap(QPixmap(getManPicPath(defMenPosition[i][j])));
    //     }
    // }
    // // Добавление строк с обозначениями вертикалей сверху
    // for (int i = 0; i < nCells; ++i) {
    //     QLabel *verticalLabel = new QLabel(vLiterals[i], this);
    //     verticalLabel->setGeometry((i + 1) * cellSize, 0, cellSize, cellSize); // Смещение вниз
    //     verticalLabel->setAlignment(Qt::AlignCenter);

    //     // Установка цвета фона для ячеек с обозначениями
    //     verticalLabel->setStyleSheet("QLabel { background-color : #b8a18a; font-size: 24px; font-weight: bold; color: darkRed; }");
    // }

    // Добавление строк с обозначениями вертикалей снизу
    for (int i = 0; i < nCells; ++i) {
        QLabel *verticalLabel = new QLabel(vLiterals[i], this);
        verticalLabel->setGeometry(i * cellSize, cellSize * nCells, cellSize, cellSize); // Смещение вниз
        verticalLabel->setAlignment(Qt::AlignCenter);

        // Установка цвета фона для ячеек с обозначениями
        verticalLabel->setStyleSheet("QLabel { background-color : #b8a18a; font-size: 24px; font-weight: bold; color: darkRed; }");
    }

    // Добавление строк с обозначениями горизонталей слева и справа
    for (int i = 0; i < nCells; ++i) {
        // QLabel *horizontalLabelLeft = new QLabel(hLiterals[i], this);
        // horizontalLabelLeft->setGeometry(0, (nCells - i) * cellSize, cellSize, cellSize); // Смещение вправо
        // horizontalLabelLeft->setAlignment(Qt::AlignCenter);
        // horizontalLabelLeft->setStyleSheet("QLabel { background-color : #b8a18a; font-size: 24px; font-weight: bold; color: darkRed; }");
        QLabel *horizontalLabelRight = new QLabel(hLiterals[i], this);
        horizontalLabelRight->setGeometry(nCells * cellSize, (nCells - i - 1) * cellSize, cellSize, cellSize); // Смещение вправо
        horizontalLabelRight->setAlignment(Qt::AlignCenter);
        horizontalLabelRight->setStyleSheet("QLabel { background-color : #b8a18a; font-size: 24px; font-weight: bold; color: darkRed; }");
    }

       setBoard();
}


void BoardReplayWidget::setBoard(int *const *const men, int status, bool turn){
    if (men){
        for (int x = 0; x < nCells; ++x)
            for (int y = 0; y < nCells; ++y)
                if (men[x][y] != matrix[x][y]){
                    matrix[x][y] = men[x][y];
                    cells[x][y].setPixmap(QPixmap(getManPicPath(matrix[x][y])).scaled(cellSize,
                                                                                      cellSize,
                                                                                      Qt::KeepAspectRatio));
                }
    } else
        for (int x = 0; x < nCells; ++x){
            for (int y = 0; y < nCells; ++y)
                if (defMenPosition[x][y] != matrix[x][y]){
                    matrix[x][y] = defMenPosition[x][y];
                    cells[x][y].setPixmap(QPixmap(getManPicPath(matrix[x][y])).scaled(cellSize,
                                                                                       cellSize,
                                                                                       Qt::KeepAspectRatio));
                }
        }
    emit sendStatus(status);
    emit sendTurn(turn);
}

QString BoardReplayWidget::getManPicPath(int m)
{
    switch (m) {
    case 1: return QString(":/img/img/pieces /pawn-white.png");
    case 2: return QString(":/img/img/pieces /knight-white.png");
    case 3: return QString(":/img/img/pieces /bishop-white.png");
    case 4: return QString(":/img/img/pieces /rook-white.png");
    case 5: return QString(":/img/img/pieces /queen-white.png");
    case 6: return QString(":/img/img/pieces /king-white.png");

    case -1: return QString(":/img/img/pieces /pawn-black.png");
    case -2: return QString(":/img/img/pieces /knight-black.png");
    case -3: return QString(":/img/img/pieces /bishop-black.png");
    case -4: return QString(":/img/img/pieces /rook-black.png");
    case -5: return QString(":/img/img/pieces /queen-black.png");
    case -6: return QString(":/img/img/pieces /king-black.png");

    case 0:
        default: return nullptr;
    }
}
