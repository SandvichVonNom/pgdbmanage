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

    void on_Backup_Btn_ServerAdd_clicked();

    void on_Restore_Btn_ServerAdd_clicked();

    void on_Restore_Btn_File_clicked();

    void on_Backup_Btn_RunBackup_clicked();

private:
    Ui::MainWindow *ui;
    void loadServerList();
    void appendServerList(QString);
};

#endif // MAINWINDOW_H
