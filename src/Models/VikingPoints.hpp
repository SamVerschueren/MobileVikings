/*
 * VikingPoints.hpp
 *
 * Created on: 25-jun.-2013
 * Author: Sam Verschueren      <sam.verschueren@gmail.com>
 */

#ifndef VIKINGPOINTS_HPP_
#define VIKINGPOINTS_HPP_

class VikingPoints {

    private:
        int usedPoints;
        int unusedPoints;
        int earnedPoints;
        int waitingPoints;

        int usedTopups;


    public:
        VikingPoints();

        int getUsedPoints() const;
        void setUsedPoints(int usedPoints);

        int getUnusedPoints() const;
        void setUnusedPoints(int unusedPoints);

        int getEarnedPoints() const;
        void setEarnedPoints(int earnedPoints);

        int getWaitingPoints() const;
        void setWaitingPoints(int waitingPoints);

        int getUsedTopups() const;
        void setUsedTopups(int usedTopups);
};

#endif /* VIKINGPOINTS_HPP_ */
