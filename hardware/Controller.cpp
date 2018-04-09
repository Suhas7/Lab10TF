#include <cmath>
#define PI 3.1415926535897932384626433832795028841971
#define cJ 1 //standardize joystick output

void Controller::Controller(){
	static int i = 0;
	this->ID=i;
	i++;
}
void Controller::Controller(int n){
	this->ID=n;
}

double Controller::getJAngle(){
	double x = this->X.Distance();
	double y = this->Y.Distance()
	return atan(y/x)*180/PI;
}
double Controller::getJX(){
	return cJ*this->X.Distance();
}
double Controller::getJY(){
	return cJ*this->Y.Distance();
}
bool Controller::getA();
bool Controller::getB();
bool Controller::getJ();