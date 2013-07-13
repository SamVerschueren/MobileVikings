/*
 * LoginService.hpp
 *
 * A service is a class that knows how to interact with files or webservices.
 * The ViewModel does not need to know how this stuff is done. He only
 * needs to know that he can call this service in order to execute the
 * login command. This concept is called seperation of concerns.
 *
 * Created on: 25-feb.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */
#ifndef LOGINSERVICE_HPP_
#define LOGINSERVICE_HPP_

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

class LoginService : public QObject {
    Q_OBJECT

    signals:
        void loginCompleted(const QString &message);

    private:
        QNetworkAccessManager *networkAccessManager;

    public:
        LoginService(QObject *parent);
        ~LoginService();

        void login(const QString &username, const QString &password);

    private slots:
        void requestFinished(QNetworkReply *reply);
};

#endif /* LOGINSERVICE_HPP_ */
