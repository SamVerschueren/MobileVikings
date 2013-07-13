/*
 * Msisdn.hpp
 *
 * Created on: 4-jul.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef MSISDN_HPP_
#define MSISDN_HPP_

#include "SimBalance.hpp"
#include "Usage.hpp"
#include "TopupHistory.hpp"
#include "VikingPoints.hpp"

class Msisdn {

    private:
        QString msisdn;
        QString alias;

    public:
        Msisdn(const QString& msisdn, const QString& alias);
        ~Msisdn();

        void setMsisdn(const QString& msisdn);
        QString getMsisdn() const;

        void setAlias(const QString& alias);
        QString getAlias() const;
};

#endif /* MSISDN_HPP_ */
