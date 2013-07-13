/*
 * MainViewModel.cpp
 *
 * Created on: 22-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include "MainViewModel.hpp"

/**
 * Creates a new instance of the <em>MainViewModel</em>.
 */
MainViewModel::MainViewModel() {
    this->settings = new QSettings("samver", "bbVikings", this);

    this->msisdnDataModel = new GroupDataModel();
    this->msisdnDataModel->setGrouping(ItemGrouping::None);
}

/**
 * Cleans up the memory by deleting all dynamically created objects.
 */
MainViewModel::~MainViewModel() {
    delete settings;
}

void MainViewModel::setService(VikingService* service) {
    this->service = service;

    connect(this->service, SIGNAL(msisdnCompleted(QString, QList<Msisdn*>)), this, SLOT(msisdnsLoaded(QString, QList<Msisdn*>)));
}

/**
 * Returns whether the user allready is signed in or not.
 *
 * @returns bool True if there are credentials stored in the settings object, false otherwhise.
 */
bool MainViewModel::hasCredentials() const {
    return this->settings->contains("username") && this->settings->contains("password");
}

GroupDataModel* MainViewModel::getDataModel() const {
    return this->msisdnDataModel;
}

void MainViewModel::msisdnsLoaded(const QString& message, const QList<Msisdn*>& msisdns) {
    qDebug() << "MainViewModel::msisdnsLoaded";

    this->msisdnDataModel->clear();

    QString msisdnSetting = this->settings->value("msisdn", "").toString();

    Q_FOREACH(const Msisdn* msisdn, msisdns) {
        MsisdnViewModel* vm = new MsisdnViewModel(msisdn);

        if(this->msisdnDataModel->size() == 0) {
            this->selectedMsisdn = vm;
        }
        else if(vm->getMsisdn() == msisdnSetting) {
            this->selectedMsisdn = vm;
        }

        this->msisdnDataModel->insert(vm);
    }

    emit titleChanged(this->getTitle());

    this->selectedMsisdn->setSelected(true);

    emit dataModelChanged(this->msisdnDataModel);
}

MsisdnViewModel* MainViewModel::getSelectedMsisdn() const {
    return this->selectedMsisdn;
}

QString MainViewModel::getTitle() const {
    if(this->selectedMsisdn) {
        return this->selectedMsisdn->getAlias();
    }

    return "Mobile Vikings";
}

/**
 * When the user presses the signout menuitem in the global menu of the application,
 * this method will be called. It will remove all the data in the settings object en it will
 * emit the signOutCompleted signal.
 */
Q_INVOKABLE void MainViewModel::signOut() {
    this->settings->clear();

    this->selectedMsisdn = 0;

    emit titleChanged(this->getTitle());

    emit signOutCompleted();
}

Q_INVOKABLE void MainViewModel::loadMsisdn() {
    this->service->loadMsisdn(this->settings->value("username", "").toString(), this->settings->value("password", "").toString());
}

Q_INVOKABLE void MainViewModel::selectMsisdn(const QVariantList& indexPath) {
    qDebug() << "MainViewModel::selectMsisdn";

    QObject* obj = qvariant_cast<QObject *>(this->msisdnDataModel->data(indexPath));

    MsisdnViewModel* temp = qobject_cast<MsisdnViewModel*>(obj);

    if(temp != this->selectedMsisdn) {
        this->selectedMsisdn->setSelected(false);

        this->selectedMsisdn = temp;
        this->selectedMsisdn->setSelected(true);

        this->settings->setValue("msisdn", this->selectedMsisdn->getMsisdn());

        emit titleChanged(this->getTitle());
        emit msisdnChanged(this->selectedMsisdn->getMsisdn());
    }
}
