ArcherSprites[4] = {'a','b','c','d'}
arrowSprites[6] = {'a','b','c','d','e','f'}
//insert arrow init velocities
const Wall* stage; //stage is defined as a collection of Walls, static

class Wall{
	float x1;
	float y1;
	float x2;
	float y2;
}

class ActiveObject{ //make Arrow/Archer inherit?
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
	ActiveObject(int type);
}

class Archer{
	private:
		int playerID;
		int* arrowInventory;
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
		//status
		float dodged; //framecount
		bool grounded;
	public:
		//constructor/destructors
		Archer();
		Archer(int PlayerNum)
		~Archer();
		//physics
		halt();
		haltX();
		haltY();
		applyForce(float x, float y);
		//behaviors
		catch(Arrow& caughtArrow);
		jump();
		dodge(float angle);
}

class Arrow{
	private:
		int arrowType;
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
	public:
		//constructor/destructors
		Arrow();
		Arrow(int arrowtype);
		~Arrow();
		applyForce(float x, float y);
}

//Systick Handler
void Systick_Handler(){
	//detect collisions
	//resolve collisions
		//wall/arrow: arrow halts x,y
		//wall/player: player halts both- key to wall jump, can wall hang
		//arrow/player: destroy player instance, iff player.dodge==0, otherwise give arrow
			//according sound FX
		//arrow/arrow: halt x of both
		//player/player: halts along axist of collision
	//apply velocities to all players, objects
	//decrement nonzero dodge values
}