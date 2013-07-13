/*
 * TopupHistoryViewModel.cpp
 *
 * Created on: 27-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include "TopupHistoryViewModel.hpp"

TopupHistoryViewModel::TopupHistoryViewModel(TopupHistory* history) {
    this->amount = QString("%1 %2").arg(QChar(8364)).arg(history->getAmount());
    this->status = history->getStatus();
    this->paymentMethod = history->getPaymentMethod();
    this->executedOn = history->getExecutedOn();
    this->paymentReceivedOn = history->getPaymentReceivedOn();
}

QString TopupHistoryViewModel::getAmount() const {
    return this->amount;
}

QString TopupHistoryViewModel::getStatus() const {
    return this->status;
}

QString TopupHistoryViewModel::getPaymentMethod() const {
    return this->paymentMethod;
}

QDateTime TopupHistoryViewModel::getExecutedOn() const {
    return this->executedOn;
}

QDateTime TopupHistoryViewModel::getPaymentReceivedOn() const {
    return this->paymentReceivedOn;
}
