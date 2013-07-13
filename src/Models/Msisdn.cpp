/*
 * Msisdn.cpp
 *
 * Created on: 4-jul.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include "Msisdn.hpp"

Msisdn::Msisdn(const QString& msisdn, const QString& alias) : msisdn(msisdn), alias(alias) {

}

Msisdn::~Msisdn() {

}

void Msisdn::setMsisdn(const QString& msisdn) {
    this->msisdn = msisdn;
}

QString Msisdn::getMsisdn() const {
    return this->msisdn;
}

void Msisdn::setAlias(const QString& alias) {
    this->alias = alias;
}

QString Msisdn::getAlias() const {
    return this->alias;
}
