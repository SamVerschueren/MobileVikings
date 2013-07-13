/*
 * SimBalance.cpp
 *
 * Created on: 10-mei-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include "SimBalance.hpp"

SimBalance::SimBalance() {

}

QDateTime SimBalance::getValidUntil() const {
    return this->validUntil;
}

void SimBalance::setValidUntil(const QDateTime &dateTime) {
    this->validUntil = dateTime;
}

double SimBalance::getCredits() const {
    return this->credits;
}

void SimBalance::setCredits(double credits) {
    this->credits = credits;
}

bool SimBalance::isExpired() const {
    return this->expired;
}

void SimBalance::setExpired(bool expired) {
    this->expired = expired;
}

int SimBalance::getSms() const {
    return this->sms;
}

void SimBalance::setSms(int sms) {
    this->sms = sms;
}

int SimBalance::getSmsSuperOnNet() const {
    return this->smsSuperOnNet;
}

void SimBalance::setSmsSuperOnNet(int smsSuperOnNet) {
    this->smsSuperOnNet = smsSuperOnNet;
}

int SimBalance::getSmsSuperOnNetMax() const {
    return this->smsSuperOnNetMax;
}

void SimBalance::setSmsSuperOnNetMax(int smsSuperOnNetMax) {
    this->smsSuperOnNetMax = smsSuperOnNetMax;
}

int SimBalance::getVoiceSuperOnNet() const {
    return this->voiceSuperOnNet;
}

void SimBalance::setVoiceSuperOnNet(int voiceSuperOnNet) {
    this->voiceSuperOnNet = voiceSuperOnNet;
}

int SimBalance::getVoiceSuperOnNetMax() const {
    return this->voiceSuperOnNetMax;
}

void SimBalance::setVoiceSuperOnNetMax(int voiceSuperOnNetMax) {
    this->voiceSuperOnNetMax = voiceSuperOnNetMax;
}

double SimBalance::getData() const {
    return this->data;
}

void SimBalance::setData(double data) {
    this->data = data;
}


