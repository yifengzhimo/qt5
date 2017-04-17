#include "gameview.h"
#include "ui_gameview.h"
#include <QTime>
#include <QMessageBox>

GameView::GameView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameView)
{
    ui->setupUi(this);

    cells[0][0] = ui->label00; cells[0][1] = ui->label01; cells[0][2] = ui->label02; cells[0][3] = ui->label03;
    cells[1][0] = ui->label10; cells[1][1] = ui->label11; cells[1][2] = ui->label12; cells[1][3] = ui->label13;
    cells[2][0] = ui->label20; cells[2][1] = ui->label21; cells[2][2] = ui->label22; cells[2][3] = ui->label23;
    cells[3][0] = ui->label30; cells[3][1] = ui->label31; cells[3][2] = ui->label32; cells[3][3] = ui->label33;

    initView();
    connect(ui->newBtn, SIGNAL(clicked(bool)), this, SLOT(slotNewGame()));
    setFocus();
}

GameView::~GameView()
{
    delete ui;
}

void GameView::initView()
{
    for(int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            array[i][j] = 0;


    generateNumber();
    generateNumber();
    updateView();
}

bool GameView::generateNumber()
{
    if (noSpace())
        return false;

    qsrand(QTime::currentTime().msec());
    int n = qrand()%10;
    int i = qrand()%4;
    int j = qrand()%4;

    if (n >= 5) n=4;
    else n = 2;

    while (1)
    {
        if (array[i][j] == 0)
            break;
        i = qrand()%4;
        j = qrand()%4;
    }

    array[i][j] = n;
    return true;
}

bool GameView::canMoveLeft()
{
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            if (array[i][j] != 0)
                if (array[i][j-1]==0 || array[i][j-1]==array[i][j])
                    return true;
    return false;
}

bool GameView::canMoveRight()
{
    for(int i = 0;i<4;i++)
        for(int j = 0;j<4;j++)
            if( array[i][j] !=0 )
                if( array[i][j+1] == 0 || array[i][j+1] == array[i][j])
                    return true;

    return false;
}

bool GameView::canMoveUp()
{
    for(int i = 0;i<4;i++)
        for(int j = 0;j<4;j++)
            if( array[j][i] !=0 )
                if( array[j][i-1] == 0 || array[j][i-1] == array[j][i])
                    return true;

    return false;
}

bool GameView::canMoveDown()
{
    for(int j = 0;j<4;j++)
        for(int i = 0;i<4;i++)
            if( array[i][j] !=0 )
                if( array[i][j+1] == 0 || array[i][j+1] == array[i][j])
                    return true;

    return false;
}

bool GameView::noBlockHorizontal(int row, int col1, int col2)
{
    for (int i=col1+1; i<col2; i++)
        if (array[row][i] != 0)
            return false;
    return true;
}

bool GameView::noBlockVertical(int col, int row1, int row2)
{
    for (int i=row1+1; i<row2; i++)
        if (array[i][col] != 0)
            return false;
    return true;
}

bool GameView::noSpace()
{
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++)
        {
            if (array[i][j] == 0)
                return false;
        }
    }

    return true;
}

bool GameView::noMove()
{
    if (canMoveDown() || canMoveUp()
            || canMoveLeft() || canMoveRight())
        return false;
    return true;
}

bool GameView::isGameOver()
{
    if (noSpace() && noMove())
        gameOver();
}

bool GameView::moveLeft()
{
    if (!canMoveLeft())
        return false;

    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            if (array[i][j] != 0)
            {
                for (int k=0; k<j; k++)
                {
                    if (array[i][k] == 0 && noBlockHorizontal(i,k,j))
                    {
                        array[i][k] = array[i][j];
                        array[i][j] = 0;
                        continue;
                    }

                    else if (array[i][k] == array[i][j] && noBlockHorizontal(i,k,j))
                    {
                        array[i][k] += array[i][j];
                        score += array[i][j];
                        array[i][j] = 0;

                        continue;
                    }
                }
            }
    updateView();
    return true;
}

bool GameView::moveRight()
{
    if (!canMoveRight())
        return false;

    for (int i=0; i<4; i++)
        for (int j=2; j>=0; j--)
            if (array[i][j] != 0)
            {
                for (int k=3; k>j; k--)
                {
                    if (array[i][k] == 0 && noBlockHorizontal(i,j,k))
                    {
                        array[i][k] = array[i][j];
                        array[i][j] = 0;
                        continue;
                    }

                    else if (array[i][k] == array[i][j] && noBlockHorizontal(i,j,k))
                    {
                        array[i][k] += array[i][j];
                        score += array[i][j];
                        array[i][j] = 0;

                        continue;
                    }
                }
            }
    updateView();
    return true;
}

bool GameView::moveUp()
{
    if (!canMoveUp())
        return false;

    for(int j = 0;j<4;j++)
        for(int i = 1;i<4;i++)
            if (array[i][j] != 0)
            {
                for (int k=0; k<i; k++)
                {
                    if (array[k][j] == 0 && noBlockVertical(j, k, i))
                    {
                        array[k][j] = array[i][j];
                        array[i][j] = 0;
                        continue;
                    }

                    else if (array[k][j] == array[i][j] && noBlockVertical(j, k, i))
                    {
                        array[k][j] += array[i][j];
                        score += array[i][j];
                        array[i][j] = 0;

                        continue;
                    }
                }
            }
    updateView();
    return true;
}

bool GameView::moveDown()
{
    if (!canMoveDown())
        return false;

    for(int j = 0;j<4;j++)
        for(int i = 2;i>=0;i--)
            if (array[i][j] != 0)
            {
                for (int k=3; k>i; k--)
                {
                    if (array[k][j] == 0 && noBlockVertical(j, i, k))
                    {
                        array[k][j] = array[i][j];
                        array[i][j] = 0;
                        continue;
                    }

                    else if (array[k][j] == array[i][j] && noBlockVertical(j, i, k))
                    {
                        array[k][j] += array[i][j];
                        score += array[i][j];
                        array[i][j] = 0;

                        continue;
                    }
                }
            }

    updateView();
    return true;
}

void GameView::gameOver()
{
    QMessageBox::information(this, "A Message!", "Game Over!", QMessageBox::Yes);
}

void GameView::updateView()
{
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            if (array[i][j] == 0)
                cells[i][j]->setText(" ");
            else cells[i][j]->setText(QString("%1").arg(array[i][j]));
        }
    }

    ui->labelScore->setText(QString("%1").arg(score));

    update();
    setFocus();
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    int keyValue = event->key();

    switch (keyValue) {
    case Qt::Key_Up:
        if (moveUp())
        {
            generateNumber();
            isGameOver();
            updateView();
        }
        break;
    case Qt::Key_Down:
        if (moveDown())
        {
            generateNumber();
            isGameOver();
            updateView();
        }
        break;
    case Qt::Key_Left:
        if (moveLeft())
        {
            generateNumber();
            isGameOver();
            updateView();
        }
        break;
    case Qt::Key_Right:
        if (moveRight())
        {
            generateNumber();
            isGameOver();
            updateView();
        }
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void GameView::slotNewGame()
{
    initView();
    setFocus();
}
