/*
 * TopupHistoryViewModel.hpp
 *
 * Created on: 27-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef TOPUPHISTORYVIEWMODEL_HPP_
#define TOPUPHISTORYVIEWMODEL_HPP_

#include <QObject>
#include <QDateTime>

#include "TopupHistory.hpp"

class TopupHistoryViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString amount READ getAmount FINAL)
    Q_PROPERTY(QString status READ getStatus FINAL)
    Q_PROPERTY(QString paymentMethod READ getPaymentMethod FINAL)
    Q_PROPERTY(QDateTime executedOn READ getExecutedOn FINAL)
    Q_PROPERTY(QDateTime paymentReceivedOn READ getPaymentReceivedOn FINAL)

    private:
        QString amount;
        QString status;
        QString paymentMethod;
        QDateTime executedOn;
        QDateTime paymentReceivedOn;

    public:
        TopupHistoryViewModel(TopupHistory* history);

        QString getAmount() const;
        QString getStatus() const;
        QString getPaymentMethod() const;
        QDateTime getExecutedOn() const;
        QDateTime getPaymentReceivedOn() const;
};

#endif /* TOPUPHISTORYVIEWMODEL_HPP_ */
