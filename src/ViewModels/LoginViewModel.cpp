/*
 * LoginViewModel.cpp
 *
 * This is the implementation of the header file of the LoginViewModel. Look
 * at the header file for more details on this class.
 *
 * Created on: 11-feb.-2013
 * Author: Sam Verschueren        <sam.verschueren@gmail.com>
 */

#include <QDebug>
#include "LoginViewModel.hpp"

/**
 * Creates a new instance of the <em>LoginViewModel</em> and connecting a
 * method to the loginCompleted signal of the <em>LoginService</em>.
 */
LoginViewModel::LoginViewModel() {
    this->settings = new QSettings("samver", "bbVikings", this);

    this->loginService = new LoginService(this);

    connect(this->loginService, SIGNAL(loginCompleted(QString)), this, SLOT(loginServiceCompleted(QString)));
}

/**
 * Cleans up the memory by deleting all dynamically created objects.
 */
LoginViewModel::~LoginViewModel() {
    delete loginService;
    delete settings;
}

/**
 * Sets the username to the value provided. If the new username is something
 * other then the previous username, the username will be updated and the
 * view will be notified by the usernameChanged signal.
 *
 * @param username The username to be set.
 */
void LoginViewModel::setUsername(const QString &username) {
    if(this->username != username) {
        this->username = username;

        emit usernameChanged(username);
    }
}

/**
 * Sets the password to the value provided. If the new password is something
 * other then the previous password, the password will be updated and the
 * view will be notified by the passwordChanged signal.
 *
 * @param password The password to be set.
 */
void LoginViewModel::setPassword(const QString &password) {
    if(this->password != password) {
        this->password = password;

        emit passwordChanged(password);
    }
}

/**
 * This method is connected to the loginCompleted signal of the
 * <em>LoginService</em>. When the service is done checking the credentials,
 * this method will be executed.
 *
 * @param message The message that the service returns. If it's empty, login was succesfull.
 */
void LoginViewModel::loginServiceCompleted(const QString &message) {
    bool result = message=="";

    // If everything went OK, store the credentials in the settings object.
    if(result) {
        this->settings->setValue("username", this->username);
        this->settings->setValue("password", this->password);
    }

    emit loginCompleted(result, message);
}

/**
 * The <em>LoginViewModel</em> does not need to know how the username
 * and password are checked. This is up to the <em>LoginService</em>
 * to do that. The service will get the information from a webservice
 * or just from a file. At this point, I have no idea and I don't need
 * to know it.
 * This method is a Q_INVOKABLE method so it can be bound to the click
 * event of a button.
 */
Q_INVOKABLE void LoginViewModel::login() {
    qDebug() << "LoginViewModel::login";

    loginService->login(this->username, this->password);
}
