/*
 * TopupHistory.hpp
 *
 * Created on: 26-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef TOPUPHISTORY_HPP_
#define TOPUPHISTORY_HPP_

#include <QObject>
#include <QDateTime>

class TopupHistory {

    private:
        double amount;
        double amountExVat;
        QString status;
        QString paymentMethod;
        QDateTime executedOn;
        QDateTime paymentReceivedOn;

    public:
        TopupHistory();

        double getAmount() const;
        void setAmount(double amount);

        double getAmountExVat() const;
        void setAmountExVat(double amountExVat);

        QString getStatus() const;
        void setStatus(const QString& status);

        QString getPaymentMethod() const;
        void setPaymentMethod(const QString& paymentMethod);

        QDateTime getExecutedOn() const;
        void setExecutedOn(const QDateTime& executedOn);

        QDateTime getPaymentReceivedOn() const;
        void setPaymentReceivedOn(const QDateTime& paymentReceivedOn);
};

#endif /* TOPUPHISTORY_HPP_ */
