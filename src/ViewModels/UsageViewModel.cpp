/*
 * UsageViewModel.cpp
 *
 * Created on: 28-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include <QDebug>
#include "UsageViewModel.hpp"

UsageViewModel::UsageViewModel(Usage* usage) {
    this->start = usage->getStart();
    this->day = usage->getStart().date();
    this->to = usage->getType() == DATA ? "" : usage->getTo();
    this->price = QString("%1 %2").arg(QChar(8364)).arg(usage->getPrice());
    this->statusImage = QString("%1-%2.png").arg(usage->getType()).arg(usage->isIncoming()?"in":"out");
    this->duration = "";

    if(usage->getType() == DATA) {
        double data = (double)usage->getConnectionDuration()/1048576;

        this->to = QString("%1 MB").arg(QString::number(data, 'f', 2));
    }
    else if(usage->getType() == VOICE) {
        QTime baseTime(0, 0, 0, 0);

        this->duration = baseTime.addSecs(usage->getCallDuration()).toString();
    }
}

QDateTime UsageViewModel::getStart() const {
    return this->start;
}

QDate UsageViewModel::getDay() const {
    return this->day;
}

QString UsageViewModel::getDuration() const {
    return this->duration;
}

QString UsageViewModel::getTo() const {
    return this->to;
}

QString UsageViewModel::getPrice() const {
    return this->price;
}

QString UsageViewModel::getStatusImage() const {
    return this->statusImage;
}
