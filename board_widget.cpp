#include "board_widget.h"
#include <QMouseEvent>
#include <QCursor>
#include "board.h"

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent) // turn == true - white
{  
    this->setFixedSize(windowSize, windowSize);
    cells = new QLabel*[nCells];
    for (auto i = 0; i < nCells; ++i)
        cells[i] = new QLabel[nCells];
    for (int i = 0; i < nCells; ++i){
        for (int j = (1 + i)%2 ; j < nCells; j += 2)
            cells[i][j].setStyleSheet("QLabel { background-color : sienna;}");
        for (int j = (i)%2 ; j < nCells; j += 2)
            cells[i][j].setStyleSheet("QLabel { background-color : white;}");
    }
    for (int i = 0; i < nCells; ++i){
        for (int j = 0; j < nCells; ++j){
            cells[i][j].setParent(this);
            cells[i][j].setGeometry(i * cellSize, j * cellSize, cellSize, cellSize);
            //cells[i][j].setPixmap(QPixmap(getManPicPath(defMenPosition[i][j])));
        }
    }

    setBoard();
}

void BoardWidget::mousePressEvent(QMouseEvent *event){
    QPoint to{event->x()/cellSize, event->y()/cellSize};
    if (moveByClick){
        if (movePoint != to){
            emit sendMove(movePoint, to);
        }
    }
    else{
        if(to.x() < 10 && to.y() < 10 && matrix[to.x()][to.y()] != 0){
            movePoint.setX(to.x());
            movePoint.setY(to.y());
            // Создаем QPixmap
            QPixmap pixmap(getManPicPath(matrix[to.x()][to.y()]));

            // Изменяем размер пиксмапа
            QPixmap scaledPixmap = pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio);

            // Устанавливаем курсор с использованием объекта QCursor
            this->setCursor(QCursor(scaledPixmap));
        }

    }
}

void BoardWidget::mouseDoubleClickEvent(QMouseEvent *event){
    mousePressEvent(event);
}

void BoardWidget::rotateBoard()
{
    // int rotated[10][10];
    // // Поворот
    //    for (int i = 0; i < 10; ++i) {
    //        for (int j = 0; j < 10; ++j) {
    //            rotated[i][j] = matrix[9 - i][9 - j];
    //        }
    //    }

    //    // Копирование обратно
    //    for (int i = 0; i < 10; ++i) {
    //        for (int j = 0; j < 10; ++j) {
    //            matrix[i][j] = rotated[i][j];
    //        }
    //    }
       //setBoard(matrix, status, turn);
}

void BoardWidget::mouseReleaseEvent(QMouseEvent *event){
    if (moveByClick){
        this->setCursor(QCursor());
        moveByClick = false;
        return;
    }
    QPoint to{event->x()/cellSize, event->y()/cellSize};
    if (movePoint == to){
        if(to.x() < 10 && to.y() < 10 && matrix[to.x()][to.y()] != 0){
            moveByClick = true;
            // Создаем QPixmap
            QPixmap pixmap(getManPicPath(matrix[to.x()][to.y()]));

            // Изменяем размер пиксмапа
            QPixmap scaledPixmap = pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio);

            // Устанавливаем курсор с использованием объекта QCursor
            this->setCursor(QCursor(scaledPixmap));

        }
    }
    else{
        emit sendMove(movePoint, to);
        this->setCursor(QCursor());
    }
}

void BoardWidget::setBoard(int *const *const men, int status, bool turn){
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


QString BoardWidget::getManPicPath(int m)
{
    switch (m) {
        case 1: return QString(":/img/img/pawn-white.png");
        case 2: return QString(":/img/img/knight-white.png");
        case 3: return QString(":/img/img/bishop-white.png");
        case 4: return QString(":/img/img/rook-white.png");
        case 5: return QString(":/img/img/queen-white.png");
        case 6: return QString(":/img/img/king-white.png");

        case -1: return QString(":/img/img/pawn-black.png");
        case -2: return QString(":/img/img/knight-black.png");
        case -3: return QString(":/img/img/bishop-black.png");
        case -4: return QString(":/img/img/rook-black.png");
        case -5: return QString(":/img/img/queen-black.png");
        case -6: return QString(":/img/img/king-black.png");

        case 0:
        default: return nullptr;
    }
}
