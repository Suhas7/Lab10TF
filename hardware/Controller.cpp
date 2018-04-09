#include <cmath>
#define PI 3.1415926535897932384626433832795028841971
#define cJ 1 //standardize joystick output

float Controller::getJAngle(){
	float x = this->X.Distance();
	float y = this->Y.Distance()
	return atan(y/x)*180/PI;
}
float Controller::getJX(){
	return cJ*this->X.Distance();
}
float Controller::getJY(){
	return cJ*this->Y.Distance();
}