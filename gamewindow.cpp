#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "status.h"
#include <QStringListModel>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
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
    connect(ui->flipBoard, SIGNAL(clicked(bool)), board, SLOT(flipBoard()));
}

GameWindow::~GameWindow()
{
    delete ui;
    delete board;
}

void GameWindow::getMoves(QStringList moves)
{
    QStringListModel *model = new QStringListModel();
    model->setStringList(moves);
    ui->listView->setModel(model);
}

void GameWindow::setStatus(int status){
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

void GameWindow::setTurn(bool turn){
    if (turn) ui->turn->setText(QString("White"));
    else      ui->turn->setText(QString("Black"));
}

void GameWindow::on_exit_clicked()
{
    this->close();
}

void GameWindow::on_listView_clicked(const QModelIndex &index)
{
    qDebug() << "INDEX: " << index.row();
    emit selectedMove(index.row());
}

