#include "Actor.h"
#include "StudentWorld.h"
//#include <cmath>
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

bool Actor::isAlive() const {
	return m_lifeStatus;
}
void Actor::setDead() {
	m_lifeStatus = false;
}




Actor::Actor(StudentWorld* pt, int imageID, double startX, double startY, Direction dir, double size , unsigned int depth) 
	:GraphObject(imageID, startX, startY, dir, size, depth) 
{
	m_lifeStatus = true;
	m_hp = 10; //random bogus value, never actually the real health here
	m_studentworld = pt;
}

Star::Star(StudentWorld* pt, int imageID, double startX, double startY, Direction dir , double size , unsigned int depth )
	:Actor(pt, imageID, startX, startY, dir, size, depth)
{
	
}
void Star::doSomething() {
	if (getX() <= -1) {
		setDead();
	}
	moveTo(getX() - 1, getY());

}
Explosion::Explosion(StudentWorld* pt, double startX, double startY, int imageID , Direction dir, double size , unsigned int depth):Actor(pt,imageID, startX, startY, dir, size, depth) {
	m_lifeTimer = 4;
}
void Explosion::doSomething() {
	if (!isAlive()) {
		return;
	}
	setSize(getSize()*1.5);
	m_lifeTimer--;
	if (m_lifeTimer <= 0) {
		setDead();
	}

}
Projectile::Projectile(StudentWorld * pt, double startX, double startY, int imageID, Direction dir , double size , unsigned int depth )
	:Actor(pt, imageID, startX, startY, dir, size, depth)
{

}
void Projectile::doSomething() {
	if (!isAlive()) { //if the projectile is "dead"
		return;
	}
	if (getX() < 0 || getX()>=VIEW_WIDTH) { // if the projectile has moved off of the screen
		setDead();
		return;
	}
	if (isHostile()) { //if the projectile is hostile to the player
		if (getWorld()->CollisionWithNachen(this)) { //projectile hit the nachenblaster
			setDead();
			return;
		}
	}
	else { //the projectile is friendly to the player
		if (getWorld()->CollisionWithAlien(this)) { //projectile hits an alien
			setDead();
			return;
		}
	}

	specificMove(); //each kind of projectile moves a little different

//check for collisions after the projectile has moved
if (isHostile()) { //if the projectile is hostile to the player
	if (getWorld()->CollisionWithNachen(this)) { //projectile hit the nachenblaster
		setDead();
		return;
	}
}
else { //the projectile is friendly to the player
	if (getWorld()->CollisionWithAlien(this)) { //projectile hits an alien
		setDead();
		return;
	}
}
}

Alien::Alien(StudentWorld * pt, int imageID, double startX, double startY, Direction dir,
	double size, unsigned int depth, int FlightPathLength, double Speed)
	:Actor(pt, imageID, startX, startY, dir, size, depth)
{
	m_FPL = FlightPathLength;
	m_travelSpeed = Speed;
	m_flightDirection = 0;

}
void Alien::moveInDirection() {

	switch (m_flightDirection) {
	case 1: // up left
		moveTo(getX() - m_travelSpeed, getY() + m_travelSpeed);
		break;
	case 0: // left
		moveTo(getX() - m_travelSpeed, getY());
		break;
	case -1: //down left
		moveTo(getX() - m_travelSpeed, getY() - m_travelSpeed);
		break;
	}
}
void Alien::doSomething() {
	if (!isAlive()) { //if the alien is dead, return
		return;
	}
	if (getX() < 0) { // if the alien has moved off the screen, set it to dead and return
		setDead();
		return;
	}
	if (getWorld()->CollisionWithNachen(this)) { // if aliens hits the player ship
		setDead();

		return; //the alien is dead, nothing else should happen
	}

	if (m_FPL <= 0 || getY() <= 0 || getY() >= VIEW_HEIGHT - 1) {//if the ship needs a new flight path, or has reached the top or bottom of the screen

		if (getY() >= VIEW_HEIGHT - 1) { //if the ship is at the top of the screen
			setFlightDirection(-1);
		}
		else if (getY() <= 0) { //if the ship is at the top of the screen
			setFlightDirection(1);
		}
		else if (m_FPL <= 0) {
			int ch = randInt(1, 3);
			switch (ch) {
			case 1: //due left
				setFlightDirection(0);
				break;
			case 2: //up and left
				setFlightDirection(1);
				break;
			case 3: //down and left
				setFlightDirection(-1);
				break;
			}
		}
		if (m_FPL <= 32) { //this statement is so the FPL setter will never change the FPL of the snagglegon who has a a huge FPL to ensure he is always zig zaging
			setFPL(randInt(1, 32));
		}

	}
	if (!specialAction()) { //if the alien doesnt do one of their special abilities, move normally
		moveInDirection(); //move
		setFPL(m_FPL - 1);

	}
	if (getWorld()->CollisionWithNachen(this)) {
		setDead();
		return;
	}
}
Goodie::Goodie(StudentWorld* pt, double startX, double startY, int imageID, Direction dir, double size, unsigned int depth)
	:Actor(pt, imageID, startX, startY, dir, size, depth)
{
	setObjectScore(100);
}
void Goodie::doSomething() {
	if (!isAlive()) {
		return;
	}
	if (getWorld()->CollisionWithNachen(this)){ //first collision check
		benefit();
		return;
	}
	moveTo(getX() - .75, getY() - .75); //move if there is no collison then check again
	if (getWorld()->CollisionWithNachen(this)) { //second collision check
		benefit();
		return;
	}
}

NachenBlaster::NachenBlaster(StudentWorld* pt, int imageID, double startX, double startY, Direction dir, double size, unsigned int depth) 
	:Actor(pt, imageID, startX, startY, dir, size, depth)
{
	setHealth(50);
	m_CabbagePoints = 30;
	m_torpedoCount = 0;
}
void NachenBlaster::doSomething() {

	if (isAlive()) {
		int ch;
		if (getWorld()->getKey(ch)) {
			switch (ch) {
			case KEY_PRESS_SPACE:
				if (m_CabbagePoints >= 5) {
					m_CabbagePoints -= 5;
					getWorld()->shootCabbage(getX()+12, getY());
				}
				break;
			case KEY_PRESS_TAB:
				if (m_torpedoCount > 0) {
					getWorld()->shootTorpedo(getX() + 12, getY(), 1);
					m_torpedoCount--;
				}
				break;
			case KEY_PRESS_LEFT: //move in the negative x direction
				if (getX()  >= 0) { moveTo(getX() - 6, getY()); }
				break;
			case KEY_PRESS_RIGHT: //move in the positive x direction
				if (getX()  < VIEW_WIDTH) { moveTo(getX() + 6, getY()); }
				break;
			case KEY_PRESS_UP: //move in positive y direction
				if (getY() < VIEW_HEIGHT) { moveTo(getX(), getY() + 6); }
				break;
			case KEY_PRESS_DOWN: //move in ngeative y direction
				if (getY() >= 0) { moveTo(getX(), getY() - 6); }
				break;
			}
		}
		if (m_CabbagePoints < 30) {
			m_CabbagePoints++;
		}
	}
}

Smallgon::Smallgon(StudentWorld * pt, double startX, double startY, int imageID , Direction dir ,
	double size , unsigned int depth , int FlightPathLength , double Speed ) 
	:Alien(pt, imageID, startX, startY, dir,size, depth,  FlightPathLength, Speed)
{
	setHealth(5 * (1 + (pt->getLevel() - 1)*.1));
	setDamage(5); //the smallgon does this much damage when it hits the Nachenblaster
	setObjectScore(250);
}
bool Smallgon::specialAction() {
	if (getWorld()->NachenInRange(this)) {
		if (randInt(1, ((20 / getWorld()->getLevel()) + 5)) == 1) { //chance to shoot a turnip
			getWorld()->shootTurnip(getX() - 14, getY());
			return true;// special action taken, notify the alien to ignore next normal movement
		}
	}
	return false; //no speical action performs

}
bool Smallgon::GoodieAction() {
	return false;//no goodie spawned
}

Smoregon::Smoregon(StudentWorld * pt, double startX, double startY,  int imageID, Direction dir,
	double size, unsigned int depth, int FlightPathLength, double Speed)
	:Alien(pt, imageID, startX, startY, dir, size, depth, FlightPathLength, Speed)
{
	setHealth(5 * (1 + (pt->getLevel() - 1)*.1));
	setObjectScore(250);
	setDamage(5); //the smoregon does this much damage when it hits the Nachenblaster
}
bool Smoregon::specialAction() {

	if (getWorld()->NachenInRange(this)) {
		if (randInt(1, ((20 / getWorld()->getLevel()) + 5)) == 1) { //chance to shoot a turnip
			getWorld()->shootTurnip(getX()-14, getY());
			return true;// special action taken, notify the alien to ignore next normal movement
		}
		if (randInt(1, ((20 / getWorld()->getLevel()) + 5)) == 1) { //chance for ramming speed
			setFlightDirection(0); //due left
			setSpeed(5); //faster speed
			setFPL(VIEW_WIDTH); //make sure the FPL will last until it the smoregon dies
			return false; //ramming is not counted as a special action 
		}

	}
	return false; //no special action performed
}
bool Smoregon::GoodieAction() {
	if (randInt(1, 6) == 1) {
		if (randInt(1, 2) == 1) {
			getWorld()->spawnTorpedoG(getX(), getY());
		}
		else {
			getWorld()->spawnRepair(getX(), getY());
		}
		return true; //goodie spawned!
	}
	return false;//no goodie spawned
}

Snagglegon::Snagglegon(StudentWorld* pt, double startX, double startY,  int imageID , Direction dir ,
	double size , unsigned int depth , int FlightPathLength , double Speed ) 
	:Alien(pt, imageID, startX, startY, dir, size, depth,  FlightPathLength, Speed)
{
	setHealth(10 * (1 + (pt->getLevel() - 1)*.1));
	setObjectScore(1000);
	setDamage(15); //the snagglegon does this much damage when it hits the Nachenblaster
	setFlightDirection(-1);//down and left
}
bool Snagglegon::specialAction() {
	if (getWorld()->NachenInRange(this)) {
		if (randInt(1, ((15 / getWorld()->getLevel()) + 10)) == 1) { //chance to shoot a turnip
			getWorld()->shootTorpedo(getX() - 14, getY(), -1);//faction number for the alien is -1, so the studentworld know it is a hostile torpedo
			return true;// special action taken, notify the alien to ignore next normal movement
		}
	}
	return false; //no special action peformed
}
bool Snagglegon::GoodieAction() {
	if (randInt(1, 6) == 1) {
		getWorld()->spawnExtraLife(getX(), getY());
		return true;//goodie spawned!
	}
	return false; //no goodie spawned
}

Cabbage::Cabbage(StudentWorld * pt, double startX, double startY, int imageID, Direction dir,
	double size, unsigned int depth)
	:Projectile(pt, startX, startY,  imageID, dir, size, depth)
{
	setDamage(2); //damage cabage will do
	getWorld()->playSound(SOUND_PLAYER_SHOOT);
}
void Cabbage::specificMove() {
	moveTo(getX()+8, getY());
	setDirection(getDirection() + 20);
}

Turnip::Turnip(StudentWorld * pt, double startX, double startY,  int imageID, Direction dir,
	double size, unsigned int depth)
	: Projectile(pt, startX, startY,  imageID, dir, size, depth)
{
	setDamage(2); //the damage turnip will do if it hits the nachenblaster
	getWorld()->playSound(SOUND_ALIEN_SHOOT);
}
void Turnip::specificMove() {
	moveTo(getX()-6, getY());
	setDirection(getDirection() + 20);
}

Torpedo::Torpedo(StudentWorld * pt, double startX, double startY, int FACTION, int imageID, Direction dir,
	double size, unsigned int depth)
	: Projectile(pt, startX, startY, imageID, dir, size, depth), m_faction(FACTION) 
{
	getWorld()->playSound(SOUND_TORPEDO);
	setDamage(8); //damage torpedo will do
	m_faction = FACTION;
	switch (m_faction) {
	case 1: // the torpedo is friendly to the player
		setDirection(0);
		break;
	case -1: //the torpedo is hostile to the player
		setDirection(180);
		break;
	}
}
bool Torpedo ::isHostile() {
	switch (m_faction) {
	case 1: // the torpedo is friendly to the player
		return false;
		break;
	case -1: //the torpedo is hostile to the player
		return true;
		break;
	}
	return false;
}
void Torpedo::specificMove() {
	if (isHostile()) {
		moveTo(getX()-8, getY());
	}
	else {
		moveTo(getX()+8, getY());
	}
	
}
ExtraLifeGoodie::ExtraLifeGoodie(StudentWorld* pt, double startX, double startY, int imageID, Direction dir, double size, unsigned int depth)
	:Goodie(pt, startX, startY, imageID, dir, size, depth)
{
	
}

void ExtraLifeGoodie::benefit() {
	getWorld()->incLives();
}

RepairGoodie::RepairGoodie(StudentWorld* pt, double startX, double startY, int imageID, Direction dir, double size, unsigned int depth)
	:Goodie(pt, startX, startY, imageID, dir, size, depth)
{

}
void RepairGoodie::benefit() {
	getWorld()->healNB(10);
}

TorpedoGoodie::TorpedoGoodie(StudentWorld* pt, double startX, double startY, int imageID, Direction dir, double size, unsigned int depth)
	:Goodie(pt, startX, startY, imageID, dir, size, depth)
{

}
void TorpedoGoodie::benefit() {
	getWorld()->addTorpedo();
}