#include "/physics/Actors.hpp"
#include "/audio/Sound.hpp"
#include "/display/kentec.hpp"

//Systick Handler
void Systick_Handler(){
	//detect collisions
	for(int i =0; i<num_objects; i++){ //n^2 complexity
		for(int j =i; j<num_objects;j++){
			//if collision has happened, process it
			if(checkCollision(objects[i], objects[j])) processCollision(objects[i], objects[j]);
		}
	}
	for(int i =0; i<num_objects; i++) objects[i].processPhys();
	//decrement nonzero dodge values
}