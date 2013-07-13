/*
 * TopupHistoryListViewModel.hpp
 *
 * Created on: 26-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef TOPUPHISTORYLISTVIEWMODEL_HPP_
#define TOPUPHISTORYLISTVIEWMODEL_HPP_

#include <QObject>
#include <QSettings>
#include <bb/cascades/GroupDataModel>

#include "VikingService.hpp"
using namespace bb::cascades;

class TopupHistoryListViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(VikingService* service WRITE setService FINAL)
    Q_PROPERTY(GroupDataModel* dataModel READ getDataModel NOTIFY dataModelChanged FINAL)

    Q_SIGNALS:
        void dataModelChanged(GroupDataModel* dataModel);

    private slots:
        void topupHistoryLoaded(const QString& message, const QList<TopupHistory*>& list);

    private:
        GroupDataModel* dataModel;
        VikingService* service;
        QSettings* settings;

        bool loaded;

    public:
        TopupHistoryListViewModel();
        ~TopupHistoryListViewModel();

        GroupDataModel* getDataModel() const;
        void setService(VikingService* service);

        Q_INVOKABLE void loadTopupHistory();
        Q_INVOKABLE void reset();

    signals:
        void loadCompleted(const QString& message);
};

#endif /* TOPUPHISTORYLISTVIEWMODEL_HPP_ */
