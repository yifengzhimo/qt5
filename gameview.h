#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QKeyEvent>

namespace Ui {
class GameView;
}

class GameView : public QWidget
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = 0);
    ~GameView();

    void initView();
    bool generateNumber();

    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveUp();
    bool canMoveDown();

    bool noBlockHorizontal(int row, int col1, int col2);
    bool noBlockVertical(int col, int row1, int row2);
    bool noSpace();
    bool noMove();
    bool isGameOver();

    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    void gameOver();

    void updateView();

    void keyPressEvent(QKeyEvent* event);

public slots:
    void slotNewGame();

private:
    Ui::GameView *ui;

    int array[4][4] = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };

    QLabel* cells[4][4];

    int score = 0;
};

#endif // GAMEVIEW_H
