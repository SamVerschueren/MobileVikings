/*
 * LoginViewModel.hpp
 *
 * The header file for the LoginViewModel. This provides the contract for the
 * implementation of the ViewModel. This model is the abstraction of the
 * login view.
 *
 * The property username and password are binded to the apropriate textfields and
 * the login method is executed when the login button is clicked.
 *
 * Created on: 11-feb.-2013
 * Author: Sam Verschueren        <sam.verschueren@gmail.com>
 */

#ifndef LOGINVIEWMODEL_HPP_
#define LOGINVIEWMODEL_HPP_

#include <QObject>
#include <QSettings>
#include "LoginService.hpp"

class LoginViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString username WRITE setUsername NOTIFY usernameChanged FINAL)
    Q_PROPERTY(QString password WRITE setPassword NOTIFY passwordChanged FINAL)

    Q_SIGNALS:
        void usernameChanged(const QString &username);
        void passwordChanged(const QString &password);

    signals:
        // This signal will be emitted when the login action is completed
        void loginCompleted(bool result, const QString &message);

    public slots:
        void loginServiceCompleted(const QString &message);

    private:
        QString username;
        QString password;

        QSettings *settings;
        LoginService *loginService;

    public:
        LoginViewModel();
        ~LoginViewModel();

        void setUsername(const QString &username);
        void setPassword(const QString &password);

        Q_INVOKABLE void login();
};

#endif /* LOGINVIEWMODEL_HPP_ */
