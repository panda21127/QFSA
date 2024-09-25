#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QFileDialog>

#include <QDebug>

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}


void CMainWindow::on_textInput_textChanged()
{
    if (mashine.getfileState())
    {
        try
        {
            if (mashine.isGood(ui->textInput->toPlainText()))
            {
                ui->textOutput->setText("YES");
                qDebug() << "Analysis";
            }
            else
            {
                ui->textOutput->setText("NO");
                qDebug() << "No Analysis";
            }
        }
        catch (const char* exeption)
        {
            ui->textOutput->setText(exeption);
            qDebug() << exeption;
        }
    }
    else
    {
        ui->textOutput->setText("NO FILE");
    }
}


void CMainWindow::on_btnLoad_clicked()
{
    QString fn = QFileDialog::getOpenFileName(nullptr, tr("Open template"), QString(), tr("Template (*.txt)"));

    try
    {
        mashine.readFile(fn);

        mashine.determineGraph(mashine.isDeterminate());
    }
    catch (const char* exeption)
    {
        ui->textFileName->setText(exeption);
        ui->textOutput->setText(exeption);
        qDebug() << exeption;
    }

    ui->textFileName->setText(fn);

    on_textInput_textChanged();
}

