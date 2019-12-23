#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"

#include <string>
#include <vector>
 
class Object;
class Actor;
class Goodie;
class Projectile;
class Alien;
class NachenBlaster;


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
	virtual ~StudentWorld() { cleanUp(); }
    virtual int init();
    virtual int move();
    virtual void cleanUp();
	bool NachenInRange(Actor* OPT);

	bool CollisionWithAlien(Actor*OPT);
	bool CollisionWithNachen(Actor*OPT);
	void healNB(double amt); //suffering negative damage heals the actor
	void addTorpedo();
	void shootCabbage(double startX, double startY);
	void spawnExplosion(double startX, double startY);
	bool handleCollision(Actor* Dealer, Actor* taker);
	void shootTorpedo(double startX, double startY, int faction);
	void shootTurnip(double startX, double startY);

	void spawnExtraLife(double startX, double startY);
	void spawnRepair(double startX, double startY);
	void spawnTorpedoG(double startX, double startY);
	

private:
	//User is responsible for specifying starting Xcoord
	void addStar(std::vector<Actor*>& stars, int Xcoord);
	std::vector<Actor*> actors;
	Alien* tester;
	int aliensDestroyed=0;
	int aliensNeededtoContinue=1;
	NachenBlaster* NB;
	int score = 0;

};

#endif // STUDENTWORLD_H_
