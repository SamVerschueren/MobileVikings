/*
 * TopupHistoryListViewModel.cpp
 *
 * Created on: 26-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include "TopupHistoryListViewModel.hpp"
#include "TopupHistoryViewModel.hpp"

TopupHistoryListViewModel::TopupHistoryListViewModel() : loaded(false) {
    this->settings = new QSettings("samver", "bbVikings", this);

    // Sort the list on the executedOn property in descending order
    this->dataModel = new GroupDataModel(QStringList() << "executedOn");
    this->dataModel->setSortedAscending(false);
    this->dataModel->setGrouping(ItemGrouping::None);
}

TopupHistoryListViewModel::~TopupHistoryListViewModel() {
    delete settings;
    delete dataModel;
}

GroupDataModel* TopupHistoryListViewModel::getDataModel() const {
    return this->dataModel;
}

void TopupHistoryListViewModel::setService(VikingService* service) {
    this->service = service;

    connect(this->service, SIGNAL(topupHistoryCompleted(QString, QList<TopupHistory*>)), this, SLOT(topupHistoryLoaded(QString, QList<TopupHistory*>)));
}

Q_INVOKABLE void TopupHistoryListViewModel::loadTopupHistory() {
    qDebug() << "TopupHistoryViewModel::loadTopupHistory";

    if(!loaded && this->settings->contains("username") && this->settings->contains("password")) {
        this->service->loadTopupHistory(this->settings->value("username", "").toString(), this->settings->value("password", "").toString(), this->settings->value("msisdn", "").toString());

        this->loaded = true;
    }
}

Q_INVOKABLE void TopupHistoryListViewModel::reset() {
    this->dataModel->clear();

    this->loaded = false;
}

void TopupHistoryListViewModel::topupHistoryLoaded(const QString& message, const QList<TopupHistory*>& list) {
    qDebug() << "TopupHistoryViewModel::topupHistoryLoaded";

    this->dataModel->clear();

    if(message == "" && list.size() > 0) {
        Q_FOREACH(TopupHistory* history, list) {
            this->dataModel->insert(new TopupHistoryViewModel(history));
        }

        emit dataModelChanged(this->dataModel);
    }

    emit loadCompleted(message);
}
