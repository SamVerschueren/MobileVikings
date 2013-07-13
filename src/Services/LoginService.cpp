/*
 * LoginService.cpp
 *
 * The implementation of the data service. For more information on this
 * class, please look at the header file.
 *
 * Created on: 25-feb.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include "LoginService.hpp"

/**
 * Creates a new instance of this data service.
 */
LoginService::LoginService(QObject *parent=0) : QObject(parent) {
    this->networkAccessManager = new QNetworkAccessManager(this);

    // Connect with the finished signal of the networkAccessManager
    connect(this->networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
}

/**
 * Destroys objects that are dynamically created. For example when we use
 * a <em>NetworkAccessManager</em> we will delete him in this destructor.
 */
LoginService::~LoginService() {
    delete networkAccessManager;
}

/**
 * This method is called in the <em>LoginViewModel</em> and knows how
 * to check the credentials of the user. When the login is completed, the
 * loginCompleted signal is emitted. If the login was succesfull, no message
 * is provided, otherwhise an errormessage will be send with it.
 *
 * @param The username of the login attempt.
 * @param The password of the login attempt.
 */
void LoginService::login(const QString &username, const QString &password) {
    QNetworkRequest request;
    request.setRawHeader("Authorization", "Basic " + QByteArray(QString("%1:%2").arg(username).arg(password).toAscii()).toBase64());
    request.setUrl(QUrl("https://mobilevikings.com/api/2.0/basic/points/stats.json"));

    networkAccessManager->get(request);
}

/**
 * This slot is connected with the finished signal of the <em>QNetworkAccessManager</em>.
 * When that signal is emitted, this method will be executed.
 *
 * @param reply The reply that the network access manager returns.
 */
void LoginService::requestFinished(QNetworkReply *reply) {
    if(reply->error() == QNetworkReply::NoError) {
        const QByteArray result(reply->readAll());

        qDebug() << result;

        emit loginCompleted("");
    }
    else {
        if(reply->error() == QNetworkReply::AuthenticationRequiredError) {
            emit loginCompleted(tr("Uw aanmeldgegevens zijn niet correct."));
        }
        else {
            emit loginCompleted(tr("Er is geen netwerk beschikbaar."));
        }
    }
}
