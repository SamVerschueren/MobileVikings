/*
 * VikingPoints.cpp
 *
 * Created on: 25-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#include "VikingPoints.hpp"

VikingPoints::VikingPoints() {

}

int VikingPoints::getUsedPoints() const {
    return this->usedPoints;
}

void VikingPoints::setUsedPoints(int usedPoints) {
    this->usedPoints = usedPoints;
}

int VikingPoints::getUnusedPoints() const {
    return this->unusedPoints;
}

void VikingPoints::setUnusedPoints(int unusedPoints) {
    this->unusedPoints = unusedPoints;
}

int VikingPoints::getEarnedPoints() const {
    return this->earnedPoints;
}

void VikingPoints::setEarnedPoints(int earnedPoints) {
    this->earnedPoints = earnedPoints;
}

int VikingPoints::getWaitingPoints() const {
    return this->waitingPoints;
}

void VikingPoints::setWaitingPoints(int waitingPoints) {
    this->waitingPoints = waitingPoints;
}

int VikingPoints::getUsedTopups() const {
    return this->usedTopups;
}

void VikingPoints::setUsedTopups(int usedTopups) {
    this->usedTopups = usedTopups;
}
