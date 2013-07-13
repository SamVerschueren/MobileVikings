/*
 * UsageViewModel.hpp
 *
 * Created on: 28-jun.-2013
 * Author: Sam Verschueren
 */

#ifndef USAGEVIEWMODEL_HPP_
#define USAGEVIEWMODEL_HPP_

#include <QObject>
#include <QDateTime>

#include "Usage.hpp"

class UsageViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QDateTime start READ getStart FINAL)
    Q_PROPERTY(QDate day READ getDay FINAL)
    Q_PROPERTY(QString duration READ getDuration FINAL)
    Q_PROPERTY(QString to READ getTo FINAL)
    Q_PROPERTY(QString price READ getPrice FINAL)
    Q_PROPERTY(QString statusImage READ getStatusImage FINAL)

    private:
        QDateTime start;
        QDate day;
        QString duration;
        QString to;
        QString price;
        QString statusImage;

    public:
        UsageViewModel(Usage* usage);

        QDateTime getStart() const;
        QDate getDay() const;
        QString getDuration() const;
        QString getTo() const;
        QString getPrice() const;
        QString getStatusImage() const;
};

#endif /* USAGEVIEWMODEL_HPP_ */
