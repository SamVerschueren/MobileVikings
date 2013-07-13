/*
 * MsisdnViewModel.hpp
 *
 * Created on: 4-jul.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef MSISDNVIEWMODEL_HPP_
#define MSISDNVIEWMODEL_HPP_

#include <QObject>

#include "Msisdn.hpp"

class MsisdnViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool selected READ isSelected NOTIFY selectionChanged FINAL)
    Q_PROPERTY(QString msisdn READ getMsisdn NOTIFY msisdnChanged FINAL)
    Q_PROPERTY(QString alias READ getAlias NOTIFY aliasChanged FINAL)

    Q_SIGNALS:
        void selectionChanged(bool isSelected);
        void msisdnChanged(const QString& msisdn);
        void aliasChanged(const QString& alias);

    private:
        bool selected;
        QString msisdn;
        QString alias;

        void setMsisdn(const QString& msisdn);
        void setAlias(const QString& alias);

    public:
        MsisdnViewModel(const Msisdn* msisdn);

        QString getMsisdn() const;
        QString getAlias() const;

        void setSelected(bool isSelected);
        bool isSelected() const;
};

#endif /* MSISDNVIEWMODEL_HPP_ */
