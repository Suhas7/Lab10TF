#include <cmath>
#define PI 3.1415926535897932384626433832795028841971
#include "../hardware/Controller.hpp"
//PHYSICS CALIBRATION
	//winSize
		//KEEP AN EYE OUT FOR UNITIZATION AND INTERNAL RESOLUTION
		#define xSIZE 320 //defaults bc of res
		#define ySIZE 240
	//calibrate weights
		#define JUMPMAG 3
		#define GRAVMAG 2
		#define DODGESPEED 7
		#define ARROWSPEED 4;
	//arrow IDs
		#define sentinel -1;
		#define normal 0;
		#define feather 1;
		#define bomb 2;
		#define sbomb 3;

//OBJECT DEFINITIONS
class Object{
	public:
	double xPos;
	double yPos;
	int sprite;
	int spriteOffset;
	int distance;
	double colliderWidth;
	double colliderHeight;
	double colliderOffset;
};
class Wall: public Object{public:
	double x1;
	double y1;
	double x2;
	double y2;
};
class ActiveObject : public Object{public:
	//physics
	double colliderRadius;
	double colliderOffset;
	bool grounded=false;
	double xVel;
	double yVel;
	double xAcc;
	double yAcc;
	double terminalX;
	double terminalY;

	//operations
	void ActiveObject::ActiveObject();
	void ActiveObject(int type);
	//frame processing:
	void processPhys();
	void applyVel();
	void applyAcc();
	void lateralVel(double x);
	void applyForce(double x, double y);

	void halt();
	void haltX();
	void haltY();
	void haltR();
};
class Archer: public ActiveObject{public:
	int playerID;
	Controller* ctrlr;
	int inventorySize;
	int* arrowInventory;
	//status
	bool grounded;
	bool aiming;
	int dodged; //framecount, 15fm?
	double aimAngle;
	//constructor/destructors
	Archer();
	Archer(int PlayerNum);
	~Archer();
	//phys
	void refresh();
	//behaviors
	void catchArrow(Arrow& caughtArrow);
	void jump();
	void dodge(double angle);
	void aim(double angle);
	void shoot(double angle);
};
class Arrow: public ActiveObject{public:
	int arrowType;
	double angle;
	//constructor/destructors
	Arrow();
    void Arrow::Arrow(double xPos,double yPos,int type,double angle);
	~Arrow();
	//phys
	void refresh();
};

//COLLISION FUNCTIONS
void serviceCollision(Object& a, Object& b);
	//HELPER FUNCTIONS
	void processWallWall(Object& a, Object& b);
	void processWallArcher(Object& a, ActiveObject& b);
	void processWallArrow(Object& a, ActiveObject& b);
	void processArcherArcher(ActiveObject& a,ActiveObject& b);
	void processArcherArrow(ActiveObject& a, ActiveObject& b);
	void processArrowArrow(ActiveObject& a, ActiveObject& b);
	double collisionAngle(Object& a, Object& b);