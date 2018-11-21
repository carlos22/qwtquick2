#ifndef QMLPLOT_H
#define QMLPLOT_H

#include <QtQuick>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

class QwtQuick2Plot : public QQuickPaintedItem
{
    Q_OBJECT

public:
    QwtQuick2Plot( QQuickItem* parent = nullptr );
    virtual ~QwtQuick2Plot();

    void paint( QPainter* painter );

    Q_INVOKABLE void initQwtPlot();

protected:
    void routeMouseEvents( QMouseEvent* event );
    void routeWheelEvents( QWheelEvent* event );

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void wheelEvent( QWheelEvent *event );

    virtual void timerEvent(QTimerEvent *event);

private:
    QwtPlot*         m_qwtPlot;
    QwtPlotCurve*    m_curve1;
    int              m_timerId;

private slots:
    void updatePlotSize();

};

#endif // QMLPLOT_H
