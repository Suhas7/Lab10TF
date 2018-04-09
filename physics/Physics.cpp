//KEEP AN EYE OUT FOR GETTING STUCK ON WALLS

//GENERAL PHYSICS
	//MOVEMENT PROCESSING
		void checkCollision(ActiveObject& a, ActiveObject& b){ //check if collider radii cross
			float xDist = (a->xPos-b->xPos)*(a->xPos-b->xPos);
			float yDist = (a->yPos-b->yPos)*(a->yPos-b->yPos);
			float threshold = (a->colliderRadius+b->colliderRadius)*(a->colliderRadius+b->colliderRadius);
			if(threshold>=(xDist+yDist)) return true;
			return false;
		}
		void processCollision(ActiveObject& a, ActiveObject& b){ //
			//HOW TO CHECK isInstance??
			//resolve collisions
			//wall/arrow: arrow halts x,y
				//halt All
				//grounded=true
			//wall/player: 
				//if angle is not down quadrant:
					//player halts both- key to wall jump, can wall hang
				//else:
					//halt the players Y velocity
			//arrow/player: 
				//destroy player instance, iff player.dodge==0 && arrowspeed>=fatal
				//else if dodge, give arrow
				//else phase arrow
				//according sound FX
			//arrow/arrow: halt both, slight upward/rand horizontal speed
			//player/player:
				//if not upper quad: halts along axis of collision
				//else: kill player bc booperoni
		}
	//MOVEMENT APPLICATION
		void ActiveObject::applyVel(){
			this->xPos+=this->xVel/60;
			this->xPos %= xSIZE;
			this->yPos+=this->yVel/60;
			this->yPos %= ySIZE;
		}
		void ActiveObject::applyAcc(){
			this->xVel+=this->xAcc/60;
			this->xVel %= self->terminalX;
			this->yVel+=this->yAcc/60;
			this->yVel %= self->terminalY;
		}
		void ActiveObject::applyForce(float x, float y){
			this->xVel+=x;
			this->xVel %= this->terminalX;
			this->yVel+=y;
			this->yVel %= this->terminalY;
		}
	//MOVEMENT ERASURE
		void ActiveObject::haltX() this->xVel=0;
		void ActiveObject::haltY() this->YVel=0;
		void ActiveObject::haltR() this->rVel=0;
		void ActiveObject::halt(){this->haltX();this->haltY();this->haltR();}
//ARCHER METHODS
	//ARCHER STRUCTORS
		//TO IMPLEMENT
		void Archer::Archer(){
			static int i=0;
			this->playerID=i;
			this->arrowInventory=new int[8]; //is this right lol
			for(this->inventorySize=0;this->inventorySize<3;this->inventorySize++){ //def arrows
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
		void Archer::jump(){this->yVel=JUMPVEL}
		void Archer::aim(float angle){
			static int last = false;
			if(bBut){
				self->aiming=true;
				aim = angle;
				last=true
			}else{
				if(last){shoot(aim);}
				self->aiming=false;
			}
		}
		void Archer::shoot(float angle){
			Arrow shotArrow = new arrow(this->xPos, this->yPos, this->arrowInventory[0], angle);
			for(int i =1; i<this->inventorySize; i++){
				this->arrowInventory[i-1]=arrowInventory[i];
			}
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