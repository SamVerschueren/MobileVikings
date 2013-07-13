/*
 * MsisdnViewModel.cpp
 *
 * Created on: 4-jul.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include "MsisdnViewModel.hpp"

MsisdnViewModel::MsisdnViewModel(const Msisdn* msisdn) {
    this->setMsisdn(msisdn->getMsisdn());
    this->setAlias(msisdn->getAlias());
    this->setSelected(false);
}

void MsisdnViewModel::setMsisdn(const QString& msisdn) {
    this->msisdn = msisdn;

    emit msisdnChanged(this->msisdn);
}

QString MsisdnViewModel::getMsisdn() const {
    return this->msisdn;
}

void MsisdnViewModel::setAlias(const QString& alias) {
    this->alias = alias;

    emit aliasChanged(this->alias);
}

QString MsisdnViewModel::getAlias() const {
    return this->alias;
}

void MsisdnViewModel::setSelected(bool isSelected) {
    this->selected = isSelected;

    emit selectionChanged(isSelected);
}

bool MsisdnViewModel::isSelected() const {
    return this->selected;
}
