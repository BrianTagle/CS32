#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;


class Actor : public GraphObject {
public:
	Actor(StudentWorld* pt, int imageID, double startX, double startY, Direction dir = 0, double size = 1.0, unsigned int depth = 0);
	virtual ~Actor() {}
	virtual void doSomething() = 0;
	StudentWorld* getWorld() const { return m_studentworld; }
	double getHealth() const { return m_hp; }
	void setHealth(double healthValue) { m_hp = healthValue; }
	void sufferDamage(double hp) { m_hp -= hp; }
	//check if the object is alive
	bool isAlive() const;
	//change the state of the object to dead
	void setDead();
	//returns whether the object is hostile or not
	virtual bool isHostile() { return false; }
	
	//returns the damage
	double getDamage() const{ return m_damage; }	
	
	int getObjectScore() const { return m_score; }
	virtual bool GoodieAction() { return false; }
	//by default the actor is not a gon alien
	virtual bool isGon() { return false; }
	//by default an actors is not a projectile
	virtual bool isProjectile() { return false; }
protected:
	//changes the damage, usually used in constructors so we dont have to pass an extra parameter
	void setDamage(double damage) { m_damage = damage; }
	//changes the score an object will give the player when a certain action is performed
	void setObjectScore(int amt) { m_score = amt; }
	
private:
	double m_hp;
	StudentWorld* m_studentworld;
	// true is alive, false is dead
	bool m_lifeStatus;
	//the damage an actor will do when colliding with specific other actors
	double m_damage=0;
	//the amount of score the player will recieve when something happeneds to the specified object.  THIS IS NOT THE PLAYER SCORE
	int m_score = 0;
};
class Explosion : public Actor {
public:
	Explosion(StudentWorld* pt, double startX, double startY, int imageID =IID_EXPLOSION, Direction dir = 0, double size = 1.0, unsigned int depth = 0);
	virtual ~Explosion() {}
	virtual void doSomething();
private:
	int m_lifeTimer;
};
class NachenBlaster : public Actor {
public:
	NachenBlaster(StudentWorld* pt, int imageID = IID_NACHENBLASTER, double startX = 0, double startY = 128, Direction dir = 0,
		double size = 1.0, unsigned int depth = 0);
	virtual ~NachenBlaster() {}
	virtual void doSomething();
	int getCabbagePoints() const{ return m_CabbagePoints; } 
	int getTorpedoCount() const { return m_torpedoCount; } 
	void increaseTorpedoCount() { m_torpedoCount+=5; }
	
private:
	int m_CabbagePoints;
	int m_torpedoCount;
};
class Projectile :public Actor {
public:
	Projectile(StudentWorld * pt, double startX, double startY, int imageID, Direction dir = 0, double size = 1.0, unsigned int depth = 0);
	virtual ~Projectile() {}
	virtual void doSomething();
	virtual void specificMove() = 0;
	virtual bool isProjectile() { return true; }
	
private:
	
	
};
class Goodie : public Actor {
public:
	Goodie(StudentWorld* pt, double startX, double startY, int imageID , Direction dir = 0, double size = .5, unsigned int depth = 1);
	virtual ~Goodie() {}
	virtual void doSomething();
	virtual void benefit() = 0;
	
private:
};
class Alien : public Actor {
public:
	Alien(StudentWorld * pt, int imageID , double startX , double startY , Direction dir = 0, 
		double size = 1.5, unsigned int depth = 1,  int FlightPathLength = 0, double Speed = 1);
	virtual ~Alien() {}
	virtual void doSomething();
	virtual bool specialAction() = 0;
	
	
	//returns that the alien is hostile
	virtual bool isHostile() { return true; }
	//all aliens are gons
	virtual bool isGon() { return true; }

protected:
	//move in the specificed direction with the specified speed
	void moveInDirection();

	//change the flight path length
	void setFPL(int newFPL) { m_FPL = newFPL; }
	//change the current flight Direction
	void setFlightDirection(int newDirection) { m_flightDirection = newDirection; }

	//changes the speed
	void setSpeed(double speed) { m_travelSpeed = speed; }
	
private:
	//flight plan length
	int m_FPL;
	//number of pixels the ship will move per tick
	double m_travelSpeed;
	//the direction of flight, values range from -1 to 1
	int m_flightDirection;
	
};
class Star : public Actor {
public:
	Star(StudentWorld* pt, int imageID, double startX, double startY, Direction dir = 0, double size = 1.0, unsigned int depth = 3);
	virtual ~Star() {}
	virtual void doSomething();
	
};
class Cabbage:public Projectile {
public:
	Cabbage(StudentWorld * pt, double startX, double startY,  int imageID = IID_CABBAGE, Direction dir = 0, double size = .5, unsigned int depth = 1);
	virtual ~Cabbage() {}
	virtual void specificMove() ;
	virtual bool isHostile() { return false; }
private:

};
class Turnip :public Projectile {
public:
	Turnip(StudentWorld * pt, double startX, double startY, int imageID = IID_TURNIP, Direction dir = 0, double size = .5, unsigned int depth = 1);
	virtual ~Turnip() {}
	virtual void specificMove() ;
	virtual bool isHostile() { return true; }
private:
};
class Torpedo : public Projectile {
public:
	Torpedo(StudentWorld * pt, double startX, double startY, int FACTION = 1, int imageID = IID_TORPEDO, Direction dir = 0, double size = .5, unsigned int depth = 1);
	virtual ~Torpedo() {}
	virtual void specificMove();
	virtual bool isHostile();
private:
	int m_faction;
};

class ExtraLifeGoodie : public Goodie {
public:
	ExtraLifeGoodie(StudentWorld* pt, double startX, double startY, int imageID = IID_LIFE_GOODIE, Direction dir = 0, double size = .5, unsigned int depth = 1);
	virtual ~ExtraLifeGoodie() {}
	virtual void benefit();
private:
};
class RepairGoodie : public Goodie {
public:
	RepairGoodie(StudentWorld* pt, double startX, double startY, int imageID = IID_REPAIR_GOODIE, Direction dir = 0, double size = .5, unsigned int depth = 1);
	virtual ~RepairGoodie() {}
	virtual void benefit();
private:
};
class TorpedoGoodie :public Goodie {
public:
	TorpedoGoodie(StudentWorld* pt, double startX, double startY, int imageID = IID_TORPEDO_GOODIE, Direction dir = 0, double size = .5, unsigned int depth = 1);
	virtual ~TorpedoGoodie(){}
	virtual void benefit();
private:
};

class Smallgon :public Alien {
public:
	Smallgon(StudentWorld * pt, double startX, double startY, int imageID = IID_SMALLGON, Direction dir = 0,
		double size = 1.5, unsigned int depth = 1, int FlightPathLength = 0, double Speed = 2);
	virtual ~Smallgon(){}
	
	virtual bool specialAction();
	//smallgon currently doesnt drop any goodies
	virtual bool GoodieAction(); 
private:
};
class Smoregon : public Alien {
public:
	Smoregon(StudentWorld * pt, double startX, double startY,  int imageID = IID_SMOREGON, Direction dir = 0,
		double size = 1.5, unsigned int depth = 1, int FlightPathLength = 0, double Speed = 2);
	virtual ~Smoregon() {}
	virtual bool specialAction();
	//possibly drop a torpedo or a repair goodie
	virtual bool GoodieAction(); 
private:
};
class Snagglegon:public Alien {
public:
	Snagglegon(StudentWorld * pt, double startX, double startY, int imageID = IID_SNAGGLEGON, Direction dir = 0,
		double size = 1.5, unsigned int depth = 1, int FlightPathLength = VIEW_HEIGHT+VIEW_WIDTH, double Speed = 1.75);
	virtual ~Snagglegon() {}
	virtual bool specialAction();
	//possible drop an extra life
	virtual bool GoodieAction(); 
private:
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
