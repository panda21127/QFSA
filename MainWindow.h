#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>

#include <StateMashine.h>

QT_BEGIN_NAMESPACE
namespace Ui { class CMainWindow; }
QT_END_NAMESPACE

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private slots:
    void on_textInput_textChanged();

    void on_btnLoad_clicked();

private:
    Ui::CMainWindow *ui;

    CStateMashine mashine;
};
#endif // CMAINWINDOW_H
