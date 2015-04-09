#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QFile>
#include <QListWidget>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include <string>
#include <QFileDialog>
#include <tcl.h>
#include <expect_tcl.h>
#include <expect.h>

QFile fileServers("servers.txt");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::loadServerList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Updates the server lists from the txt file
void MainWindow::loadServerList()
{
    QStringList ServerList;

    if (!fileServers.exists())
    {
        if (fileServers.open(QFile::ReadWrite | QIODevice::Append)) {
            QTextStream out(&fileServers);
            out << "foo.bar";
        }
        fileServers.close();
    }

    fileServers.open(QIODevice::ReadWrite);
    while (!fileServers.atEnd()) {
        QByteArray line = fileServers.readLine();
        ServerList.append(line.split('\n').first());
    }

    fileServers.close();

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

// Uses QTextStream to append an entry to the server txt file.  Calls loadServerList() to refresh from the modified file.
void MainWindow::appendServerList(QString NewServer)
{
    if (fileServers.open(QFile::ReadWrite | QIODevice::Append)) {
        QTextStream out(&fileServers);
        if (NewServer.length() > 0)
            out << endl << NewServer;
    }
    fileServers.close();
    MainWindow::loadServerList();
}

// Pulls string from the adjacent box when the button is pressed.  Appends text to end of server txt file, then refreshes server list.
void MainWindow::on_Copy_Btn_ServerAdd_clicked()
{
    QString NewServer = ui->Copy_Line_ServerAdd->text();
    MainWindow::appendServerList(NewServer);
}


void MainWindow::on_Backup_Btn_ServerAdd_clicked()
{
    QString NewServer = ui->Backup_Line_ServerAdd->text();
    MainWindow::appendServerList(NewServer);
}

void MainWindow::on_Restore_Btn_ServerAdd_clicked()
{
    QString NewServer = ui->Restore_Line_ServerAdd->text();
    MainWindow::appendServerList(NewServer);
}

void MainWindow::on_Restore_Btn_File_clicked()
{
    QString SqlFile = QFileDialog::getOpenFileName(this,
    tr("Select SQL Backup"), "", tr("SQL files (*.sql)"));
    ui->Restore_Line_File->setText(SqlFile);
}


void MainWindow::on_Backup_Btn_RunBackup_clicked()
{
//    FILE* fd = exp_popen("ssh htpc@192.168.42.102");
//    std::string host = "myhost";
//    FILE *expect = exp_popen((char *) host.c_str());
}
