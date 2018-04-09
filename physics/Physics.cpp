//KEEP AN EYE OUT FOR GETTING STUCK ON WALLS

//GENERAL PHYSICS
	//MOVEMENT PROCESSING
		void checkCollision(Object& a, Object& b){ //check if collider radii cross
			float xDist = (b.xPos-a.xPos);
			float yDist = (b.yPos-a.yPos);
			if(xDist<=(a.colliderWidth+b.colliderWidth)) return true;
			if(yDist<=(a.colliderHeight+b.colliderHeight)) return true;
			return false;
			/* RADIAL IMPLEMENTATION
				float xDist = (a->xPos-b->xPos)*(a->xPos-b->xPos);
				float yDist = (a->yPos-b->yPos)*(a->yPos-b->yPos);
				float sDist = (a->colliderRadius+b->colliderRadius);
				float threshold = sDist*sDist;
				return threshold>=(xDist+yDist) ? true:false;*/
		}
		void serviceCollision(Object& a, Object& b){ //
			//HOW TO CHECK isInstance??
			//resolve collisions
			//bruteforce case division
			if(isWall(a)){
				if(isWall(b)) processWallWall(a,b);
				if(isArcher(b)) processWallArcher(a, b)
				if(isArrow(b)) processWallArrow(a, b);
			}
			if(isArcher(a)){
				if(isWall(b)) processWallArcher(b, a);
				if(isArcher(b)) processArcherArcher(a, b);
				if(isArrow(b)) processArcherArrow(a, b);
			}
			if(isArrow(a)){
				if(isWall(b)) processWallArrow(b, a);
				if(isArcher(b)) processArcherArrow(b, a)
				if(isArrow(b)) processArrowArrow(a, b);
			}
		}
		
		void processWallWall(Object& a, Object& b) return;
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
			//if grounded || dodge then b.catch(a);
			//if b.dodge==0 && arrowspeed>=fatal: kill player and stop arrow
			//else phase arrow
			//according sound FX
		void processArrowArrow(ActiveObject& a, ActiveObject& b);
			//arrow/arrow: halt both, slight upward/rand horizontal speed
			//process angle of collision, send arrows opposite direction w scaled speed
		void collisionAngle(Object& a, Object& b){
			float yDist = (a->yPos-b->yPos)*(a->yPos-b->yPos);
			float xDist = (a->xPos-b->xPos)*(a->xPos-b->xPos);
			return atan(yDist/xDist)*180/PI;
		}
	//MOVEMENT APPLICATION
		void ActiveObject::processPhys(){
			this.applyAcc();
			this.applyVel();
			//iff arrow:
				this.angle=atan(this.yVel/this.xVel); //only for arrows?
		}
		void ActiveObject::applyVel(){ //increment pos by scaled Vel
			this->xPos+=this->xVel/60;
			this->xPos %= xSIZE;
			this->yPos+=this->yVel/60;
			this->yPos %= ySIZE;
		}
		void ActiveObject::applyAcc(){ //increment velocity by scaled Acc
			this->xVel+=this->xAcc/60;
			this->xVel %= self->terminalX;
			this->yVel+=this->yAcc/60;
			this->yVel %= self->terminalY;
		}
		void ActiveObject::applyForce(float x, float y){
			this->xAcc+=x;
			this->yAcc+=y;
		}
	//MOVEMENT ERASURE
		void ActiveObject::haltX() this->xVel=0;
		void ActiveObject::haltY() this->YVel=0;
		void ActiveObject::haltR() this->rVel=0;
		void ActiveObject::halt(){ this->haltX();this->haltY();this->haltR();}
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
		void Archer::catch(Arrow& caughtArrow){
			if(this->inventorySize==4){caughtArrow->halt();return;} //if inventory full, halt arrow and return
			this->arrowInventory[inventorySize]=caughtArrow->arrowType; //else, add to inventory and destroy
			delete caughtArrow;
			playSound(sByte[4]);
		}
		void Archer::jump(){
			if(this->grounded) this->yVel=JUMPVEL;
		}
		void Archer::aim(float angle){
			static int last = false;
			if(bBut){
				self->aiming=true;
				aim = this->ctrlr.getJAngle();
				last=true;
			}else{
				if(last){shoot(this->ctrlr.getJAngle());}
				self->aiming=false;
			}
		}
		void Archer::shoot(float angle){
			Arrow shotArrow = new arrow(this->xPos, this->yPos, this->arrowInventory[0], angle);
			for(int i =1; i<this->inventorySize; i++){this->arrowInventory[i-1]=arrowInventory[i];}
			inventorySize--;
			shotArrow->angle=angle;
		}
		void Archer::dodge(float angle){
			this->xVel = DODGESPEED * cos(angle*PI/180);
			this->yVel = DODGESPEED * sin(angle*PI/180);
			this->dodged=15;
		}
//ARROW METHODS
	void Arrow::Arrow(float xPos,float yPos,int type,float angle){
		this->xPos=xPos;
		this->yPos=yPos;
		this->xVel=ARROWSPEED * cos(angle*PI/180);
		this->yVel=ARROWSPEED * sin(angle*PI/180);
		this->yAcc=GRAVMAG;
		this->xAcc=0;
		this->angle =angle;
		terminalX=5;
	 	terminalY=7;
	}
	void Arrow::refresh(){
		aim();
		this->angle =atan((this->yVel/this->yDist))*180/PI;
	}