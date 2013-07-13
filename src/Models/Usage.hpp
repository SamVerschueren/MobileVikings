/*
 * Usage.hpp
 *
 * Created on: 27-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef USAGE_HPP_
#define USAGE_HPP_

#include <QDateTime>

#include "UsageType.hpp"

class Usage {

    private:
        QDateTime start;
        QDateTime end;
        QString to;
        double price;
        int callDuration;
        int connectionDuration;
        bool incoming;
        bool superOnNet;
        UsageType type;

    public:
        Usage();

        void setStart(const QDateTime& start);
        QDateTime getStart() const;

        void setEnd(const QDateTime& end);
        QDateTime getEnd() const;

        void setTo(const QString& to);
        QString getTo() const;

        void setPrice(double price);
        double getPrice() const;

        void setCallDuration(int callDuration);
        int getCallDuration() const;

        void setConnectionDuration(int connectionDuration);
        int getConnectionDuration() const;

        void setIncoming(bool incoming);
        bool isIncoming() const;

        void setSuperOnNet(bool superOnNet);
        bool isSuperOnNet() const;

        void setType(const UsageType& type);
        UsageType getType() const;
};

#endif /* USAGE_HPP_ */
