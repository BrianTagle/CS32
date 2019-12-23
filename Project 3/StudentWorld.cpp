#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include<cmath>

using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
}

int StudentWorld::init()
{
	aliensDestroyed = 0;
	aliensNeededtoContinue = 6 + (4 * getLevel());
	NB = new NachenBlaster(this);
	for (int i = 0; i < 30; i++) {// add the first 30 stars to the world
		int intX = randInt(0, VIEW_WIDTH - 1);
		addStar(actors, intX);

	}
	

	
	
	string text = "Lives: " + to_string(getLives()) + "  Health: "+ to_string(int(NB->getHealth()*2)) + 
		"%  Score: "+ to_string(getScore()) + "  Level: "+ to_string(getLevel()) +
		"  Cabbages: "+ to_string(NB->getCabbagePoints()) +"%  Torpedoes: "+to_string(NB->getTorpedoCount())+ " ";
	setGameStatText(text);
	
	
    return GWSTATUS_CONTINUE_GAME; //init always returns continue game;
}

int StudentWorld::move()
{
	string text = "Lives: " + to_string(getLives()) + "  Health: " + to_string(int(NB->getHealth() * 2)) +
		"%  Score: " + to_string(getScore()) + "  Level: " + to_string(getLevel()) +
		"  Cabbages: " + to_string(NB->getCabbagePoints()*10 /3) + "%  Torpedoes: " + to_string(NB->getTorpedoCount()) + " ";

	setGameStatText(text);
	if (NB->getHealth() <= 0) {
		decLives();
		return GWSTATUS_PLAYER_DIED; //the player has died
	}
	if (aliensDestroyed >= aliensNeededtoContinue) { //when the players has killed enough aliens for the current level
		return GWSTATUS_FINISHED_LEVEL;
		
	}

	NB->doSomething();
	vector<Actor*>::iterator it = actors.begin();
	while (it != actors.end()) {
		(*it)->doSomething(); //let the star move one pixel to the left
		if (!((*it)->isAlive())) { //if the star's state is dead, remove it from the game
			delete *it;
			it = actors.erase(it);
			
		}
		else {
			it++;
		}
	}
	if (randInt(1, 15) == 1) {
		
		addStar(actors, (VIEW_WIDTH-1));
	}
	int shipsRemaining = aliensNeededtoContinue - aliensNeededtoContinue;
	int maxShips = 4 + (.5*getLevel());
	int currentShips = 0;
	for (int i = 0; i < actors.size(); i++) {
		if (actors[i]->isGon()) {
			currentShips++;
		}
	}
	if(currentShips < maxShips || currentShips < shipsRemaining) { //if instead of while loop so only
		int S1 = 60;
		int S2 = 20 + (getLevel() * 5);
		int S3 = 5 + (getLevel() * 10);
		int S = S1 + S2 + S3;
		int randS = randInt(1, S);
		Actor* N; 

		if (randS <= S1 ) { //smallgon spawn
			N = new Smallgon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1));
			actors.push_back(N);
		}
		else if (randS > S1 && randS <= S - S3) { //smoregon spawn 
			N = new Smoregon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1));
			actors.push_back(N);
		}
		else if (randS > S - S3) {//snagglegon spawn
			N = new Snagglegon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1));
			actors.push_back(N);
		}
		
	}


	

	
	return GWSTATUS_CONTINUE_GAME;

}

void StudentWorld::cleanUp()
{
	
	for (int i = 0; i< actors.size(); i++)
	{
		delete (actors[i]);
	}
	actors.clear();
	
	//clear star vector of all stars
	delete NB; //delete the current nachenblaster
	NB = nullptr;
}


void StudentWorld::addStar(vector<Actor*>& stars, int Xcoord) {
	double size = (randInt(5, 50)) / double(100);
	
	int intY = randInt(0, VIEW_HEIGHT-1);
	Star *S = new Star(this, IID_STAR, Xcoord, intY, 0, size, 3);
	stars.push_back(S);
}
bool StudentWorld::NachenInRange(Actor* OPT) {
	if (NB->getX() < OPT->getX() && abs(NB->getY() - OPT->getY()) <= 4) { //if the nachen is to the left of the alien and is within 4 pixels in either y direction
		return true;
	}
	return false;
}

bool StudentWorld::CollisionWithAlien(Actor*OPT) {
	for (int i = 0; i < actors.size(); i++) {
		if (actors[i]->isHostile()) {
			double distance = sqrt(pow(OPT->getX() - actors[i]->getX(), 2) + pow(OPT->getY() - actors[i]->getY(), 2)); //find the euclidian distance 
			if (distance < (.75*(OPT->getRadius() + actors[i]->getRadius()))) { //if that distance is less that .75 * the sum of the radius's
				if (handleCollision(OPT, actors[i]) ){
					return true; //collision detected
				}
				
				
			}
		}
	}
	return false;// no collision
}
bool StudentWorld::CollisionWithNachen(Actor*OPT){
	double distance = sqrt(pow(OPT->getX() - NB->getX(), 2) + pow(OPT->getY() - NB->getY(), 2)); //find the euclidian distance 
	if (distance < (.75*(OPT->getRadius() + NB->getRadius()))) { //if that distance is less that .75 * the sum of the radius's
		handleCollision(OPT, NB);
		
		return true; //COLLISION DETECTED
		
	}
	return false;// no collision
}

void StudentWorld::spawnExplosion(double startX, double startY) {
	Actor* N = new Explosion(this, startX, startY);
	actors.push_back(N);
}
void StudentWorld::shootCabbage(double startX, double startY) {
	Actor* N = new Cabbage(this, startX, startY);
	actors.push_back(N);
}
void StudentWorld::shootTurnip(double startX, double startY) {
	Actor* N = new Turnip(this, startX, startY);
	actors.push_back(N);
}
void StudentWorld::shootTorpedo(double startX, double startY, int faction) {
	Actor* N = new Torpedo(this, startX, startY, faction);
	actors.push_back(N);
}
bool StudentWorld::handleCollision(Actor* Dealer, Actor* taker) {
	if (Dealer->isProjectile() && taker->isProjectile()) { //two projectiles will never intersect
		return false;
	}
	if (Dealer->getObjectScore() > 0) { //when the damage dealer is an alien ship or a goodie , taker is the nachenblaster
		Dealer->setDead();
		if (Dealer->isGon()) { //the collision is with an alien
			taker->sufferDamage(Dealer->getDamage());
			playSound(SOUND_DEATH);
			spawnExplosion(Dealer->getX(), Dealer->getY());
			Dealer->GoodieAction();
			aliensDestroyed++; //increment the number of aliens destroyed
		}
		else { //collision with a goodie
			playSound(SOUND_GOODIE);
		}

		increaseScore(Dealer->getObjectScore());
	}
	else if(Dealer->isProjectile()) { //the dealer is a projectile
		taker->sufferDamage(Dealer->getDamage());
		Dealer->setDead(); //destroy the projectile after it hits an alien
		if (taker->getHealth() <= 0) { //when the alien dies, create an explosion
			taker->setDead();
			increaseScore(taker->getObjectScore());
			
			if (taker->isHostile()) {
				playSound(SOUND_DEATH);
				spawnExplosion(taker->getX(), taker->getY());
				aliensDestroyed++; //increment the number of aliens destroyed
				taker->GoodieAction();
			}
		}
		else {
			playSound(SOUND_BLAST); //sound for when the projectile impacts the alien but does not kill it
		}
	}
	return true;//succesful collision action
}
void StudentWorld::healNB(double amt) { 
	NB->sufferDamage(-amt); 
	if (NB->getHealth() > 50) {
		NB->setHealth(50);
	}
} //suffering negative damage heals the actor

void StudentWorld::addTorpedo() {
	NB->increaseTorpedoCount();
}

void StudentWorld::spawnExtraLife(double startX, double startY) {
	Actor* N = new ExtraLifeGoodie(this, startX, startY);
	actors.push_back(N);
}
void StudentWorld::spawnRepair(double startX, double startY) {
	Actor* N = new RepairGoodie(this, startX, startY);
	actors.push_back(N);
}
void StudentWorld::spawnTorpedoG(double startX, double startY) {
	Actor* N = new TorpedoGoodie(this, startX, startY);
	actors.push_back(N);
}