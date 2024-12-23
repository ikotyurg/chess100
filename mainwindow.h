#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "board.h"
#include "promotiondialog.h"
#include "savegamedialog.h"
#include "board_widget.h"
#include "replay_list_games_window.h"
#include "men.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ReplayListGamesWindow rlgw;
public:
    BoardWidget *board;

signals:
    void promotion(bool);
    void promotion(int);
    void newGame();
    void saveGame(QString);
    void selectedMove(int);

private slots:
    void setStatus(int status);
    void setTurn(bool turn);

    void on_exit_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void getMoves(QStringList);

    void on_rotateButton_clicked();

    void on_replay_clicked();

private:
    Board* myBoard; // Указатель на объект Board

private:
    PromotionDialog promDialog;
    SaveGameDialog saveGameDialog;
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
