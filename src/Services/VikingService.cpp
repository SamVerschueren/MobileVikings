/*
 * VikingService.cpp
 *
 * Created on: 14-mei-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include <bb/data/JsonDataAccess>
#include <bb/pim/contacts/ContactService>
#include "VikingService.hpp"
#include "UsageType.hpp"
using namespace bb::data;
using namespace bb::pim::contacts;

VikingService::VikingService() {
    this->networkMsisdnManager = new QNetworkAccessManager(this);
    connect(this->networkMsisdnManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(msisdnLoaded(QNetworkReply*)));

    this->networkSimManager = new QNetworkAccessManager(this);
    connect(this->networkSimManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(simBalanceLoaded(QNetworkReply*)));

    this->networkUsageManager = new QNetworkAccessManager(this);
    connect(this->networkUsageManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(usageLoaded(QNetworkReply*)));

    this->networkTopupManager = new QNetworkAccessManager(this);
    connect(this->networkTopupManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(topupHistoryLoaded(QNetworkReply*)));

    this->networkPointsManager = new QNetworkAccessManager(this);
    connect(this->networkPointsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(pointsLoaded(QNetworkReply*)));
}

VikingService::~VikingService() {
    delete networkMsisdnManager;
    delete networkSimManager;
    delete networkUsageManager;
    delete networkTopupManager;
    delete networkPointsManager;
}

void VikingService::loadMsisdn(const QString& username, const QString& password) const {
    QNetworkRequest request;
    request.setRawHeader("Authorization", "Basic " + this->createAuthToken(username, password));
    request.setUrl(QUrl("https://mobilevikings.com/api/2.0/basic/msisdn_list.json?alias=1"));

    this->networkMsisdnManager->get(request);
}

/**
 * Loads the simbalance of the account with the username and password provided.
 *
 * @param username The username of the user.
 * @param password The password of the user.
 */
void VikingService::loadSimBalance(const QString& username, const QString& password, const QString& msisdn) const {
    QUrl url("https://mobilevikings.com/api/2.0/basic/sim_balance.json");

    if(msisdn != "") {
        url.addQueryItem("msisdn", msisdn);
    }

    QNetworkRequest request;
    request.setRawHeader("Authorization", "Basic " + this->createAuthToken(username, password));
    request.setUrl(url);

    this->networkSimManager->get(request);
}

void VikingService::loadUsage(const QString& username, const QString& password, const QString& msisdn) const {
    QDateTime now = QDateTime::currentDateTime();
    QDateTime weekAgo = now.addDays(-5);
    QDateTime tomorrow = now.addDays(1);

    QString fromDate = weekAgo.toString("yyyy-MM-ddT00:00:00");
    QString untilDate = tomorrow.toString("yyyy-MM-ddT00:00:00");

    QUrl url("https://mobilevikings.com/api/2.0/basic/usage.json");
    url.addQueryItem("page_size", QString::number(1000));
    url.addQueryItem("from_date", fromDate);
    url.addQueryItem("until_date", untilDate);

    if(msisdn != "") {
        url.addQueryItem("msisdn", msisdn);
    }

    QNetworkRequest request;
    request.setRawHeader("Authorization", "Basic " + this->createAuthToken(username, password));
    request.setUrl(url);

    this->networkUsageManager->get(request);
}

void VikingService::loadTopupHistory(const QString& username, const QString& password, const QString& msisdn) const {
    QUrl url("https://mobilevikings.com/api/2.0/basic/top_up_history.json");

    if(msisdn != "") {
        url.addQueryItem("msisdn", msisdn);
    }

    QNetworkRequest request;
    request.setRawHeader("Authorization", "Basic " + this->createAuthToken(username, password));
    request.setUrl(url);

    this->networkTopupManager->get(request);
}

void VikingService::loadPoints(const QString& username, const QString& password, const QString& msisdn) const {
    QUrl url("https://mobilevikings.com/api/2.0/basic/points/stats.json");

    if(msisdn != "") {
        url.addQueryItem("msisdn", msisdn);
    }

    QNetworkRequest request;
    request.setRawHeader("Authorization", "Basic " + this->createAuthToken(username, password));
    request.setUrl(url);

    this->networkPointsManager->get(request);
}

void VikingService::msisdnLoaded(QNetworkReply* reply) {
    qDebug() << "VikingService::msisdnLoaded";

    QList<Msisdn*> list;

    if(reply->error() == QNetworkReply::NoError) {
        const QByteArray result(reply->readAll());

        JsonDataAccess jda;

        QVariantList dataList = jda.loadFromBuffer(result).toList();

        Q_FOREACH(const QVariant& d, dataList) {
            QVariantMap data = d.value<QVariantMap>();

            QString msisdn = data.value("msisdn").toString();
            QString alias = data.value("alias").toString();

            list.append(new Msisdn(msisdn, alias));
        }

        emit msisdnCompleted("", list);
    }
    else {
        if(reply->error() == QNetworkReply::AuthenticationRequiredError) {
            emit msisdnCompleted("NO_AUTH", list);
        }
        else if(reply->error() == QNetworkReply::HostNotFoundError) {
            emit msisdnCompleted(tr("No network available."), list);
        }
        else {
            emit msisdnCompleted(tr("An error occurred while retrieving your sim balance."), list);
        }
    }
}

void VikingService::simBalanceLoaded(QNetworkReply* reply) {
    qDebug() << "VikingService::simBalanceLoaded";

    if(reply->error() == QNetworkReply::NoError) {
        const QByteArray result(reply->readAll());

        JsonDataAccess jda;

        QVariantMap dataMap = jda.loadFromBuffer(result).toMap();

        QDateTime validUntil = dataMap.value("valid_until").toDateTime();
        double credits = dataMap.value("credits").toDouble();
        bool expired = dataMap.value("is_expired").toBool();
        int sms = dataMap.value("sms").toInt();
        int smsSuperOnNet = dataMap.value("sms_super_on_net").toInt();
        int smsSuperOnNetMax = dataMap.value("sms_super_on_net_max").toInt();
        int voiceSuperOnNet = dataMap.value("voice_super_on_net").toInt();
        int voiceSuperOnNetMax = dataMap.value("voice_super_on_net_max").toInt();
        double data = dataMap.value("data").toDouble();

        SimBalance* balance = new SimBalance();
        balance->setValidUntil(validUntil);
        balance->setCredits(credits);
        balance->setExpired(expired);
        balance->setSms(sms);
        balance->setSmsSuperOnNet(smsSuperOnNet);
        balance->setSmsSuperOnNetMax(smsSuperOnNetMax);
        balance->setVoiceSuperOnNet(voiceSuperOnNet);
        balance->setVoiceSuperOnNetMax(voiceSuperOnNetMax);
        balance->setData(data);

        emit simBalanceCompleted("", balance);
    }
    else {
        if(reply->error() == QNetworkReply::AuthenticationRequiredError) {
            emit simBalanceCompleted("NO_AUTH", NULL);
        }
        else if(reply->error() == QNetworkReply::HostNotFoundError) {
            emit simBalanceCompleted(tr("No network available."), NULL);
        }
        else {
            emit simBalanceCompleted(tr("An error occurred while retrieving your sim balance."), NULL);
        }
    }
}

void VikingService::usageLoaded(QNetworkReply* reply) {
    qDebug() << "VikingService::usageLoaded";

    QList<Usage*> resultList;

    if(reply->error() == QNetworkReply::NoError) {
        const QByteArray result(reply->readAll());

        JsonDataAccess jda;

        QVariantList list = jda.loadFromBuffer(result).toList();

        ContactService contactService;

        ContactSearchFilters filter;
        filter.setLimit(1);

        Contact emptyContact;

        Q_FOREACH(const QVariant &u, list) {
            QVariantMap data = u.value<QVariantMap>();

            Usage* usage = new Usage();
            usage->setStart(data.value("start_timestamp").toDateTime());
            usage->setEnd(data.value("end_timestamp").toDateTime());
            usage->setPrice(data.value("price").toDouble());
            usage->setTo(data.value("to").toString());
            usage->setCallDuration(data.value("duration_call").toInt());
            usage->setConnectionDuration(data.value("duration_connection").toInt());
            usage->setSuperOnNet(data.value("is_super_on_net").toBool());
            usage->setIncoming(data.value("is_incoming").toBool());

            if(data.value("is_sms").toBool()) usage->setType(SMS);
            else if(data.value("is_mms").toBool()) usage->setType(MMS);
            else if(data.value("is_voice").toBool()) usage->setType(VOICE);
            else if(data.value("is_data").toBool()) usage->setType(DATA);

            if(usage->getType() != DATA) {
                QString number = usage->getTo();

                if(phoneCache.contains(number)) {
                    usage->setContact(phoneCache.value(number));
                }
                else if(number == "9997") {
                    usage->setTo(tr("Voicemail"));
                }
                else if(number == "") {
                    usage->setTo(tr("Onbekend nummer"));
                }
                else {
                    filter.setSearchValue(number);

                    QList<Contact> contactList = contactService.searchContactsByPhoneNumber(filter);

                    if(contactList.size() > 0) {
                        phoneCache.insert(number, contactList.at(0));

                        usage->setContact(contactList.at(0));
                    }
                    else {
                        phoneCache.insert(number, emptyContact);
                    }
                }
            }

            resultList.append(usage);
        }

        emit usageCompleted("", resultList);
    }
    else {
        if(reply->error() == QNetworkReply::AuthenticationRequiredError) {
            emit usageCompleted("NO_AUTH", resultList);
        }
        else if(reply->error() == QNetworkReply::HostNotFoundError) {
            emit usageCompleted(tr("No network available."), resultList);
        }
        else {
            emit usageCompleted(tr("An error occurred while retrieving your usage."), resultList);
        }
    }
}

void VikingService::topupHistoryLoaded(QNetworkReply* reply) {
    qDebug() << "VikingService::topupHistoryLoaded";

    QList<TopupHistory*> resultList;

    if(reply->error() == QNetworkReply::NoError) {
        const QByteArray result(reply->readAll());

        JsonDataAccess jda;

        QVariantList list = jda.loadFromBuffer(result).toList();

        Q_FOREACH(const QVariant &topup, list) {
            QVariantMap data = topup.value<QVariantMap>();

            TopupHistory* history = new TopupHistory();
            history->setAmount(data.value("amount").toDouble());
            history->setAmountExVat(data.value("amount_ex_vat").toDouble());
            history->setStatus(data.value("status").toString());
            history->setPaymentMethod(data.value("method").toString());
            history->setExecutedOn(data.value("executed_on").toDateTime());
            history->setPaymentReceivedOn(data.value("payment_received_on").toDateTime());

            resultList.append(history);
        }

        emit topupHistoryCompleted("", resultList);
    }
    else {
        if(reply->error() == QNetworkReply::AuthenticationRequiredError) {
            emit topupHistoryCompleted("NO_AUTH", resultList);
        }
        else if(reply->error() == QNetworkReply::HostNotFoundError) {
            emit topupHistoryCompleted(tr("No network available."), resultList);
        }
        else {
            emit topupHistoryCompleted(tr("An error occurred while retrieving your top up history."), resultList);
        }
    }
}

void VikingService::pointsLoaded(QNetworkReply* reply) {
    qDebug() << "VikingService::pointsLoaded";

    if(reply->error() == QNetworkReply::NoError) {
        const QByteArray result(reply->readAll());

        JsonDataAccess jda;

        QVariantMap dataMap = jda.loadFromBuffer(result).toMap();

        VikingPoints* points = new VikingPoints();
        points->setUsedPoints(dataMap.value("used_points").toInt());
        points->setUnusedPoints(dataMap.value("unused_points").toInt());
        points->setWaitingPoints(dataMap.value("waiting_points").toInt());
        points->setEarnedPoints(dataMap.value("earned_points").toInt());
        points->setUsedTopups(dataMap.value("topups_used").toInt());

        emit vikingPointsCompleted("", points);
    }
    else {
        if(reply->error() == QNetworkReply::AuthenticationRequiredError) {
            emit vikingPointsCompleted("NO_AUTH", NULL);
        }
        else if(reply->error() == QNetworkReply::HostNotFoundError) {
            emit vikingPointsCompleted(tr("No network available."), NULL);
        }
        else {
            emit vikingPointsCompleted(tr("An error occured while retrieving your vikingpoints."), NULL);
        }
    }
}

QByteArray VikingService::createAuthToken(const QString& username, const QString& password) const {
    return QByteArray(QString("%1:%2").arg(username).arg(password).toAscii()).toBase64();
}
