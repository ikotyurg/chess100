#include "logic.h"


Logic::Logic(QObject *parent) : QObject(parent){
    // connect with db
    connect(&db , SIGNAL(sendGames(QStringList)), &mw, SLOT(getGames(QStringList)));
    connect(&db , SIGNAL(sendMoves(QStringList)), &mw, SLOT(getMoves(QStringList)));
    connect(&db , SIGNAL(sendMoves(QVector<Move>)),
            &br, SLOT(initBoard(QVector<Move>)));
    connect(&bg , SIGNAL(sendLastMove(const std::pair<QString, Move>&)),
            &db, SLOT(getLastMove(const std::pair<QString, Move>&)));
    connect(&mw , SIGNAL(newGame()), &db, SLOT(clear()));
    connect(&mw , SIGNAL(saveGame(QString)), &db, SLOT(store(QString)));
    connect(&mw , SIGNAL(loadGame(QString)), &db, SLOT(loadGame(QString)));
    connect(&mw , SIGNAL(loadGames()), &db, SLOT(sendGames()));

    // connect business logic with its representation (game)
    connect(&bg , SIGNAL(moved(QVector <Men>, int, bool)),
            mw.board, SLOT(setBoard(QVector <Men>, int, bool)));
    connect(&bg , SIGNAL(promotion(bool)), &mw, SIGNAL(promotion(bool)));
    connect(mw.board , SIGNAL(sendMove(const QPoint, const QPoint)),
            &bg, SLOT(move(const QPoint, const QPoint)));
    connect(&mw , SIGNAL(promotion(int)),
            &bg, SLOT(promotion(int)));
    connect(&mw , SIGNAL(newGame()),
            &bg, SLOT(initBoard()));

    // connect business logic with its representation (replay)
    connect(&mw, SIGNAL(selectedMove(int)), &br, SLOT(move(int)));
    connect(&bg, SIGNAL(moved(QVector <Men>, int, bool)),
                        mw.board, SLOT(setBoard(QVector <Men>, int, bool)));
    bg.initBoard();
}
