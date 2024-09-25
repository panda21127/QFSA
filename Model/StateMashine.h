#ifndef CSTATEMASHINE_H
#define CSTATEMASHINE_H

#include <QString>

#include <QMap>

class CStateMashine
{
public:
    CStateMashine();

    void readFile(QString filename);

    void determineGraph(bool isDeteminated);
    bool isDeterminate();

    bool getfileState();

    bool isGood(QString str);

private:
    QMap<QString, QMap<QString, QVector<QString>>> m_mapTransitions;
    QMap<QString, QMap<QString, QString>> m_determinateGraph;

    bool m_fileSetted = false;
};

#endif // CSTATEMASHINE_H
