#ifndef PLOTDATA_H
#define PLOTDATA_H

#include <QPointF>
#include <QVector>

#include <qwt_series_data.h>


class PlotData : public QwtSeriesData<QPointF>
{
public:
    PlotData(const QVector<QPointF> *container);

private:
      const QVector<QPointF>* _container;

      // QwtSeriesData interface
public:
      size_t size() const;
      QPointF sample(size_t i) const;
      QRectF boundingRect() const;
};








#endif // PLOTDATA_H
