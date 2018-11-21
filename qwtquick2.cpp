#include "qwtquick2.h"

#include <qwt_plot.h>

#include <QDebug>
#include <qwt_plot_curve.h>
#include <qwt_plot_renderer.h>

QwtQuick2Plot::QwtQuick2Plot( QQuickItem* parent ) : QQuickPaintedItem( parent )
    , m_qwtPlot( nullptr ), m_timerId( 0 )
{
    setFlag( QQuickItem::ItemHasContents, true );
    setAcceptedMouseButtons( Qt::AllButtons );

    connect( this, &QQuickPaintedItem::widthChanged, this, &QwtQuick2Plot::updatePlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &QwtQuick2Plot::updatePlotSize );
}

QwtQuick2Plot::~QwtQuick2Plot()
{
    delete m_qwtPlot;
    m_qwtPlot = nullptr;

    if(m_timerId != 0) {
        killTimer(m_timerId);
    }
}

void QwtQuick2Plot::initQwtPlot()
{
    m_qwtPlot = new QwtPlot();
    m_qwtPlot->setAutoReplot(true);
    m_qwtPlot->setStyleSheet("background: white");

    updatePlotSize();

    m_curve1 = new QwtPlotCurve("Curve 1");

    m_curve1->setPen(QPen(Qt::red));
    m_curve1->setStyle(QwtPlotCurve::Lines);

    QVector<QPointF> v;
    v.append(QPointF(1.0, 2.0));
    v.append(QPointF(2.0, 4.4));
    v.append(QPointF(2.5, 8.4));
    v.append(QPointF(4.5, 10.0));
    m_curve1->setSamples(v);

    m_qwtPlot->setAxisTitle( m_qwtPlot->xBottom, tr("t") );
    m_qwtPlot->setAxisTitle( m_qwtPlot->yLeft, tr("S" ) );

    m_curve1->attach(m_qwtPlot);

    startTimer(500);

    m_qwtPlot->replot();
}


void QwtQuick2Plot::paint( QPainter* painter )
{
    if (m_qwtPlot)
    {
        QPixmap    picture( boundingRect().size().toSize() );

        QwtPlotRenderer renderer;
        renderer.renderTo(m_qwtPlot, picture);

        painter->drawPixmap( QPoint(), picture );
    }
}

void QwtQuick2Plot::mousePressEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void QwtQuick2Plot::mouseReleaseEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void QwtQuick2Plot::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void QwtQuick2Plot::mouseDoubleClickEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void QwtQuick2Plot::wheelEvent( QWheelEvent* event )
{
    routeWheelEvents( event );
}

void QwtQuick2Plot::timerEvent(QTimerEvent* /*event*/)
{
    static double t, U;
    U = (static_cast<double>(qrand()) / RAND_MAX) * 5;

    // TODO: impl
    /*
    QVector<QPointF> v;
    v.append(QPointF(t, U));
    m_curve1->setSamples(v);
    */

    qDebug() << Q_FUNC_INFO << QString("Adding dot t = %1, S = %2").arg(t).arg(U);
    t++;
    m_qwtPlot->replot();
}

void QwtQuick2Plot::routeMouseEvents( QMouseEvent* event )
{
    if (m_qwtPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        QCoreApplication::postEvent( m_qwtPlot, newEvent );
    }
}

void QwtQuick2Plot::routeWheelEvents( QWheelEvent* event )
{
    if (m_qwtPlot)
    {
        QWheelEvent* newEvent = new QWheelEvent( event->pos(), event->delta(), event->buttons(), event->modifiers(), event->orientation() );
        QCoreApplication::postEvent( m_qwtPlot, newEvent );
    }
}

void QwtQuick2Plot::updatePlotSize()
{
    if (m_qwtPlot) {
        m_qwtPlot->setGeometry(0, 0, static_cast<int>(width()), static_cast<int>(height()));
    }
}
