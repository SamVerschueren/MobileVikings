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
    this->contact = usage->getContact().displayName();
    this->contactId = usage->getContact().id();

    if(usage->getType() == DATA) {
        double data = (double)usage->getConnectionDuration()/1048576;

        this->to = QString("%1 MB").arg(QString::number(data, 'f', 2));
    }
    else if(usage->getType() == VOICE) {
        QTime baseTime(0, 0, 0, 0);

        this->duration = baseTime.addSecs(usage->getCallDuration()).toString();
    }

    this->telInvocation = Invocation::create(InvokeQuery::create().parent(this).uri(QString("tel:%1").arg(usage->getTo())));

    this->invokeManager = new InvokeManager(this);
}

UsageViewModel::~UsageViewModel() {
    delete telInvocation;
    delete invokeManager;
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

QString UsageViewModel::getContact() const {
    return this->contact;
}

int UsageViewModel::getContactId() const {
    return this->contactId;
}

Q_INVOKABLE void UsageViewModel::sendText() const {
    this->telInvocation->trigger("bb.action.SENDTEXT");
}

Q_INVOKABLE void UsageViewModel::call() const {
    this->telInvocation->trigger("bb.action.DIAL");
}

Q_INVOKABLE void UsageViewModel::viewOrAddContact() const {
    InvokeRequest cardRequest;

    if(this->contact == "") {
        cardRequest.setTarget("sys.pim.contacts.card.picker");
        cardRequest.setAction("bb.action.ADDTOCONTACT");
        cardRequest.setMimeType("application/vnd.blackberry.string.phone");
        cardRequest.setData(this->to.toUtf8());
    }
    else {
        cardRequest.setTarget("sys.pim.contacts.card.viewer");
        cardRequest.setAction("bb.action.VIEW");
        cardRequest.setMimeType("application/vnd.blackberry.contact.id");
        cardRequest.setData(QString::number(this->contactId).toUtf8());
    }

    invokeManager->invoke(cardRequest);
}

Q_INVOKABLE void UsageViewModel::copyNumber() const {
    Clipboard clipboard;

    clipboard.clear();
    clipboard.insert("text/plain", this->getTo().toUtf8());
}
