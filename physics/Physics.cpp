//KEEP AN EYE OUT FOR GETTING STUCK ON WALLS
#include "Actors.hpp"
#include "../hardware/Controller.hpp"
//#include <cmath>
//GENERAL PHYSICS
	//ISINSTANCE FUNCTIONS
        bool isWall(Object& in){return dynamic_cast<Wall*>(in) != nullptr; }
        bool isArcher(Object& in){return (dynamic_cast<Archer*>(in))!=nullptr;}
        bool isArrow(Object& in){return (dynamic_cast<Arrow*>(in))!=nullptr;}
	//MOVEMENT PROCESSING
		bool checkCollision(Object& a, Object& b){ //check if colliders intersect
			double xDist = (b.xPos-a.xPos);
			double yDist = (b.yPos-a.yPos);
			if(xDist<0) xDist*=-1;
			if(yDist<0) yDist*=-1;
			if(xDist<=(a.colliderWidth+b.colliderWidth)) return true;
			if(yDist<=(a.colliderHeight+b.colliderHeight)) return true;
			return false;
			/* RADIAL IMPLEMENTATION
				double xDist = (a->xPos-b->xPos)*(a->xPos-b->xPos);
				double yDist = (a->yPos-b->yPos)*(a->yPos-b->yPos);
				double sDist = (a->colliderRadius+b->colliderRadius);
				double threshold = sDist*sDist;
				return threshold>=(xDist+yDist) ? true:false;*/
		}
		void serviceCollision(Object& a, Object& b){ //
			//resolve collisions
			//bruteforce case division
			if(isWall(a)){
				if(isWall(b)) processWallWall(a,b);
				if(isArcher(b)) processWallArcher(a, dynamic_cast<Archer&>(b));
				if(isArrow(b)) processWallArrow(a, dynamic_cast<Arrow&>(b));
			}
			if(isArcher(a)){
				if(isWall(b)) processWallArcher(b, dynamic_cast<Archer&>(a));
				if(isArcher(b)) processArcherArcher(dynamic_cast<Archer&>(a), dynamic_cast<Archer&>(b));
				if(isArrow(b)) processArcherArrow(dynamic_cast<Archer&>(a), dynamic_cast<Arrow&>(b));
			}
			if(isArrow(a)){
				if(isWall(b)) processWallArrow(b, dynamic_cast<Arrow&>(a));
				if(isArcher(b)) processArcherArrow(dynamic_cast<Archer&>(b), dynamic_cast<Arrow&>(a));
				if(isArrow(b)) processArrowArrow(dynamic_cast<Arrow&>(a), dynamic_cast<Arrow&>(b));
			}
		}
        void processWallWall(Object& a, Object& b){return;}
        //phase thru?
        void processWallArcher(Object& a, ActiveObject& b);
        //set angle var to angle of collision
        //wall/player:
        //if angle is not down quadrant:
        //player halts both- key to wall jump, can wall hang
        //else:
        //halt the players Y velocity
        //scale down X velocity
        void processWallArrow(Object& a, ActiveObject& b);
        //arrow halts x,y
        //halt arrow
        //grounded=true
        void processArcherArcher(ActiveObject& a,ActiveObject& b);
        //if not upper quad: halts along axis of collision
        //else: kill player bc booperoni
        void processArcherArrow(ActiveObject& a, ActiveObject& b);
        //if grounded || dodge then b.catchArrow(a);
        //if b.dodge==0 && arrowspeed>=fatal: kill player and stop arrow
        //else phase arrow
        //according sound FX
        void processArrowArrow(ActiveObject& a, ActiveObject& b);
        //arrow/arrow: halt both, slight upward/rand horizontal speed
        //process angle of collision, send arrows opposite direction w scaled speed
        double collisionAngle(Object& a, Object& b){
            double yDist = (a.yPos-b.yPos)*(a.yPos-b.yPos);
            double xDist = (a.xPos-b.xPos)*(a.xPos-b.xPos);
            return atan(yDist/xDist)*180/PI;
        }


	//MOVEMENT APPLICATION
        void ActiveObject::ActiveObject();
		void ActiveObject::processPhys(){
			this->applyAcc();
			this->applyVel();
			//iff arrow:
			//	this->angle=atan(this->yVel/this->xVel); //only for arrows?
		}
		void ActiveObject::applyVel(){ //increment pos by scaled Vel
			this->xPos+=this->xVel/60;
			while(this->xPos>xSIZE) this->xPos -= xSIZE;
			this->yPos+=this->yVel/60;
            while(this->yPos>ySIZE) this->yPos -= ySIZE;
		}
		void ActiveObject::applyAcc(){ //increment velocity by scaled Acc
			this->xVel+=this->xAcc/60;
			if(this->xVel>this->terminalX)this->xVel = this->terminalX ;
			this->yVel+=this->yAcc/60;
            if(this->yVel>this->terminalY)this->yVel = this->terminalY;
        }
		void ActiveObject::applyForce(double x, double y){
			this->xAcc+=x;
			this->yAcc+=y;
		}
	//MOVEMENT ERASURE
		void ActiveObject::haltX(){this->xVel=0;}
		void ActiveObject::haltY(){this->yVel=0;}
		//void ActiveObject::haltR(){this->rVel=0;}
		void ActiveObject::halt(){ this->haltX();this->haltY();}
//ARCHER METHODS
	//ARCHER STRUCTORS
		void Archer::Archer(){
			static int i=0;
			this->playerID=i;
			this->arrowInventory=new int[8]; //is this right lol
			for(this->inventorySize=0;this->inventorySize<3;this->inventorySize++){ //default arrows
				this->arrowInventory[this->inventorySize]=0;
			}
			for(int in = 3; in<8; in++){this->arrowInventory[in]=-1;}
			this->dodged=0;
			this->grounded=true;
			this->aiming=false;
		}
		void Archer::~Archer(){delete[] this->arrowInventory;}
	//ARCHER BEHAVIOUR
		void Archer::catchArrow(Arrow& caughtArrow){
			if(this->inventorySize==4){caughtArrow.halt();return;} //if inventory full, halt arrow and return
			this->arrowInventory[inventorySize]=caughtArrow.arrowType; //else, add to inventory and destroy
			delete caughtArrow;
			//playSound(sByte[4]);
		}
		void Archer::jump(){
			if(this->grounded) this->yVel=JUMPMAG;
		}
		void Archer::aim(double angle){
			static int last = false;
			if(this->ctrlr.getB()){
				this->aiming=true;
				this->aimAngle = this->ctrlr.getJAngle();
				last=true;
			}else{
				if(last){shoot(this->ctrlr.getJAngle());}
				this->aiming=false;
			}
		}
		void Archer::shoot(double angle){
			Arrow* shotArrow = new Arrow(this->xPos, this->yPos, this->arrowInventory[0], angle);
			for(int i =1; i<this->inventorySize; i++){this->arrowInventory[i-1]=arrowInventory[i];}
			inventorySize--;
			shotArrow->angle=angle;
		}
		void Archer::dodge(double angle){
			this->xVel = DODGESPEED * cos(angle*PI/180);
			this->yVel = DODGESPEED * sin(angle*PI/180);
			this->dodged=15;
		}
        void Archer::refresh(){
            if(this->dodged) this->dodged--;        //update dodge status, if nonzero
            this->aim(this->ctrlr.getJAngle());     //update aim parameter

        }
//ARROW METHODS
    void Arrow::Arrow();
	void Arrow::Arrow(double xPos,double yPos,int type,double angle){
		this->xPos=xPos;
		this->yPos=yPos;
		this->xVel=(cos(angle*PI/180))*ARROWSPEED;
		this->yVel=(sin(angle*PI/180))*ARROWSPEED;
		this->yAcc=GRAVMAG;
		this->xAcc=0;
		this->angle =angle;
		terminalX=5;
	 	terminalY=7;
	}
	void Arrow::refresh(){
		this->angle =atan((this->yVel/this->xVel))*180/PI;
	}
