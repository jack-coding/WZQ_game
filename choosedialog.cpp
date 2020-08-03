#include "choosedialog.h"
#include "ui_choosedialog.h"
#include "mainwindow.h"
#include <QDebug>

chooseDialog::chooseDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chooseDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("五子棋游戏--选择对战模式");
    this->setFixedSize(this->width(),this->height());
    this->m_Mode=AI;
    initLayout();
}

chooseDialog::~chooseDialog()
{
    delete ui;
}


void chooseDialog::on_AImodeBtn_clicked()
{
    this->m_Mode=AI;
    this->m_Mainwindow=new MainWindow(this->m_Mode,NULL);
    this->m_Mainwindow->show();
    this->m_Mainwindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(m_Mainwindow,SIGNAL(mainWindowClose()),this,SLOT(reshow()));
    this->hide();
}

void chooseDialog::on_HumanmodeBtn_clicked()
{
    this->m_Mode=MAN;
    this->m_Mainwindow=new MainWindow(this->m_Mode,NULL);
    this->m_Mainwindow->setAttribute(Qt::WA_DeleteOnClose);
    this->m_Mainwindow->show();
    connect(m_Mainwindow,SIGNAL(mainWindowClose()),this,SLOT(reshow()));
    this->hide();
}

void chooseDialog::reshow()
{
    this->show();
}

void chooseDialog::initLayout()
{
    ui->secondLayout->setSpacing(45);
    ui->mainvLayout->setAlignment(this,Qt::AlignHCenter);
    ui->layoutWidget->setGeometry(QRect(240, 60, 211, 241));
}
