#include "MainWindow.h"

#include <QApplication>

#include <StateMashine.h>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMainWindow w;
    //w.show();

    QVector <QString> arrayStr =
    {
        "a",
        "\\",
        "/a,;",
        "/a,8",
        "acf",
        "ae",
        "ab",
    };

    CStateMashine mashine;

    try
    {
        mashine.readFile("D:/Qt/Comp_2/Recources/Graphs/var3_nd.txt");

        mashine.determineGraph(mashine.isDeterminate());

        for (QString str : arrayStr)
        {
            if (mashine.isGood(str))
            {
                qDebug() << "Analysis";
            }
            else
            {
                qDebug() << "No Analysis";
            }
        }
    }
    catch (const char* exeption)
    {
        qDebug() << exeption;
    }

    return a.exec();
}
