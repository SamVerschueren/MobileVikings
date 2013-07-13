/*
 * MainViewModel.hpp
 *
 * Created on: 22-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef MAINVIEWMODEL_HPP_
#define MAINVIEWMODEL_HPP_

#include <QObject>
#include <QSettings>
#include <bb/cascades/GroupDataModel>

#include "VikingService.hpp"
#include "MsisdnViewModel.hpp"
#include "Msisdn.hpp"

using namespace bb::cascades;

class MainViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(VikingService* service WRITE setService FINAL)
    Q_PROPERTY(bool credentials READ hasCredentials FINAL)
    Q_PROPERTY(GroupDataModel* dataModel READ getDataModel NOTIFY dataModelChanged FINAL)
    Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged FINAL)

    Q_SIGNALS:
        void dataModelChanged(GroupDataModel *dataModel);
        void titleChanged(const QString& title);

    signals:
        void signOutCompleted();
        void msisdnChanged(const QString& msisdn);
        void msisdnCompleted(const QString& message, const QVariantList& list);

    private:
        bool credentials;
        QSettings* settings;

        VikingService* service;

        GroupDataModel* msisdnDataModel;
        MsisdnViewModel* selectedMsisdn;

    public:
        MainViewModel();
        ~MainViewModel();

        void setService(VikingService* service);

        bool hasCredentials() const;

        GroupDataModel* getDataModel() const;
        MsisdnViewModel* getSelectedMsisdn() const;

        QString getTitle() const;

        Q_INVOKABLE void signOut();
        Q_INVOKABLE void loadMsisdn();
        Q_INVOKABLE void selectMsisdn(const QVariantList& indexPath);

    private slots:
        void msisdnsLoaded(const QString& message, const QList<Msisdn*>& msisdn);
};

#endif /* MAINVIEWMODEL_HPP_ */
