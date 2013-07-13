/*
 * SimBalanceViewModel.hpp
 *
 * Created on: 23-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef SIMBALANCEVIEWMODEL_HPP_
#define SIMBALANCEVIEWMODEL_HPP_

#include <QObject>
#include <QSettings>

#include "VikingService.hpp"
#include "SimBalance.hpp"

class SimBalanceViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(VikingService* service WRITE setService FINAL)
    Q_PROPERTY(QDateTime validUntil READ getValidUntil NOTIFY validUntilChanged FINAL)
    Q_PROPERTY(QString credits READ getCredits NOTIFY creditsChanged FINAL)
    Q_PROPERTY(bool expired READ isExpired NOTIFY expiredChanged FINAL)
    Q_PROPERTY(QString sms READ getSms NOTIFY smsChanged FINAL)
    Q_PROPERTY(QString smsSuperOnNet READ getSmsSuperOnNet NOTIFY smsSuperOnNetChanged FINAL)
    Q_PROPERTY(QString voiceSuperOnNet READ getVoiceSuperOnNet NOTIFY voiceSuperOnNetChanged FINAL)
    Q_PROPERTY(QString data READ getData NOTIFY dataChanged FINAL)

    Q_SIGNALS:
        void validUntilChanged(const QDateTime& validUntil);
        void creditsChanged(const QString& credits);
        void expiredChanged(bool expired);
        void smsChanged(const QString& sms);
        void smsSuperOnNetChanged(const QString& smsSuperOnNet);
        void voiceSuperOnNetChanged(const QString& voiceSuperOnNet);
        void dataChanged(const QString& data);

    private:
        QSettings* settings;
        VikingService* vikingService;

        bool loaded;

        // properties
        QDateTime validUntil;
        QString credits;
        bool expired;
        QString sms;
        QString smsSuperOnNet;
        QString voiceSuperOnNet;
        QString data;

    public:
        SimBalanceViewModel();
        ~SimBalanceViewModel();

        void setService(VikingService* service);

        QDateTime getValidUntil() const;
        QString getCredits() const;
        bool isExpired() const;
        QString getSms() const;
        QString getSmsSuperOnNet() const;
        QString getVoiceSuperOnNet() const;
        QString getData() const;

        Q_INVOKABLE void loadSimBalance();
        Q_INVOKABLE void reset();

    private slots:
        void simBalanceLoaded(const QString& message, SimBalance* balance);

    signals:
        void loadCompleted(const QString& message);
};


#endif /* SIMBALANCEVIEWMODEL_HPP_ */
