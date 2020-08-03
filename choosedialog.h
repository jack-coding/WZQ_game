#ifndef CHOOSEDIALOG_H
#define CHOOSEDIALOG_H

#include <QWidget>
#include"gamemodel.h"

class MainWindow;

namespace Ui {
class chooseDialog;
}

class chooseDialog : public QWidget
{
    Q_OBJECT

public:
    explicit chooseDialog(QWidget *parent = nullptr);
    ~chooseDialog();
private slots:


    void on_AImodeBtn_clicked();

    void on_HumanmodeBtn_clicked();
    void reshow();
private:
    void initLayout();
    GameType m_Mode;
    MainWindow *m_Mainwindow;
    Ui::chooseDialog *ui;
};

#endif // CHOOSEDIALOG_H
