#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

#define F 5.0	//External force on the cargo (pN) (to -x)
#define N 10	//Number of motors attached to the cargo
#define K 0.32	//Sprin constant of motor (pN/nm)
#define MAX_DIST 200.0
#define STALK_LENGTH 110.0	//Stalk length (nm)
#define EPS	0.01	//For precision
#define DELTA 0.01

float cargo_pos = 0;
float motors[N];

float n_r, n_l; //Motors to right, left of final cargo

float rand1(){

	return (float)rand()/RAND_MAX;

}

void place_motors(){	//To place the motors at the required position 
					//with respect to the cargo
	
	for(int i = 0; i<N; i++){	
		
		//To give the motor appropriate postition
		motors[i] = rand1()*2*MAX_DIST - MAX_DIST + cargo_pos;

	}

}

float calc_force(){	 //To calculate the force at that point

	float force = 0;

	for(int i = 0; i<N; i++){

		if(abs(motors[i] - cargo_pos) > STALK_LENGTH){

			if(motors[i] - cargo_pos <0){
				
				force += K*(motors[i] - cargo_pos + STALK_LENGTH);
			}
			else{

				force += K*(motors[i] - cargo_pos - STALK_LENGTH);
			}

		}
	}

	return force-F;

}


int main(){

	place_motors();

	for(int i =0; i<N; i++){

		cout<<motors[i]<<" ";

	}
	cout<<endl;

	float force;

	do{

		force = calc_force();

		if(force>=0){

			cargo_pos += DELTA;

		}

		else{

			cargo_pos -= DELTA;
		}

	}while(force > EPS);

	cout<<cargo_pos<<endl;

	return 0;
}