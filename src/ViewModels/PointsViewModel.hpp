/*
 * PointsViewModel.hpp
 *
 * Created on: 25-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef POINTSVIEWMODEL_HPP_
#define POINTSVIEWMODEL_HPP_

#include <QObject>
#include <QSettings>

#include "VikingService.hpp"

class PointsViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(VikingService* service WRITE setService FINAL)

    Q_PROPERTY(int usedPoints READ getUsedPoints NOTIFY usedPointsChanged FINAL)
    Q_PROPERTY(int unusedPoints READ getUnusedPoints NOTIFY unusedPointsChanged FINAL)
    Q_PROPERTY(int waitingPoints READ getWaitingPoints NOTIFY waitingPointsChanged FINAL)
    Q_PROPERTY(int earnedPoints READ getEarnedPoints NOTIFY earnedPointsChanged FINAL)
    Q_PROPERTY(int usedTopups READ getUsedTopups NOTIFY usedTopupsChanged FINAL)

    Q_SIGNALS:
        void usedPointsChanged(int usedPoints);
        void unusedPointsChanged(int unusedPoints);
        void waitingPointsChanged(int waitingPoints);
        void earnedPointsChanged(int earnedPoints);
        void usedTopupsChanged(int usedTopups);

    private:
        QSettings* settings;
        VikingService* service;

        bool loaded;

        // properties
        int usedPoints;
        int unusedPoints;
        int waitingPoints;
        int earnedPoints;
        int usedTopups;

    public:
        PointsViewModel();
        ~PointsViewModel();

        void setService(VikingService* service);

        int getUsedPoints() const;
        int getUnusedPoints() const;
        int getWaitingPoints() const;
        int getEarnedPoints() const;
        int getUsedTopups() const;

        Q_INVOKABLE void loadVikingPoints();
        Q_INVOKABLE void reset();

    private slots:
        void vikingPointsLoaded(const QString& message, VikingPoints* points);

    signals:
        void loadCompleted(const QString& message);
};

#endif /* POINTSVIEWMODEL_HPP_ */
