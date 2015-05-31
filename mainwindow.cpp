#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(400,500);
    this->setMinimumSize(400,500);

    score = 0;
    win = 8192;
    max = 0;
    move = 0;

    QLabel* temp[16] = {ui->label01,ui->label02,ui->label03,ui->label04,ui->label05,ui->label06,ui->label07,ui->label08,ui->label09,ui->label10,ui->label11,ui->label12,ui->label13,ui->label14,ui->label15,ui->label16};
    for( int i=0 ; i<16 ; i++ ){
        Qgrid[i] = temp[i];
    }
    for( int i=0 ; i<4 ; i++ ){
        for( int j=0 ; j<4 ; j++ ){
            mapArray[4*i+j] = &grid[i][j];
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if( event->key()==Qt::Key_Right )
    {
        //MainWindow::backupGrid();
        MainWindow::right();
        MainWindow::showWindow();
        MainWindow::findMax();
        if( MainWindow::endCheck()==1 ){
            MainWindow::winDialog();
        }
        else if( MainWindow::endCheck()==2 ){
            MainWindow::loseDialog();
        }
        else{
            MainWindow::spawn();
        }
    }
    if( event->key()==Qt::Key_Left )
    {
        //MainWindow::backupGrid();
        MainWindow::left();
        MainWindow::showWindow();
        MainWindow::findMax();
        if( MainWindow::endCheck()==1 ){
            MainWindow::winDialog();
        }
        else if( MainWindow::endCheck()==2 ){
            MainWindow::loseDialog();
        }
        else{
            MainWindow::spawn();
        }
    }
    if( event->key()==Qt::Key_Up )
    {
        //MainWindow::backupGrid();
        MainWindow::up();
        MainWindow::showWindow();
        MainWindow::findMax();
        if( MainWindow::endCheck()==1 ){
            MainWindow::winDialog();
        }
        else if( MainWindow::endCheck()==2 ){
            MainWindow::loseDialog();
        }
        else{
            MainWindow::spawn();
        }
    }
    if( event->key()==Qt::Key_Down )
    {
        //MainWindow::backupGrid();
        MainWindow::down();
        MainWindow::showWindow();
        MainWindow::findMax();
        if( MainWindow::endCheck()==1 ){
            MainWindow::winDialog();
        }
        else if( MainWindow::endCheck()==2 ){
            MainWindow::loseDialog();
        }
        else{
            MainWindow::spawn();
        }
    }
}

void MainWindow::showWindow(){
    for( int i=0 ; i<16 ; i++ ){
        if( *mapArray[i]==0 )
            Qgrid[i]->setPixmap(QPixmap(""));
        if( *mapArray[i]==2 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/2.png"));
        if( *mapArray[i]==4 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/4.png"));
        if( *mapArray[i]==8 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/8.png"));
        if( *mapArray[i]==16 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/16.png"));
        if( *mapArray[i]==32 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/32.png"));
        if( *mapArray[i]==64 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/64.png"));
        if( *mapArray[i]==128 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/128.png"));
        if( *mapArray[i]==256 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/256.png"));
        if( *mapArray[i]==512 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/512.png"));
        if( *mapArray[i]==1024 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/1024.png"));
        if( *mapArray[i]==2048 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/2048.png"));
        if( *mapArray[i]==4096 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/4096.png"));
        if( *mapArray[i]==8192 )
            Qgrid[i]->setPixmap(QPixmap(":/icon/8192.png"));
    }
    ui->currentScore->display(score);
    if( score>best ){
        best = score;
        ui->bestScore->display(best);
    }
}

int MainWindow::randomInt(int x)
{
    int index;
    index = rand()%x + 0;
    return index;
}

void MainWindow::spin(){//clockwise
    int temp[4][4];
    for( int i=0 ; i<4 ; i++ ){
        for( int j=0 ; j<4 ; j++ ){
            temp[i][j] = grid[3-j][i];
        }
    }
    for( int i=0 ; i<4 ; i++ ){
        for( int j=0 ; j<4 ; j++ ){
            grid[i][j] = temp[i][j];
        }
    }
}

void MainWindow::right(){
    int bound;
    move = 0;
    for( int i=0 ; i<4 ; i++ ){
        bound = 4;
        for( int j=2 ; j>=0 ; j-- ){
            if( grid[i][j]!=0 ){
                for( int k=j+1 ; k<bound ; k++ ){
                    if( grid[i][k]!=0 ){
                        if( grid[i][j]==grid[i][k] ){
                            grid[i][j] = 0;
                            grid[i][k] *= 2;
                            score += grid[i][k];
                            move = 1;
                            bound = k;
                            for( int m=3 ; m>k ; m-- ){
                                if( grid[i][m]==0 ){
                                    grid[i][m] = grid[i][k];
                                    grid[i][k] = 0;
                                    bound = m;
                                    break;
                                }
                            }
                        }
                        else{
                            if( k!=j+1 ){
                                grid[i][k-1] = grid[i][j];
                                grid[i][j] = 0;
                                move = 1;
                            }
                            break;
                        }
                    }
                    else if( k==bound-1 ){
                        grid[i][k] = grid[i][j];
                        grid[i][j] = 0;
                        move = 1;
                    }
                }
            }
        }
    }
}

void MainWindow::left(){
    MainWindow::spin();
    MainWindow::spin();
    MainWindow::right();
    MainWindow::spin();
    MainWindow::spin();
}

void MainWindow::up(){
    MainWindow::spin();
    MainWindow::right();
    MainWindow::spin();
    MainWindow::spin();
    MainWindow::spin();
}

void MainWindow::down(){
    MainWindow::spin();
    MainWindow::spin();
    MainWindow::spin();
    MainWindow::right();
    MainWindow::spin();
}

int MainWindow::endCheck()
{
    if( max==win ){
        return 1;//game win
    }

    int zero = 0;
    for( int i=0 ; i<4 ; i++ ){
        for( int j=0 ; j<4 ; j++ ){
            if( grid[i][j]==0 ){
                zero = 1;
                return 0;//game going on
            }
        }
    }
    if( zero==0 ){
        for( int i=0 ; i<4 ; i++ ){
            for( int j=0 ; j<3 ; j++ ){
                if( grid[i][j]==grid[i][j+1] ){
                    return 0;
                }
            }
        }
        for( int i=0 ; i<4 ; i++ ){
            for( int j=0 ; j<3 ; j++ ){
                if( grid[j][i]==grid[j+1][i] ){
                    return 0;
                }
            }
        }
    }
    return 2;//game loss
}

void MainWindow::startGrid()
{
    int i,j,k,l;
    score = 0;
    max = 0;
    for( i=0;i<4;i++ )
        for( j=0;j<4;j++ )
            grid[i][j] = 0;
    i = randomInt(4);
    j = randomInt(4);
    grid[i][j] = 2;
    do{
        k = randomInt(4);
        l = randomInt(4);
    }while( k==i && l==j);
    grid[k][l] = 2;
}

void MainWindow::backupGrid()
{
    for( int i=0 ; i<4 ; i++ ){
        for( int j=0 ; j<4 ; j++ ){
            bgrid[i][j] = grid[i][j];
            //std::cout << bgrid[i][j];
            //if((j+1)%4==0) std::cout<<std::endl;
        }
        //if((i+1)%4==0) std::cout<<std::endl;
    }
}

void MainWindow::spawn()
{
    if( move==1 ){
        int i,j,k;
        int overTime = 0;
        do{
            i = randomInt(4);
            j = randomInt(4);
            overTime++;
            if( overTime>200 ){
                for( int i=0 ; i<4 ; i++ ){
                    for( int j=0 ; j<4 ; j++ ){
                        if( grid[i][j]==0 ){
                            grid[i][j] = 2;
                        }
                    }
                }
            }
        }while( grid[i][j]!=0 );
        k = randomInt(100);
        if( k<15 )
            grid[i][j] = 4;
        else
            grid[i][j] = 2;
    }
}

void MainWindow::findMax()
{
    for( int i=0 ; i<4 ; i++ )
        for( int j=0 ; j<4 ; j++ )
            if( grid[i][j]>max )
                max = grid[i][j];
}

int MainWindow::checkMove()
{
    int k=0;
    for( int i=0 ; i<4 ; i++ ){
        for( int j=0 ; j<4 ; j++ ){
            if( bgrid[i][j]!=grid[i][j] ){
                k = 1;
                break;
            }
        }
    }
    return k;
}

void MainWindow::winDialog(){
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(0, "", "<font size='8' color='red'>&nbsp;&nbsp;&nbsp;WIN</font> <br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Play Again ?",
                                QMessageBox::Yes|QMessageBox::No);
  if( reply==QMessageBox::Yes ){
    MainWindow::startGrid();
    MainWindow::showWindow();
  }
  else{
    exit(0);
  }
}

void MainWindow::loseDialog(){
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(0, "", "<font size='8' color='blue'>&nbsp;&nbsp;LOSE</font> <br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Try Again ?",
                                QMessageBox::Yes|QMessageBox::No);
  if( reply==QMessageBox::Yes ){
    MainWindow::startGrid();
    MainWindow::showWindow();
  }
  else{
    exit(0);
  }
}

void MainWindow::on_NewGameButton_clicked()
{
    MainWindow::startGrid();
    MainWindow::showWindow();
}

void MainWindow::on_HelpButton_clicked()
{
    QMessageBox::about(NULL, "About", "<font size ='4'>1. Use arrow keys to move the tiles.<br>2. Two same tiles merge into one.<br> 3. Collect as much colors as possible.<br>4. Good Luck & Have Fun !</font>");
}
