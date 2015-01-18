#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QFile>
#include <QListWidget>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include <string>

QFile FileServers("/home/box/Projects/pgdbmanage/servers.txt");

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
    QStringList ServerList;

    FileServers.open(QIODevice::ReadWrite);
    while (!FileServers.atEnd()) {
        QByteArray line = FileServers.readLine();
        ServerList.append(line.split('\n').first());
    }
    FileServers.close();

    qDebug() << ServerList;

    ui->Copy_list_Src->clear();
    ui->Copy_list_Src->addItems(ServerList);
    ui->Copy_list_Dest->clear();
    ui->Copy_list_Dest->addItems(ServerList);
    ui->Backup_list_Src->clear();
    ui->Backup_list_Src->addItems(ServerList);
    ui->Restore_list_Dest->clear();
    ui->Restore_list_Dest->addItems(ServerList);
}



void MainWindow::on_Copy_Btn_ServerAdd_clicked()
{
    QString NewServer = ui->Copy_Line_ServerAdd->text(); // Pulls text from the Copy_Line_ServerAdd element
    if (FileServers.open(QFile::ReadWrite | QIODevice::Append)) { // Should be abstracted, going to have similar code >= 4 times
        QTextStream out(&FileServers);
        out << endl << NewServer;
    }
    FileServers.close();
    MainWindow::loadServerList();
}
