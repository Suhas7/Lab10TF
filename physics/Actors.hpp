//PHYSICS CALIBRATION
	//winSize
			//KEEP AN EYE OUT FOR UNITIZATION AND INTERNAL RESOLUTION
		#define xSIZE 320
		#define ySIZE 240
	//calibrate weights
		#define JUMPMAG 3
		#define GRAVMAG 2
		#define DODGESPEED 7
		#define ARROWSPEED 4;
	//arrow IDs
		#define normal 0;
		#define feather 1;
		#define bomb 2;
		#define bomb 3;
	//insert arrow init velocities
//OBJECT DEFINITIONS
class ActiveObject{
	//physics
	float colliderRadius;
	float colliderOffset;
	float xPos;
	float yPos;
//	float angle;
	float xVel;
	float yVel;
	float rVel;
	float xAcc;
	float yAcc;
	float terminalX;
	float terminalY;

	//operations
	ActiveObject(int type);

	applyVel();
	applyAcc();
	applyForce(float x, float y);
	
	halt();
	haltX();
	haltY();
	haltR();
}
	//SUBCLASS DEFINITION
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
		class Arrow: public ActiveObject{
			private:
				int arrowType;
				float angle;
			public:
				//constructor/destructors
				Arrow();
				Arrow(int arrowtype);
				~Arrow();
		}
		class Wall{
			float x1;
			float y1;
			float x2;
			float y2;
		}