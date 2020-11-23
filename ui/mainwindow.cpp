#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(QDateTime::currentDateTime().toTime_t());
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);





    //    QString sDefaultDate ="2019-11-02";
    //    m_nTimestamp = 1572624000;  //2019-11-02 00:00:00
    //    m_sSqlstr = "data20191102";
//    m_nTimestamp = 1572624000;  //2019-11-02 00:00:00
//    m_sSqlstr = "data20191102";
    QDateTime datetime;
    QString sDefaultDate =datetime.currentDateTime().addDays(-1).toString("yyyy-MM-dd ");
    ui->dateTimeEdit->setDateTime(datetime.currentDateTime().addDays(-1));
    m_nTimestamp = datetime.currentDateTime().addDays(-1).toTime_t();
    m_sSqlstr = "data" + datetime.currentDateTime().addDays(-1).toString("yyyyMMdd ");
    ui->cb_Ia->setCheckState(Qt::Checked);
    ui->cb_Ib->setCheckState(Qt::Checked);
    ui->cb_Ic->setCheckState(Qt::Checked);
    ui->cb_P->setCheckState(Qt::Checked);
    ui->cb_Q->setCheckState(Qt::Checked);
    QFont font1 ( "Microsoft YaHei", 20, 75);
    ui->statusBar->setFont(font1);

    m_bIa = m_bIb = m_bIc = m_bP = m_bQ = true;

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->customPlot->xAxis->setRange(-10, 10);
    ui->customPlot->yAxis->setRange(-5,155);
    ui->customPlot->axisRect()->setupFullAxesBox();

    ui->customPlot->plotLayout()->insertRow(0);
    QCPTextElement *title = new QCPTextElement(ui->customPlot, "Ia Ib Ic", QFont("sans", 17, QFont::Bold));
    ui->customPlot->plotLayout()->addElement(0, 0, title);

    ui->customPlot->xAxis->setLabel("Time");
    ui->customPlot->yAxis->setLabel("Value");
    ui->customPlot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->legend->setSelectedFont(legendFont);
    ui->customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items


    //     addRandomGraph();
    //     ui->customPlot->rescaleAxes();

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));/**/
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(ui->customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    //    connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));

    // setup policy and connect slot for context menu popup:
    ui->customPlot->setContextMenuPolicy(Qt::CustomContextMenu);




    ui->customPlot_4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->customPlot_4->xAxis->setRange(-10, 10);
    ui->customPlot_4->yAxis->setRange(-5,155);
    ui->customPlot_4->axisRect()->setupFullAxesBox();

    ui->customPlot_4->plotLayout()->insertRow(0);
    QCPTextElement *title4 = new QCPTextElement(ui->customPlot_4, "P    Q", QFont("sans", 17, QFont::Bold));
    ui->customPlot_4->plotLayout()->addElement(0, 0, title4);

    ui->customPlot_4->xAxis->setLabel("Time");
    ui->customPlot_4->yAxis->setLabel("Value");
    ui->customPlot_4->legend->setVisible(true);

    ui->customPlot_4->legend->setFont(legendFont);
    ui->customPlot_4->legend->setSelectedFont(legendFont);
    ui->customPlot_4->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

    //    ui->customPlot_4->rescaleAxes();

    connect(ui->customPlot_4, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->customPlot_4, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->customPlot_4, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->customPlot_4->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_4->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot_4->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_4->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(ui->customPlot_4, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    //    connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(ui->customPlot_4, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));

    // setup policy and connect slot for context menu popup:
    ui->customPlot_4->setContextMenuPolicy(Qt::CustomContextMenu);


    removeAllGraphs();
    OpenCommonCsvfile("common.CSV");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::titleDoubleClick(QMouseEvent* event)
{
    Q_UNUSED(event)
    if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender()))
    {
        // Set the plot title by double clicking on it
        bool ok;
        QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
        if (ok)
        {
            title->setText(newTitle);
            ui->customPlot->replot();
        }
    }
}

void MainWindow::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    // Set an axis label by double clicking on it
    if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
    {
        bool ok;
        QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
        if (ok)
        {
            axis->setLabel(newLabel);
            ui->customPlot->replot();
        }
    }
}



void MainWindow::selectionChanged()
{
    /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.
   
   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.
   
   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // synchronize selection of graphs with selection of corresponding legend items:
    for (int i=0; i<ui->customPlot->graphCount(); ++i)
    {

        QCPGraph *graph = ui->customPlot->graph(i);
        QCPPlottableLegendItem *item = ui->customPlot->legend->itemWithPlottable(graph);

        if (item->selected() || graph->selected())
        {

            item->setSelected(true);
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
        }
    }
}

void MainWindow::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->xAxis->orientation());
    else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->yAxis->orientation());
    else
        ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->xAxis->orientation());
    else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->yAxis->orientation());
    else
        ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::addRandomGraph()
{


}

void MainWindow::removeSelectedGraph()
{
    if (ui->customPlot->selectedGraphs().size() > 0)
    {
        ui->customPlot->removeGraph(ui->customPlot->selectedGraphs().first());
        ui->customPlot->replot();
    }
}

void MainWindow::removeAllGraphs()
{
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
    ui->customPlot_4->clearGraphs();
    ui->customPlot_4->replot();
}



void MainWindow::moveLegend()
{
    if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
            ui->customPlot->replot();
        }
    }
}

void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
    // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
    // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
    double dataValue = plottable->interface1D()->dataMainValue(dataIndex);


    if(m_listHistoryCurve.contains(dataIndex))
    {

        QString strTime = QDateTime::fromTime_t(m_listHistoryCurve.find(dataIndex).value().t).toString("yyyy-MM-dd hh:mm:ss");

        QString str ;
        ui->label_Ia->setText(str.sprintf("%.2f A",m_listHistoryCurve.find(dataIndex).value().Ia));
        ui->label_Ib->setText(str.sprintf("%.2f A", m_listHistoryCurve.find(dataIndex).value().Ib));
        ui->label_Ic->setText(str.sprintf("%.2f A", m_listHistoryCurve.find(dataIndex).value().Ic));
        ui->label_P->setText(str.sprintf("%.2f  kW", m_listHistoryCurve.find(dataIndex).value().P));
        ui->label_Q->setText(str.sprintf("%.2f kVar", m_listHistoryCurve.find(dataIndex).value().Q));
        ui->label_time->setText(strTime);
        //        ui->label_timeDesc->setText("Now time value:");
        QString st=QString::fromLocal8Bit("当前时刻电机值:");
        ui->label_timeDesc->setText(st);


    }

    //    qDebug()<<ui->customPlot->selectedGraphs().size() <<ui->customPlot->selectedGraphs();

    //    QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
    //    ui->statusBar->showMessage(message, 2500);
}






void MainWindow::on_pushButton_Search_clicked()
{
    //    QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
    /*    QString message = "Please wait...Searching...";
    ui->statusBar->showMessage(message, 0)*/;

    QString str1=QString::fromLocal8Bit("正在查询数据，请等待...");
    ui->statusBar->showMessage(str1, 0);
    qDebug()<<"on_pushButton_Search_clicked "<<ui->dateTimeEdit->date();
    ui->dateTimeEdit->setEnabled(false);
    ui->pushButton_Search->setEnabled(false);
    ui->cb_Ia->setEnabled(false);
    ui->cb_Ib->setEnabled(false);
    ui->cb_Ic->setEnabled(false);
    ui->cb_Q->setEnabled(false);
    ui->cb_P->setEnabled(false);




    removeAllGraphs();
    m_listHistoryCurve.clear();
    vectorIa.clear();
    vectorIb.clear();
    vectorIc.clear();
    vectorP.clear();
    vectorQ.clear();
    vectorIanum.clear();

    QMap<int,ListItemHistory> tempHistoryCure;
    //    int temp_t = m_nTimestamp;  //2019-11-02 00:00:00

    int temp_t=1572624000;
    temp_t=m_nTimestamp;

    qDebug()<<"m_sSqlstr"<<m_sSqlstr <<"m_nTimestamp"<<m_nTimestamp;

    //    QVector<double> vectorIa ,vectorIb ,vectorIc ,vectorP ,vectorQ ,vectorIanum;

    dbConn = QSqlDatabase::addDatabase("QODBC");
    //   dbConn.setDatabaseName("Driver={SQL Server};Server=172.17.64.69;Database=overload;UID=sa;PWD=COSLIGHT;");
    //    dbConn.setDatabaseName("Driver={SQL Server};Server=172.17.78.18;Database=overload;UID=sa;PWD=Coslight123;");
    dbConn.setDatabaseName(m_dbbuf);
    qDebug() << " m_dbbuf"<<m_dbbuf;

    if(!dbConn.open ())
    {
        qDebug() << "Database open failed!";


    }else
    {
        QStringList str;
        QSqlQuery query(dbConn);

        query.setForwardOnly(true);

        QString strSqlText("SELECT v1 , v2, v3 , t , v10, v11  FROM [overload].[dbo].["+ m_sSqlstr+"]  WHERE idx = "+ m_sIdx+" order by t");//查询语法
        qDebug() << "SELECT strSqlText"<<strSqlText;
        query.prepare(strSqlText);
        query.exec();

        int num =0;

        while (query.next()) //依次取出查询结果的每一条记录，直至结束
        {

            ListItemHistory data;
            data.Ia = query.value(0).toFloat();
            data.Ib = query.value(1).toFloat();
            data.Ic = query.value(2).toFloat();
            data.P = query.value(4).toFloat();
            data.Q = query.value(5).toFloat();
            data.t = query.value(3).toInt();
            vectorIa.append(data.Ia);
            vectorIb.append(data.Ib);
            vectorIc.append(data.Ic);
            vectorP.append(query.value(4).toFloat());
            vectorQ.append(query.value(5).toFloat());
            vectorIanum.append(data.t);
            data.index = num++;
            m_listHistoryCurve.insert(data.index,data);
            tempHistoryCure.insert(data.t,data);


        }
    }
    dbConn.close();


    //如果查询数据少于86400点，则检查缺失时间点的数据，并将数据填充为0.
    if(tempHistoryCure.size()<86400 && tempHistoryCure.size() >0)
    {
        m_listHistoryCurve.clear();
        for(int n = 0; n < 86400 ;n++)
        {
            ListItemHistory data;

            if(tempHistoryCure.contains(temp_t))
            {
                // 1572624000


                vectorIa.append(tempHistoryCure.find(temp_t).value().Ia);
                vectorIb.append(tempHistoryCure.find(temp_t).value().Ib);
                vectorIc.append(tempHistoryCure.find(temp_t).value().Ic);
                vectorP.append(tempHistoryCure.find(temp_t).value().P);
                vectorQ.append(tempHistoryCure.find(temp_t).value().Q);

                data.Ia = tempHistoryCure.find(temp_t).value().Ia;
                data.Ib = tempHistoryCure.find(temp_t).value().Ib;
                data.Ic = tempHistoryCure.find(temp_t).value().Ic;
                data.P = tempHistoryCure.find(temp_t).value().P;
                data.Q = tempHistoryCure.find(temp_t).value().Q;
                data.t = tempHistoryCure.find(temp_t).value().t;
            }
            else
            {

                vectorIa.append(0);
                vectorIb.append(0);
                vectorIc.append(0);
                vectorP.append(0);
                vectorQ.append(0);

                data.Ia = 0;
                data.Ib = 0;
                data.Ic = 0;
                data.P = 0;
                data.Q = 0;
                data.t = 0;

            }
            m_listHistoryCurve.insert(n,data);
            vectorIanum.append(temp_t);
            temp_t++;


        }
    }


    //绘制Ia，Ib，Ic，P，Q曲线
    for (int k=0; k<5; k++)
    {
        if(k == 0 && m_bIa)
        {
            QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
            dateTicker->setDateTimeFormat("yy-MM-dd hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
            ui->customPlot->xAxis->setTicker(dateTicker);//设置X轴为时间轴

            m_graphIa = ui->customPlot->addGraph();
            //              ui->customPlot->graph()->setName(QString("New graph %1").arg(ui->customPlot->graphCount()-1));
            ui->customPlot->graph()->setName(QString("Ia"));
            ui->customPlot->graph()->setData(vectorIanum, vectorIa);
            //   ui->customPlot->graph()->setData(time1, value);
            //  ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
            ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(1));
            if (rand()%100 > 50)
            {
                ui->customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));

            }

            QPen graphPen;

            graphPen.setColor(QColor(Qt::yellow));
            graphPen.setWidthF(1);
            ui->customPlot->graph()->setPen(graphPen);
            ui->customPlot->replot();
        }
        if(k == 1 && m_bIb )
        {
            m_graphIb = ui->customPlot->addGraph();
            ui->customPlot->graph()->setName(QString("Ib"));
            ui->customPlot->graph()->setData(vectorIanum, vectorIb);
            //  ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
            ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(1));
            if (rand()%100 > 50)
            {
                ui->customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));

            }
            QPen graphPen;
            graphPen.setColor(QColor(Qt::green));
            graphPen.setWidthF(1);
            ui->customPlot->graph()->setPen(graphPen);
            ui->customPlot->replot();
        }

        if(k == 2 && m_bIc)
        {

            m_graphIc =ui->customPlot->addGraph();
            ui->customPlot->graph()->setName(QString("Ic"));
            ui->customPlot->graph()->setData(vectorIanum, vectorIc);
            ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(1));
            if (rand()%100 > 50)
            {
                ui->customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ssNone)));

            }
            QPen graphPen;
            graphPen.setColor(QColor(Qt::red));
            graphPen.setWidthF(1);
            ui->customPlot->graph()->setPen(graphPen);
            ui->customPlot->replot();
        }
        if(k == 3 && m_bP)
        {
            QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
            dateTicker->setDateTimeFormat("yy-MM-dd hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
            ui->customPlot_4->xAxis->setTicker(dateTicker);//设置X轴为时间轴


            m_graphP =ui->customPlot_4->addGraph();
            //              ui->customPlot->graph()->setName(QString("New graph %1").arg(ui->customPlot->graphCount()-1));
            ui->customPlot_4->graph()->setName(QString("P"));
            ui->customPlot_4->graph()->setData(vectorIanum, vectorP);
            ui->customPlot_4->graph()->setLineStyle((QCPGraph::LineStyle)(1));
            if (rand()%100 > 50)
            {
                ui->customPlot_4->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));

            }
            QPen graphPen;
            graphPen.setColor(QColor(255, 0, 255));
            graphPen.setWidthF(1);
            ui->customPlot_4->graph()->setPen(graphPen);
            ui->customPlot_4->replot();
        }
        if(k == 4 && m_bQ )
        {
            QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
            dateTicker->setDateTimeFormat("yy-MM-dd hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
            ui->customPlot_4->xAxis->setTicker(dateTicker);//设置X轴为时间轴


            m_graphQ =ui->customPlot_4->addGraph();
            //              ui->customPlot->graph()->setName(QString("New graph %1").arg(ui->customPlot->graphCount()-1));
            ui->customPlot_4->graph()->setName(QString("Q"));
            ui->customPlot_4->graph()->setData(vectorIanum, vectorQ);
            ui->customPlot_4->graph()->setLineStyle((QCPGraph::LineStyle)(1));
            if (rand()%100 > 50)
            {
                ui->customPlot_4->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));

            }
            QPen graphPen;
            graphPen.setColor(QColor(Qt::black));
            graphPen.setWidthF(1);
            ui->customPlot_4->graph()->setPen(graphPen);
            ui->customPlot_4->replot();
        }

        ui->customPlot->rescaleAxes();
        ui->customPlot_4->rescaleAxes();

    }
    ui->cb_Ia->setEnabled(true);
    ui->cb_Ib->setEnabled(true);
    ui->cb_Ic->setEnabled(true);
    ui->cb_Q->setEnabled(true);
    ui->cb_P->setEnabled(true);
    ui->dateTimeEdit->setEnabled(true);
    ui->pushButton_Search->setEnabled(true);
    //    message = "Table query completed";
    //    ui->statusBar->showMessage(message, 0);

    QString str=QString::fromLocal8Bit("查询完毕");
    ui->statusBar->showMessage(str, 0);


}

void MainWindow::on_cb_Ia_stateChanged(int arg1)
{

    if(arg1== Qt::Unchecked)
    {
        ui->customPlot->removeGraph(m_graphIa);
        ui->customPlot->replot();

        m_bIa = false;

    }
    else
    {
        m_bIa = true;
        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
        dateTicker->setDateTimeFormat("yy-MM-dd hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
        ui->customPlot->xAxis->setTicker(dateTicker);//设置X轴为时间轴

        m_graphIa = ui->customPlot->addGraph();
        ui->customPlot->graph()->setName(QString("Ia"));
        ui->customPlot->graph()->setData(vectorIanum, vectorIa);

        ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(1));
        if (rand()%100 > 50)
        {
            ui->customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));

        }
        QPen graphPen;
        graphPen.setColor(Qt::yellow);
        graphPen.setWidthF(1);
        ui->customPlot->graph()->setPen(graphPen);
        ui->customPlot->replot();
        ui->customPlot->rescaleAxes();
    }

}
void MainWindow::on_cb_Ic_stateChanged(int arg1)
{
    if(arg1== Qt::Unchecked)
    {
        ui->customPlot->removeGraph(m_graphIc);
        ui->customPlot->replot();

        m_bIc = false;

    }
    else
    {
        m_bIc = true;
        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
        dateTicker->setDateTimeFormat("yy-MM-dd hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
        ui->customPlot->xAxis->setTicker(dateTicker);//设置X轴为时间轴

        m_graphIc = ui->customPlot->addGraph();
        ui->customPlot->graph()->setName(QString("Ic"));
        ui->customPlot->graph()->setData(vectorIanum, vectorIc);

        ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(1));
        if (rand()%100 > 50)
        {
            ui->customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));

        }
        QPen graphPen;
        graphPen.setColor(Qt::red);
        graphPen.setWidthF(1);
        ui->customPlot->graph()->setPen(graphPen);
        ui->customPlot->replot();
        ui->customPlot->rescaleAxes();
    }

}


void MainWindow::on_cb_Ib_stateChanged(int arg1)
{
    if(arg1== Qt::Unchecked)
    {
        ui->customPlot->removeGraph(m_graphIb);
        ui->customPlot->replot();

        m_bIb = false;

    }
    else
    {
        m_bIb = true;
        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
        dateTicker->setDateTimeFormat("yy-MM-dd hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
        ui->customPlot->xAxis->setTicker(dateTicker);//设置X轴为时间轴

        m_graphIb = ui->customPlot->addGraph();
        ui->customPlot->graph()->setName(QString("Ib"));
        ui->customPlot->graph()->setData(vectorIanum, vectorIb);

        ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(1));
        if (rand()%100 > 50)
        {
            ui->customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));

        }
        QPen graphPen;
        graphPen.setColor(Qt::green);
        graphPen.setWidthF(1);
        ui->customPlot->graph()->setPen(graphPen);
        ui->customPlot->replot();
        ui->customPlot->rescaleAxes();
    }

}



void MainWindow::on_cb_P_stateChanged(int arg1)
{
    if(arg1== Qt::Unchecked)
    {
        ui->customPlot_4->removeGraph(m_graphP);
        ui->customPlot_4->replot();
        m_bP = false;

    }
    else
    {
        m_bP = true;
        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
        dateTicker->setDateTimeFormat("yy-MM-dd hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
        ui->customPlot_4->xAxis->setTicker(dateTicker);//设置X轴为时间轴


        m_graphP = ui->customPlot_4->addGraph();
        //              ui->customPlot->graph()->setName(QString("New graph %1").arg(ui->customPlot->graphCount()-1));
        ui->customPlot_4->graph()->setName(QString("P"));
        ui->customPlot_4->graph()->setData(vectorIanum, vectorP);
        //   ui->customPlot->graph()->setData(time1, value);
        //  ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
        ui->customPlot_4->graph()->setLineStyle((QCPGraph::LineStyle)(1));
        if (rand()%100 > 50)
        {
            ui->customPlot_4->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));

        }
        QPen graphPen;
        graphPen.setColor(QColor(255, 0, 255));
        graphPen.setWidthF(1);
        ui->customPlot_4->graph()->setPen(graphPen);
        ui->customPlot_4->replot();
        ui->customPlot_4->rescaleAxes();
    }
}

void MainWindow::on_cb_Q_stateChanged(int arg1)
{
    if(arg1== Qt::Unchecked)
    {
        ui->customPlot_4->removeGraph(m_graphQ);
        ui->customPlot_4->replot();
        m_bQ = false;

    }
    else
    {
        m_bQ = true;
        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
        dateTicker->setDateTimeFormat("yy-MM-dd hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
        ui->customPlot_4->xAxis->setTicker(dateTicker);//设置X轴为时间轴     ui->customPlot_4->addGraph();
        m_graphQ = ui->customPlot_4->addGraph();
        ui->customPlot_4->graph()->setName(QString("Q"));
        ui->customPlot_4->graph()->setData(vectorIanum, vectorQ);
        ui->customPlot_4->graph()->setLineStyle((QCPGraph::LineStyle)(1));
        if (rand()%100 > 50)
        {
            ui->customPlot_4->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));

        }
        QPen graphPen;
        graphPen.setColor(Qt::black);
        graphPen.setWidthF(1);
        ui->customPlot_4->graph()->setPen(graphPen);
        ui->customPlot_4->replot();
        ui->customPlot_4->rescaleAxes();
    }
}




void MainWindow::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{

    m_nTimestamp = dateTime.toTime_t();
    m_sSqlstr =  "data"+dateTime.toString("yyyyMMdd");

}
void MainWindow::init(QString num,QString nameshow)
{
    m_sIdx = num;
}

bool MainWindow::OpenCommonCsvfile(QString m_path)
{
    QStringList m_lis;
    QFile inFile(m_path);
    QStringList lines;
    if (inFile.open(QIODevice::ReadOnly))
    {
        QTextStream stream_text(&inFile);
        while (!stream_text.atEnd())
        {
            lines.push_back(stream_text.readLine());
        }

        for (int j = 0; j < lines.size(); j++)
        {

            QString line = lines.at(j);
            QStringList split = line.split(",");
            QStringList temp;

            if(j==0)
            {
                m_lis=split;
            }else
            {

                m_dbbuf = split.at(3);
            }

        }
        inFile.close();
    }
    return true;
}
