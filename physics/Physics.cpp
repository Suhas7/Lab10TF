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
			//wall/player: player halts both- key to wall jump, can wall hang
			//arrow/player: 
				//destroy player instance, iff player.dodge==0 && arrowspeed>=fatal
				//else if dodge, give arrow
				//else phase arrow
				//according sound FX
			//arrow/arrow: halt both, slight upward/rand horizontal speed
			//player/player: halts along axis of collision
				//boops
		}
	//MOVEMENT APPLICATION
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
	//MOVEMENT ERASURE
		void ActiveObject::haltX() this->xVel=0;
		void ActiveObject::haltY() this->YVel=0;
		void ActiveObject::haltR() this->rVel=0;
		void ActiveObject::halt(){this->haltX();this->haltY();this->haltR();}
//ARCHER FUNCTIONS
	//ARCHER STRUCTORS
		//TO IMPLEMENT
		void Archer::Archer();
		void Archer::~Archer(); 
	//ARCHER BEHAVIOUR
		void Archer::catch(Arrow& caughtArrow){
			if(this->inventorySize==4){caughtArrow->halt();return;} //if inventory full, halt arrow and return
			this->arrowInventory[inventorySize]=caughtArrow->arrowType; //else, add to inventory and destroy
			delete caughtArrow;
			playSound(sByte[4]);
		}
		void Archer::jump(){this->yVel=JUMPVEL}

		//TO IMPLEMENT
		void Archer::shoot(float angle){
			Arrow shotArrow = new arrow(this->arrowInventory[0]);
			for(int i =1; i<this->inventorySize; i++){
				this->arrowInventory[i-1]=arrowInventory[i];
			}
			inventorySize--;
			shotArrow->angle=angle;
		}
		void Archer::aim(float angle){
			//while !duck || bBut hit
			//get controller input
			//set archer aim at new angle
		}
		
		void Archer::dodge(float angle){


		}

//ARROW FUNCTIONS
	//ARROW STRUCTORS