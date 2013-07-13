/*
 * UsageListViewModel.cpp
 *
 * Created on: 27-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include "UsageListViewModel.hpp"
#include "UsageViewModel.hpp"

UsageListViewModel::UsageListViewModel() {
    this->settings = new QSettings("samver", "bbVikings", this);

    // Sort the list on the executedOn property in descending order
    this->dataModel = new GroupDataModel(QStringList() << "start");
    this->dataModel->setSortedAscending(false);
    this->dataModel->setSortingKeys(QStringList() << "day" << "start");
}

UsageListViewModel::~UsageListViewModel() {
    delete settings;
    delete dataModel;
}

GroupDataModel* UsageListViewModel::getDataModel() const {
    return this->dataModel;
}

void UsageListViewModel::setService(VikingService* service) {
    this->service = service;

    connect(this->service, SIGNAL(usageCompleted(QString, QList<Usage*>)), this, SLOT(usageLoaded(QString, QList<Usage*>)));
}

Q_INVOKABLE void UsageListViewModel::loadUsage() {
    qDebug() << "UsageListViewModel::loadUsage";

    if(!loaded && this->settings->contains("username") && this->settings->contains("password")) {
        this->service->loadUsage(this->settings->value("username", "").toString(), this->settings->value("password", "").toString(), this->settings->value("msisdn", "").toString());

        this->loaded = true;
    }
}

Q_INVOKABLE void UsageListViewModel::reset() {
    this->dataModel->clear();

    this->loaded = false;
}

void UsageListViewModel::usageLoaded(const QString& message, const QList<Usage*>& list) {
    qDebug() << "UsageListViewModel::usageLoaded";

    this->dataModel->clear();

    if(message == "" && list.size() > 0) {
        Q_FOREACH(Usage* usage, list) {
            this->dataModel->insert(new UsageViewModel(usage));
        }

        emit dataModelChanged(this->dataModel);
    }

    emit loadCompleted(message);
}
