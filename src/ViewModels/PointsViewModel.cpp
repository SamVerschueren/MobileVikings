/*
 * PointsViewModel.cpp
 *
 * Created on: 25-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include "PointsViewModel.hpp"

PointsViewModel::PointsViewModel() : loaded(false) {
    this->settings = new QSettings("samver", "bbVikings", this);
}

PointsViewModel::~PointsViewModel() {
    delete settings;
}

void PointsViewModel::setService(VikingService* service) {
    this->service = service;

    connect(this->service, SIGNAL(vikingPointsCompleted(QString, VikingPoints*)), this, SLOT(vikingPointsLoaded(QString, VikingPoints*)));
}

int PointsViewModel::getUsedPoints() const {
    return this->usedPoints;
}

int PointsViewModel::getUnusedPoints() const {
    return this->unusedPoints;
}

int PointsViewModel::getWaitingPoints() const {
    return this->waitingPoints;
}

int PointsViewModel::getEarnedPoints() const {
    return this->earnedPoints;
}

int PointsViewModel::getUsedTopups() const {
    return this->usedTopups;
}

Q_INVOKABLE void PointsViewModel::loadVikingPoints() {
    qDebug() << "SimBalanceViewModel::loadVikingPoints";

    if(!loaded && this->settings->contains("username") && this->settings->contains("password")) {
        this->service->loadPoints(this->settings->value("username", "").toString(), this->settings->value("password", "").toString(), this->settings->value("msisdn", "").toString());

        this->loaded = true;
    }
}

Q_INVOKABLE void PointsViewModel::reset() {
    this->loaded = false;
}

void PointsViewModel::vikingPointsLoaded(const QString& message, VikingPoints* points) {
    if(message == "" && points != NULL) {
        this->usedPoints = points->getUsedPoints();
        this->unusedPoints = points->getUnusedPoints();
        this->earnedPoints = points->getEarnedPoints();
        this->waitingPoints = points->getWaitingPoints();
        this->usedTopups = points->getUsedTopups();

        emit usedPointsChanged(this->usedPoints);
        emit unusedPointsChanged(this->unusedPoints);
        emit earnedPointsChanged(this->earnedPoints);
        emit waitingPointsChanged(this->waitingPoints);
        emit usedTopupsChanged(this->usedTopups);
    }

    emit loadCompleted(message);
}
