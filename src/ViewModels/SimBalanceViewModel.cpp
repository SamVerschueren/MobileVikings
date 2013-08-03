/*
 * SimBalanceViewModel.cpp
 *
 * Created on: 23-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include <QDebug>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Container>
#include <bb/cascades/SceneCover>

#include "SimBalanceViewModel.hpp"

using namespace bb::cascades;

SimBalanceViewModel::SimBalanceViewModel() : loaded(false) {
    this->settings = new QSettings("samver", "bbVikings", this);
}

SimBalanceViewModel::~SimBalanceViewModel() {
    delete settings;
}

void SimBalanceViewModel::setService(VikingService* service) {
    this->vikingService = service;

    connect(this->vikingService, SIGNAL(simBalanceCompleted(QString, SimBalance*)), this, SLOT(simBalanceLoaded(QString, SimBalance*)));
}

QDateTime SimBalanceViewModel::getValidUntil() const {
    return this->validUntil;
}

QString SimBalanceViewModel::getCredits() const {
    return this->credits;
}

bool SimBalanceViewModel::isExpired() const {
    return this->expired;
}

QString SimBalanceViewModel::getSms() const {
    return this->sms;
}

QString SimBalanceViewModel::getSmsSuperOnNet() const {
    return this->smsSuperOnNet;
}

QString SimBalanceViewModel::getVoiceSuperOnNet() const {
    return this->voiceSuperOnNet;
}

QString SimBalanceViewModel::getData() const {
    return this->data;
}

void SimBalanceViewModel::setMsisdn(const QString& msisdn) {
    this->msisdn = msisdn;
}

Q_INVOKABLE void SimBalanceViewModel::loadSimBalance() {
    qDebug() << "SimBalanceViewModel::loadSimBalance";

    if(!loaded && this->settings->contains("username") && this->settings->contains("password")) {
        this->vikingService->loadSimBalance(this->settings->value("username", "").toString(), this->settings->value("password", "").toString(), this->settings->value("msisdn", "").toString());

        this->loaded = true;
    }
}

Q_INVOKABLE void SimBalanceViewModel::reset() {
    this->loaded = false;
}

void SimBalanceViewModel::simBalanceLoaded(const QString& message, SimBalance* balance) {
    if(message == "" && balance != NULL) {
        QString dataFormat = "MB";

        double data = balance->getData()/1048576;

        if(data >= 1000) {
            data /= 1024;
            dataFormat = "GB";
        }

        this->validUntil = balance->getValidUntil();
        this->credits = QString("%1 %2").arg(QChar(8364)).arg(balance->getCredits());
        this->expired = balance->isExpired();
        this->sms = QString("%1").arg(balance->getSms());
        this->smsSuperOnNet = QString("%1/%2").arg(balance->getSmsSuperOnNet()).arg(balance->getSmsSuperOnNetMax());
        this->voiceSuperOnNet = QString("%1/%2").arg(balance->getVoiceSuperOnNet()).arg(balance->getVoiceSuperOnNetMax());
        this->data = QString("%1 %2").arg(QString::number(data, 'f', 2)).arg(dataFormat);

        emit validUntilChanged(this->validUntil);
        emit creditsChanged(this->credits);
        emit expiredChanged(this->expired);
        emit smsChanged(this->sms);
        emit smsSuperOnNetChanged(this->smsSuperOnNet);
        emit voiceSuperOnNetChanged(this->voiceSuperOnNet);
        emit dataChanged(this->data);
    }

    QmlDocument *qmlCover = QmlDocument::create("asset:///Cover.qml").parent(this);

    if (!qmlCover->hasErrors()) {
        Container *coverContainer = qmlCover->createRootObject<Container>();
        coverContainer->setProperty("title", this->msisdn);
        coverContainer->setProperty("credits", this->credits);
        coverContainer->setProperty("expiry", this->validUntil.date().toString(Qt::SystemLocaleShortDate));
        SceneCover *sceneCover = SceneCover::create().content(coverContainer);

        Application::instance()->setCover(sceneCover);
    }

    emit loadCompleted(message);
}

