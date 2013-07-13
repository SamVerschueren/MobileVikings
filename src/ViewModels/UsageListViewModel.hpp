/*
 * UsageListViewModel.hpp
 *
 * Created on: 27-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef USAGELISTVIEWMODEL_HPP_
#define USAGELISTVIEWMODEL_HPP_

#include <QObject>
#include <bb/cascades/GroupDataModel>

#include "Usage.hpp"
#include "VikingService.hpp"

using namespace bb::cascades;

class UsageListViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(VikingService* service WRITE setService FINAL)
    Q_PROPERTY(GroupDataModel* dataModel READ getDataModel NOTIFY dataModelChanged FINAL)

    Q_SIGNALS:
        void dataModelChanged(GroupDataModel *dataModel);

    private slots:
        void usageLoaded(const QString& message, const QList<Usage*>& list);

    private:
        GroupDataModel* dataModel;
        VikingService* service;
        QSettings* settings;

        bool loaded;

    public:
        UsageListViewModel();
        ~UsageListViewModel();

        GroupDataModel* getDataModel() const;
        void setService(VikingService* service);

        Q_INVOKABLE void loadUsage();
        Q_INVOKABLE void reset();

    signals:
        void loadCompleted(const QString& message);
};

#endif /* USAGELISTVIEWMODEL_HPP_ */
