#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"
#include "status.h"
#include "qdebug.h"
#include <QStringListModel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    board = new BoardWidget(ui->chessboard_frame);
    auto geom = board->geometry();
    geom.setX(0); geom.setY(0);
    board->setGeometry(geom);
    promDialog.setModal(true);
    saveGameDialog.setModal(true);
    connect(this, SIGNAL(promotion(bool)), &promDialog, SLOT(execute(bool)));
    connect(&promDialog, SIGNAL(sendResult(int)),  this, SIGNAL(promotion(int)));
    connect(board, SIGNAL(sendStatus(int)), this, SLOT(setStatus(int)));
    connect(board, SIGNAL(sendTurn(bool)),   this, SLOT(setTurn(bool)));
    connect(ui->newgame, SIGNAL(clicked(bool)), this, SIGNAL(newGame()));
    connect(&saveGameDialog, SIGNAL(save(QString)),  this, SIGNAL(saveGame(QString)));
    connect(ui->savegame, SIGNAL(clicked(bool)), &saveGameDialog, SLOT(exec()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStatus(int status)
{
    switch (Status(status)) {
            case Status::Play:        ui->status->setText(QString("Play"));        break;
            case Status::Mate:        ui->status->setText(QString("Mate"));        break;
            case Status::Check:       ui->status->setText(QString("Check"));       break;
            case Status::DoubleCheck: ui->status->setText(QString("DoubleCheck")); break;
            case Status::StaleMate:   ui->status->setText(QString("StaleMate"));   break;
            case Status::Draw:        ui->status->setText(QString("Draw"));        break;
            case Status::Promotion:                                                break;
        }
}

void MainWindow::setTurn(bool turn)
{
    {
       if (turn) ui->turn->setText(QString("White"));
       else      ui->turn->setText(QString("Black"));
    }
}

void MainWindow::on_exit_clicked()
{
    close();
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    qDebug() << "INDEX: " << index.row();
       emit selectedMove(index.row());
}

void MainWindow::getMoves(QStringList moves)
{
    QStringListModel *model = new QStringListModel();
        model->setStringList(moves);
        ui->listMoves->setModel(model);
}

void MainWindow::on_rotateButton_clicked()
{
    board->rotateBoardLiterals();
    myBoard->rotateBoard();
}


void MainWindow::on_replay_clicked()
{
    this->hide();
    rlgw.load();
    rlgw.exec();
    this->show();
}

