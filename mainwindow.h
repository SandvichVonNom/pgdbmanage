#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Copy_Btn_ServerAdd_clicked();

private:
    Ui::MainWindow *ui;
    void loadServerList();
};

#endif // MAINWINDOW_H
