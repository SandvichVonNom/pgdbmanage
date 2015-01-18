#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QFile>
#include <QListWidget>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include <string>

QFile file_server_list("/home/box/Projects/pgdbmanage/servers.txt");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadServerList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadServerList()
{
    using namespace std; // enabled for initial debugging

    QStringList wordList;

    file_server_list.open(QIODevice::ReadWrite);
    while (!file_server_list.atEnd()) {
        cout << "Checked a line" << endl;
        QByteArray line = file_server_list.readLine();
        wordList.append(line.split('\n').first());
    }
    file_server_list.close();

    qDebug() << wordList;

    ui->Copy_list_Src->clear();
    ui->Copy_list_Src->addItems(wordList);
    ui->Copy_list_Dest->clear();
    ui->Copy_list_Dest->addItems(wordList);
    ui->Backup_list_Src->clear();
    ui->Backup_list_Src->addItems(wordList);
    ui->Restore_list_Dest->clear();
    ui->Restore_list_Dest->addItems(wordList);

    cout << "Finished boys";

}



void MainWindow::on_Copy_Btn_ServerAdd_clicked()
{
    QString sNewServer = ui->Copy_Line_ServerAdd->text();
    file_server_list.open(QIODevice::WriteOnly | QIODevice::Append);
    file_server_list.write("\n333");
    file_server_list.close();
    MainWindow::loadServerList();
}
