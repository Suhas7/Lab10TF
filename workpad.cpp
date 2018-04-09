
#include "../Sound.h"
//TO DOs
//DESIGN ASSETS
	//insert default stages
		const Wall* stage; //stage is defined as a collection of Walls, static
	//insert sprite filepaths
		ArcherSprites[4] = {'a','b','c','d'}
		arrowSprites[6] = {'a','b','c','d','e','f'}
	//insert sound bytes

void playSound(float* s); //shift systick parameters accordingly
//Systick Handler
void Systick_Handler(){
	//detect collisions
	for(int i =0; i<num_objects; i++){ //n^2 complexity
		for(int j =i; j<num_objects;j++){
			//if collision has happened, process it
			if(checkCollision(objects[i], objects[j])) processCollision(objects[i], objects[j]);
		}
	}
	for(int i =0; i<num_objects; i++) applyVel(i)
	//decrement nonzero dodge values
}