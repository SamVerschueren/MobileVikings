/*
 * VikingService.hpp
 *
 *  Created on: 14-mei-2013
 *      Author: Sam
 */

#ifndef VIKINGSERVICE_HPP_
#define VIKINGSERVICE_HPP_

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

#include "Msisdn.hpp"
#include "SimBalance.hpp"
#include "Usage.hpp"
#include "TopupHistory.hpp"
#include "VikingPoints.hpp"

class VikingService : public QObject {
    Q_OBJECT

    signals:
        void msisdnCompleted(const QString& message, const QList<Msisdn*>& msisdns);
        void simBalanceCompleted(const QString& message, SimBalance* simbalance);
        void usageCompleted(const QString& message, const QList<Usage*>& usage);
        void topupHistoryCompleted(const QString& message, const QList<TopupHistory*>& topupHistory);
        void vikingPointsCompleted(const QString& message, VikingPoints* vikingPoints);

    private:
        QNetworkAccessManager* networkMsisdnManager;
        QNetworkAccessManager* networkSimManager;
        QNetworkAccessManager* networkUsageManager;
        QNetworkAccessManager* networkTopupManager;
        QNetworkAccessManager* networkPointsManager;

        QByteArray createAuthToken(const QString& username, const QString& password) const;

        QHash<QString, QString> phoneCache;

    public:
        VikingService();
        ~VikingService();

        void loadMsisdn(const QString& username, const QString& password) const;
        void loadSimBalance(const QString& username, const QString& password, const QString& msisdn) const;
        void loadUsage(const QString& username, const QString& password, const QString& msisdn) const;
        void loadTopupHistory(const QString& username, const QString& password, const QString& msisdn) const;
        void loadPoints(const QString& username, const QString& password, const QString& msisdn) const;

    private slots:
        void msisdnLoaded(QNetworkReply* reply);
        void simBalanceLoaded(QNetworkReply* reply);
        void usageLoaded(QNetworkReply* reply);
        void topupHistoryLoaded(QNetworkReply* reply);
        void pointsLoaded(QNetworkReply* reply);
};

#endif /* VIKINGSERVICE_HPP_ */
