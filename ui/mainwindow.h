#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "qcustomplot.h"
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMap>
#include <QVector>
namespace Ui {
class MainWindow;
}
class ListItemHistory
{
public:

    float Ia;
    float Ib;
    float Ic;
    float P;
    float Q;
    int t;
    int index ;


};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void titleDoubleClick(QMouseEvent *event);
    void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);

    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void addRandomGraph();
    void removeSelectedGraph();
    void removeAllGraphs();
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);


    void on_pushButton_Search_clicked();

    void on_cb_Ia_stateChanged(int arg1);

    void on_cb_Ib_stateChanged(int arg1);

    void on_cb_P_stateChanged(int arg1);

    void on_cb_Q_stateChanged(int arg1);

    void on_cb_Ic_stateChanged(int arg1);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
public:
    void init(QString,QString);
     bool OpenCommonCsvfile(QString m_path);

public:
    QCPGraph *m_graphIa,*m_graphIb,*m_graphIc,*m_graphP,*m_graphQ;
    int m_nTimestamp;
    QString m_sIdx;
    QString m_sSqlstr ;
    QSqlDatabase dbConn;
    QString m_dbbuf;
    QMap<int,ListItemHistory> m_listHistoryCurve;   //鼠标选中曲线上任何一点，将Ia，Ib，Ic，P，Q所有当前时刻的值显示在界面上。
    QVector<double> m_vectorIa ,m_vectorIb ,m_vectorIc ,m_vectorP ,m_vectorQ ,m_vectorIanum;
    QVector<double> vectorIa ,vectorIb ,vectorIc ,vectorP ,vectorQ ,vectorIanum;
    bool m_bIa,m_bIb,m_bIc,m_bP,m_bQ;




private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
