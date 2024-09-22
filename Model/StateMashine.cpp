#include "StateMashine.h"

#include <QVector>
#include <QDir>

#include <QDebug>

#include <QtMath>

CStateMashine::CStateMashine()
{

}

void CStateMashine::readFile(QString filename)
{
    QFile file(filename);

    QVector <QString> array;

    if (file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          array.push_back(line);
       }
       file.close();
    }
    else
    {
        throw "No File";
        return;
    }

    for (const QString &str : array)
    {
        QString word = "";
        QString key;
        QString symbol;
        int i = 0;

        while (str[i] != ",")
        {
            word += str[i];
            i++;
        }

        i++;

        key = word;
        symbol = str[i];

        i += 2;

        word = "";

        while (i < str.size())
        {
            word += str[i];
            i++;
        }

        QVector<QString> tempArray = m_mapTransitions[key][symbol];
        tempArray.push_back(word);

        m_mapTransitions[key].insert(symbol, tempArray);

        qDebug() << str;
    }

}

void CStateMashine::determineGraph(bool isDeteminated)
{
    if (isDeteminated)
    {
        for (QString key : m_mapTransitions.keys())
        {
            for (QString symbol : m_mapTransitions[key].keys())
            {
                determinateGraph[key][symbol] = m_mapTransitions[key][symbol][0];
            }
        }

        return;
    }

    QMap<QString, bool> tempMap;

    for (QString key : m_mapTransitions.keys())
    {
        for (QString symbols : m_mapTransitions[key].keys())
        {
            tempMap[key] = true;
            for (QString value : m_mapTransitions[key][symbols])
            {
                tempMap[value] = true;
            }
        }
    }

    QVector<QVector<QString>> newStates;
    int W = tempMap.keys().count();
    int N = pow(2, W);

    for (int i = 0; i < N; i++)
    {
        QVector<QString> tempArray;

        for (int j = 0; j < W; j++)
        {
            if ( i & (1 << j) )
            {
                tempArray.push_back(tempMap.keys()[j]);
            }
        }

        newStates.push_back(tempArray);
    }

    //QMap<QVector<QString>, QMap<QString, QVector<QString>>> newTransaction;
    QMap<QString, QMap<QString, QMap<QString, bool>>> newTransactions;

    for (QVector<QString> states : newStates)
    {
        QString key = "";

        for (QString state: states)
        {
            key += state;
        }


        for (QString state: states)
        {
            //QString value = "";

            for (QString symbols: m_mapTransitions[state].keys())
            {
                m_mapTransitions[state][symbols];

                for (QString finalState: m_mapTransitions[state][symbols])
                {
                    //value += finalState;
                    newTransactions[key][symbols][finalState] = true;
                }

                //newTransactions[key].insert(symbols,value);
                //newTransaction[states].insert(symbols, m_mapTransitions[state][symbols]);
            }
        }
    }

    for (QString key : newTransactions.keys())
    {
        for (QString symbol : newTransactions[key].keys())
        {
            QString str = "";

            for (QString state : newTransactions[key][symbol].keys())
            {
                str += state;
            }

            determinateGraph[key][symbol] = str;
        }
    }

    for(;;)
    {
        bool changed = false;

        for (QString key : determinateGraph.keys())
        {
            bool flag = true;

            if (key != "q0")
            {
                flag = false;

                for (QString tempkey : determinateGraph.keys())
                {
                    for (QString symbols : determinateGraph[tempkey].keys())
                    {
                        if (key == determinateGraph[tempkey][symbols])
                        {
                            flag = true;
                            break;
                        }
                    }

                    if (flag)
                    {
                        break;
                    }
                }
            }

            if (!flag)
            {
                changed = true;
                determinateGraph.remove(key);
            }
        }

        if (!changed)
        {
            break;
        }
    }

}

bool CStateMashine::isDeterminate()
{
    for (QString key : m_mapTransitions.keys())
    {
        for (QString symbols : m_mapTransitions[key].keys())
        {
            if (m_mapTransitions[key][symbols].size() > 1)
            {
                qDebug() << "No Determinated";
                return false;
            }
        }
    }

    qDebug() << "Determinated";
    return true;

    qDebug() << m_mapTransitions;
}

bool CStateMashine::isGood(QString str)
{
    QString state = "q0";

    for (int i = 0; i < str.size(); i++)
    {
        QString symbol = QString(str[i]);

        if (determinateGraph.value(state).contains(symbol))
        {
             state = determinateGraph[state][symbol];
        }
        else
        {
            return false;
        }
    }

    if (state[0] != 'f')
    {
        return false;
    }

    return true;
}
