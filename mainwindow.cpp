#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QFile>
#include <QListWidget>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include <string>

QFile qf_file_servers("/home/box/Projects/pgdbmanage/servers.txt");

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
    QStringList wordList;

    qf_file_servers.open(QIODevice::ReadWrite);
    while (!qf_file_servers.atEnd()) {
        QByteArray line = qf_file_servers.readLine();
        wordList.append(line.split('\n').first());
    }
    qf_file_servers.close();

    qDebug() << wordList;

    ui->Copy_list_Src->clear();
    ui->Copy_list_Src->addItems(wordList);
    ui->Copy_list_Dest->clear();
    ui->Copy_list_Dest->addItems(wordList);
    ui->Backup_list_Src->clear();
    ui->Backup_list_Src->addItems(wordList);
    ui->Restore_list_Dest->clear();
    ui->Restore_list_Dest->addItems(wordList);
}



void MainWindow::on_Copy_Btn_ServerAdd_clicked()
{
    QString sNewServer = ui->Copy_Line_ServerAdd->text(); // Pulls text from the Copy_Line_ServerAdd element
    if (qf_file_servers.open(QFile::ReadWrite | QIODevice::Append)) { // Should be abstracted, going to have similar code >= 4 times
        QTextStream out(&qf_file_servers);
        out << endl << sNewServer;
    }
    qf_file_servers.close();
    MainWindow::loadServerList();
}
