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

    bool isGood(QString str);

private:
    QMap<QString, QMap<QString, QVector<QString>>> m_mapTransitions;
    QMap<QString, QMap<QString, QString>> determinateGraph;
};

#endif // CSTATEMASHINE_H
