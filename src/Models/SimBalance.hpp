/*
 * SimBalance.hpp
 *
 * Created on: 10-mei-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef SIMBALANCE_HPP_
#define SIMBALANCE_HPP_

#include <QDateTime>

class SimBalance {

    private:
        QDateTime validUntil;
        double credits;
        bool expired;
        int sms;
        int smsSuperOnNet;
        int smsSuperOnNetMax;
        int voiceSuperOnNet;
        int voiceSuperOnNetMax;
        double data;

    public:
        SimBalance();

        QDateTime getValidUntil() const;
        void setValidUntil(const QDateTime &dateTime);

        double getCredits() const;
        void setCredits(double credits);

        bool isExpired() const;
        void setExpired(bool expired);

        int getSms() const;
        void setSms(int sms);

        int getSmsSuperOnNet() const;
        void setSmsSuperOnNet(int smsSuperOnNet);

        int getSmsSuperOnNetMax() const;
        void setSmsSuperOnNetMax(int smsSuperOnNetMax);

        int getVoiceSuperOnNet() const;
        void setVoiceSuperOnNet(int voiceSuperOnNet);

        int getVoiceSuperOnNetMax() const;
        void setVoiceSuperOnNetMax(int voiceSuperOnNetMax);

        double getData() const;
        void setData(double data);
};


#endif /* SIMBALANCE_HPP_ */
