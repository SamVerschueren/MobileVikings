/*
 * TopupHistory.cpp
 *
 * Created on: 26-jun.-2013
 * Author: Sam
 */

#include "TopupHistory.hpp"

TopupHistory::TopupHistory() {

}

double TopupHistory::getAmount() const {
    return this->amount;
}

void TopupHistory::setAmount(double amount) {
    this->amount = amount;
}

double TopupHistory::getAmountExVat() const {
    return this->amountExVat;
}

void TopupHistory::setAmountExVat(double amountExVat) {
    this->amountExVat = amountExVat;
}

QString TopupHistory::getStatus() const {
    return this->status;
}

void TopupHistory::setStatus(const QString& status) {
    this->status = status;
}

QString TopupHistory::getPaymentMethod() const {
    return this->paymentMethod;
}

void TopupHistory::setPaymentMethod(const QString& paymentMethod) {
    this->paymentMethod = paymentMethod;
}

QDateTime TopupHistory::getExecutedOn() const {
    return this->executedOn;
}

void TopupHistory::setExecutedOn(const QDateTime& executedOn) {
    this->executedOn = executedOn;
}

QDateTime TopupHistory::getPaymentReceivedOn() const {
    return this->paymentReceivedOn;
}

void TopupHistory::setPaymentReceivedOn(const QDateTime& paymentReceivedOn) {
    this->paymentReceivedOn = paymentReceivedOn;
}
