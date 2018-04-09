//PHYSICS CALIBRATION
	//winSize
			//KEEP AN EYE OUT FOR UNITIZATION AND INTERNAL RESOLUTION
		#define xSIZE 320
		#define ySIZE 240
	//insert gravity weight
		#define JUMPMAG 3
		#define GRAVMAG 2
	//insert arrow init velocities

class ActiveObject{
	//physics
	float colliderRadius;
	float colliderOffset;
	float xPos;
	float yPos;
	float angle;
	float xVel;
	float yVel;
	float rVel
	float xAcc;
	float yAcc;
	float terminalX;
	float terminalY;

	//operations
	ActiveObject(int type);
	applyVel();
	applyForce(float x, float y);
	halt();
	haltX();
	haltY();
	haltR();
}

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