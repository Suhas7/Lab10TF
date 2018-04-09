#include <cmath>
#define PI 3.1415926535897932384626433832795028841971
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
	float xPos;
	float yPos;
	int sprite;
	int spriteOffset;
	int distance;
	float colliderWidth;
	float colliderHeight;
	float colliderOffset;
};
class Wall: public Object{
	float x1;
	float y1;
	float x2;
	float y2;
};
class ActiveObject : public Object{public:
	//physics
	float colliderRadius;
	float colliderOffset;
	bool grounded=false;
	float xVel;
	float yVel;
	float rVel;
	float xAcc;
	float yAcc;
	float terminalX;
	float terminalY;

	//operations
	void ActiveObject::ActiveObject();
	void ActiveObject(int type);
	//frame processing:
	void processPhys();
	void applyVel();
	void applyAcc();
	void applyForce(float x, float y);

	void halt();
	void haltX();
	void haltY();
	void haltR();
};
class Archer: public ActiveObject{
	public:
		Controller ctrlr = Controller(ID);
		int playerID;
		int inventorySize;
		int* arrowInventory;
		//status
		bool grounded;
		bool aiming;
		int dodged; //framecount, 15fm?
		float aimAngle;
	//public:
		//constructor/destructors
		Archer();
		Archer(int PlayerNum);
		~Archer();
		//phys
		void refresh();
		//behaviors
		void catchArrow(Arrow& caughtArrow);
		void jump();
		void dodge(float angle);
		void aim(float angle);
		void shoot(float angle);
};
class Arrow: public ActiveObject{
	public:
		int arrowType;
		float angle;
	//public:
		//constructor/destructors
		Arrow();
		Arrow(int arrowtype);
		~Arrow();
		//phys
		void refresh();
};
