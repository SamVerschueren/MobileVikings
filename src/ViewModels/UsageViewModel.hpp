/*
 * UsageViewModel.hpp
 *
 * Created on: 28-jun.-2013
 * Author: Sam Verschueren
 */

#ifndef USAGEVIEWMODEL_HPP_
#define USAGEVIEWMODEL_HPP_

#include <QObject>
#include <QDateTime>
#include <bb/cascades/Invocation>
#include <bb/cascades/InvokeQuery>
#include <bb/system/Clipboard>
#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>

#include "Usage.hpp"
using namespace bb::cascades;
using namespace bb::system;

class UsageViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QDateTime start READ getStart FINAL)
    Q_PROPERTY(QDate day READ getDay FINAL)
    Q_PROPERTY(QString duration READ getDuration FINAL)
    Q_PROPERTY(QString to READ getTo FINAL)
    Q_PROPERTY(QString price READ getPrice FINAL)
    Q_PROPERTY(QString statusImage READ getStatusImage FINAL)
    Q_PROPERTY(QString contact READ getContact FINAL)
    Q_PROPERTY(int contactId READ getContactId FINAL)

    private:
        QDateTime start;
        QDate day;
        QString duration;
        QString to;
        QString price;
        QString statusImage;
        QString contact;
        int contactId;

        Invocation* telInvocation;
        InvokeManager* invokeManager;

    public:
        UsageViewModel(Usage* usage);
        ~UsageViewModel();

        QDateTime getStart() const;
        QDate getDay() const;
        QString getDuration() const;
        QString getTo() const;
        QString getPrice() const;
        QString getStatusImage() const;
        QString getContact() const;
        int getContactId() const;

        Q_INVOKABLE void sendText() const;
        Q_INVOKABLE void call() const;
        Q_INVOKABLE void viewOrAddContact() const;
        Q_INVOKABLE void copyNumber() const;
};

#endif /* USAGEVIEWMODEL_HPP_ */
