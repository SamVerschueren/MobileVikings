/*
 * Usage.cpp
 *
 * Created on: 27-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include "Usage.hpp"

Usage::Usage() {

}

void Usage::setStart(const QDateTime& start) {
    this->start = start;
}

QDateTime Usage::getStart() const {
    return this->start;
}

void Usage::setEnd(const QDateTime& end) {
    this->end = end;
}

QDateTime Usage::getEnd() const {
    return this->end;
}

void Usage::setTo(const QString& to) {
    this->to = to;
}

QString Usage::getTo() const {
    return this->to;
}

void Usage::setPrice(double price) {
    this->price = price;
}

double Usage::getPrice() const {
    return this->price;
}

void Usage::setCallDuration(int callDuration) {
    this->callDuration = callDuration;
}

int Usage::getCallDuration() const {
    return this->callDuration;
}

void Usage::setConnectionDuration(int connectionDuration) {
    this->connectionDuration = connectionDuration;
}

int Usage::getConnectionDuration() const {
    return this->connectionDuration;
}

void Usage::setIncoming(bool incoming) {
    this->incoming = incoming;
}

void Usage::setSuperOnNet(bool superOnNet) {
    this->superOnNet = superOnNet;
}

bool Usage::isSuperOnNet() const {
    return this->superOnNet;
}

bool Usage::isIncoming() const {
    return this->incoming;
}

void Usage::setType(const UsageType& type) {
    this->type = type;
}

UsageType Usage::getType() const {
    return this->type;
}
