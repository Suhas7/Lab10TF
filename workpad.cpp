
#include "../Sound.h"
//winSize
#define xSIZE 320
#define ySIZE 240
#define gravMagnitude 2
//insert arrow init velocities
//DESIGN ASSETS
	//insert default stages
	//insert sprite filepaths
	//insert sound bytes
const Wall* stage; //stage is defined as a collection of Walls, static
ArcherSprites[4] = {'a','b','c','d'}
arrowSprites[6] = {'a','b','c','d','e','f'}

//KEEP AN EYE OUT FOR UNITIZATION AND INTERNAL RESOLUTION


class Wall{
	float x1;
	float y1;
	float x2;
	float y2;
}

class ActiveObject{
	//physics
	float colliderRadius;
	float colliderOffset;
	float xPos;
	float yPos;
	float xVel;
	float yVal;
	float xAcc;
	float yAcc;
	float terminalX;
	float terminalY;
	//operationss
	ActiveObject(int type);
	applyVel();
	applyForce(float x, float y);
	halt();
	haltX();
	haltY();	}

class Archer: public ActiveObject{
	private:
		int playerID;
		int inventorySize;
		int[8] arrowInventory;
		//status
		int dodged; //framecount, 15fm?
		bool grounded;
		bool aiming;
	public:
		//constructor/destructors
		Archer();
		Archer(int PlayerNum)
		~Archer();
		//behaviors
		catch(Arrow& caughtArrow); //done
		jump();
		dodge(float angle);
		aim(float angle);
		shoot(float angle);
}

class Arrow : public ActiveObject{
	private:
		int arrowType;
	public:
		//constructor/destructors
		Arrow();
		Arrow(int arrowtype);
		~Arrow();
}

//Systick Handler
void Systick_Handler(){
	//detect collisions
	for(int i =0; i<num_objects; i++){ //n^2 complexity
		for(int j =i; j<num_objects;j++) processCollision(objects[i], objects[j]);
	}
	for(int i =0; i<num_objects; i++) applyVel(i)
	//decrement nonzero dodge values
}
void checkCollision(ActiveObject& a, ActiveObject& b){ //check if collider radii cross
	float xDist = (a->xPos-b->xPos)*(a->xPos-b->xPos);
	float yDist = (a->yPos-b->yPos)*(a->yPos-b->yPos);
	float threshold = (a->colliderRadius+b->colliderRadius)*(a->colliderRadius+b->colliderRadius);
	if(threshold>=(xDist+yDist)) return true;
	return false;
}
void processCollision(ActiveObject& a, ActiveObject& b){ //
		//resolve collisions
		//wall/arrow: arrow halts x,y
		//wall/player: player halts both- key to wall jump, can wall hang
		//arrow/player: 
			//destroy player instance, iff player.dodge==0 && arrowspeed>=fatal
			//else if dodge, give arrow
			//else phase arrow
			//according sound FX
		//arrow/arrow: halt both, slight upward/rand horizontal speed
		//player/player: halts along axist of collision
}

void ActiveObject::applyVel(){
	this->xPos+=this->xVel/60;
	this->xPos %= xSIZE;
	this->yPos+=this->yVel/60;
	this->yPos %= ySIZE;
}

void ActiveObject::applyForce(float x, float y){
	this->xVel+=x;
	this->xVel %= this->terminalX;
	this->yVel+=y;
	this->yVel %= this->terminalY;
}

void Archer::catch(Arrow& caughtArrow){
	if(this->inventorySize==4){caughtArrow->halt();return;} //if inventory full, halt arrow and return
	this->arrowInventory[inventorySize]=caughtArrow->arrowType; //else, add to inventory and destroy
	caughtArrow::~Arrow();
	playSound(sByte[4]);
}

void playSound(float* s); //shift systick parameters accordingly