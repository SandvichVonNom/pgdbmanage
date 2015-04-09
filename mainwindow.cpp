#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QFile>
#include <QListWidget>
#include <QStringList>
#include <QDebug>
#include <iostream>
using std::cout;
using std::endl;

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

    // This section taken from "http://stackoverflow.com/questions/13705869/why-do-i-get-a-segmentation-fault-in-my-simple-c-program-using-libexpect-so" for learning purposes, will be changing almost everything once I better understand libexpect

    enum{FOUNDSEARCH, PROMPT};
    /* initialise expect and tcl */
    Tcl_Interp *interp = Tcl_CreateInterp();

    if(Tcl_Init(interp) == TCL_ERROR)
    {
        cout << "TCL failed to initialize." << endl;
    }

    if(Expect_Init(interp) == TCL_ERROR)
    {
        cout << "Expect failed to initialize." << endl;
    }

    /* end of intialisation procedure */

    //open a shell with a pipe
    char shellType[] = "sh";
    FILE* fp = exp_popen(shellType);

    //should we exit from the loop which is studying sh output
    bool shouldBreak = false;
    //did we find the pwd
    bool foundSearch = false;
    //does it look like expect is working
    bool expectWorking = false;
    //did we receive a prompt...therefore we should send a command
    bool receivedPrompt = false;

    while(shouldBreak == false)
    {
        switch(exp_fexpectl(fp,
            exp_glob, "/tools/test*", FOUNDSEARCH,  //different
            exp_glob,"# ", PROMPT, //cases are shown here
            exp_end))  //that the expect loop could encounter
        {
            case FOUNDSEARCH:
                foundSearch = true;
                break;
            case PROMPT:
                if (receivedPrompt)
                {
                    shouldBreak = true;
                    expectWorking = true;
                }
                else
                {
                    receivedPrompt = true;
                    fprintf(fp, "%s\r", "pwd");
                }
                break;
            case EXP_TIMEOUT:
                shouldBreak = true;
                break;
            case EXP_EOF:
                shouldBreak = true;
                break;
        }

          //cout << "exp_match : " << exp_match << endl;
    }

    cout << endl;
    if (foundSearch)
    {
        cout << "Expect found output of pwd" << endl;
    }
    else
    {
        cout << "Expect failed to find output of pwd" << endl;
    }

    if(expectWorking)
    {
        cout << "The expect interface is working" << endl;
    }
    else
    {
        cout << "The expect interface is not working" << endl;
    }

    cout << "The test program successfully reached the end" << endl;
}
