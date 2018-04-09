//KEEP AN EYE OUT FOR GETTING STUCK ON WALLS
#include "Actors.hpp"

//#include <cmath>
//GENERAL PHYSICS
	//ISINSTANCE FUNCTIONS
		template<typename T, typename K>
		inline bool isType(const K &k) {
    		return typeid(T).hash_code() == typeid(k).hash_code();
		}
//        bool isType<Wall>(Object& in){return dynamic_cast<Wall*>(in) != nullptr; }
//        bool isType<Archer>(Object& in){return (dynamic_cast<Archer*>(in))!=nullptr;}
//        bool isType<Arrow>(Object& in){return (dynamic_cast<Arrow*>(in))!=nullptr;}
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
			//dynamic casts cost tho :(
			if(isType<Wall>(a)){
				if(isType<Wall>(b)) processWallWall(a,b);
				if(isType<Archer>(b)) processWallArcher(a, dynamic_cast<Archer&>(b));
				if(isType<Arrow>(b)) processWallArrow(a, dynamic_cast<Arrow&>(b));
			}
			if(isType<Archer>(a)){
				if(isType<Wall>(b)) processWallArcher(b, dynamic_cast<Archer&>(a));
				if(isType<Archer>(b)) processArcherArcher(dynamic_cast<Archer&>(a), dynamic_cast<Archer&>(b));
				if(isType<Arrow>(b)) processArcherArrow(dynamic_cast<Archer&>(a), dynamic_cast<Arrow&>(b));
			}
			if(isType<Arrow>(a)){
				if(isType<Wall>(b)) processWallArrow(b, dynamic_cast<Arrow&>(a));
				if(isType<Archer>(b)) processArcherArrow(dynamic_cast<Archer&>(b), dynamic_cast<Arrow&>(a));
				if(isType<Arrow>(b)) processArrowArrow(dynamic_cast<Arrow&>(a), dynamic_cast<Arrow&>(b));
			}
		}
        void processWallWall(Object& a, Object& b){return;}
        //phase thru?
        void processWallArcher(Object& a, Archer& b);
        //set angle var to angle of collision
        //wall/player:
        //if angle is not down quadrant:
        //player halts both- key to wall jump, can wall hang
        //else:
        //halt the players Y velocity
        //scale down X velocity
        void processWallArrow(Object& a, Arrow& b);
        //arrow halts x,y
        //halt arrow
        //grounded=true
        void processArcherArcher(Archer& a,Archer& b);
        //if not upper quad: halts along axis of collision
        //else: kill player bc booperoni
        void processArcherArrow(Archer& a, Arrow& b);
        //if grounded || dodge then b.catchArrow(a);
        //if b.dodge==0 && arrowspeed>=fatal: kill player and stop arrow
        //else phase arrow
        //according sound FX
        void processArrowArrow(Arrow& a,Arrow& b);
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
            i++;
            ctrlr = new Controller(playerID);
			this->arrowInventory=new int[8]; //is this right lol
			for(this->inventorySize=0;this->inventorySize<3;this->inventorySize++){ //default arrows
				this->arrowInventory[this->inventorySize]=normal;
			}
			for(int in = 3; in<8; in++){this->arrowInventory[in]=sentinel;}
			this->dodged=0;
			this->grounded=true;
			this->aiming=false;
		}
		void Archer::~Archer(){
			delete this->ctrlr;
			delete[] this->arrowInventory;
		}
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
			if(this->ctrlr->getB()){
				this->aiming=true;
				this->aimAngle = this->ctrlr->getJAngle();
				last=true;
			}else{
				if(last){shoot(this->ctrlr->getJAngle());}
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
            if(this->dodged){
            	this->dodged--;
            	if(!this->dodged) this->halt();
            }        //update dodge status, if nonzero
            if(grounded){yAcc=0;yVel=0;   //set yAcc in accordance w grounding
            }else{yAcc=GRAVMAG;}
            this->aim(this->ctrlr->getJAngle());     //update aim parameter
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
