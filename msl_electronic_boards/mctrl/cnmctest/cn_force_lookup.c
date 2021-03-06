#include "cn_force_lookup.h"
#include "math.h"
#include "cn_led.h"
#include "cn_time.h"

//map_point xhuge lookup[LINE_WIDTH*LINE_WIDTH];
#ifdef TMC
#include "table3k4k.h"
// MOPS:
// #include "table3.5k3.5k.h"
#endif
#ifdef VMC
#include "table2.6k3.4k.h"
#endif
//note: lookup _must_ be indexed with uword at least (more than 2^15 entries)



void cn_init_force_lookup() {
	/*uword i;
	for(i = 0; i< LINE_WIDTH*LINE_WIDTH; ++i) {
				lookup[i].x = 0;
				lookup[i].y = 0;
	}*/
	initTable();
}

/*__inline float dMod(float x, float y) {
		 return x-floor(x/y)*y;
}*/


//should be called from controller_commit, probably disable timeout beforehand
void cn_calc_force_lookup(float minAccel, float maxAccel) {
	//sword i,j;
	sword x,y;
	float angle,dist;
	float angle2, axisAngle;
	float ftemp;
	float p1x,p1y,p2x,p2y,p3x,p3y;
	float abx,aby;
	float a,b,c;
	float axisPx[3], axisPy[3];
	float baxPx[3], baxPy[3];
	float circAngleDelta;
	uword axisI;
	udword curIdx = 0;	
	//udword now = cn_getRTC();
	//udword ttime;
	
	//cn_stop_command_timeout();
#ifdef VMC
redLedOff();
#endif	
	//c is the vector distance along the robot axis vector to the edge of the circle segment from the edge in between axis
	c = - minAccel/(maxAccel*2);  //c = minAccel * cos(2*PI/3) / maxAccel;
	c += sqrt( c*c - minAccel*minAccel/(maxAccel*maxAccel) +1);	
	
	axisPy[0] = 0;//sin(0)*maxAccel;
	axisPx[0] = maxAccel;//cos(0)*maxAccel;
	
	axisPy[1] = sin(TWO_PI_THIRD)*maxAccel;
	axisPx[1] = cos(TWO_PI_THIRD)*maxAccel;
	
	axisPy[2] = sin(FOUR_PI_THIRD)*maxAccel;
	axisPx[2] = cos(FOUR_PI_THIRD)*maxAccel;
	
	baxPy[0]  = sin(PI_THIRD)*minAccel;
	baxPx[0]  = cos(PI_THIRD)*minAccel;

	baxPy[1]  = 0;//*minAccel; //sin(3*PI/3)
	baxPx[1]  = -minAccel; //cos(3*PI/3)

	baxPy[2]  = sin(5*PI_THIRD)*minAccel;
	baxPx[2]  = cos(5*PI_THIRD)*minAccel;
	
	//the delta angle between the axis and the circle segment edge:
	p3x = baxPx[0] + axisPx[0]*c;
    p3y = baxPy[0] + axisPy[0]*c;
	circAngleDelta = ABS(DMOD(atan2(p3y,p3x),TWO_PI));
	
	for(x = -FORCE_RANGE; x <= FORCE_RANGE; ++x) { 
		//ttime = cn_getRTC();
		//printf("I: %d T: %lu\n",x,(ttime-now));
		//ledToggle();
		//now = cn_getRTC();
		
		for(y = -FORCE_RANGE; y <= FORCE_RANGE; ++y) {
		
//				x =i - FORCE_RANGE;
//				y =j - FORCE_RANGE;
				dist = sqrt(x*x+y*y); //the length of the force vector
				angle = atan2(y,x);   //its angle
				if (angle < 0) angle += TWO_PI;
				
							
				if(angle > FOUR_PI_THIRD) {
					axisI = 2;
					axisAngle = FOUR_PI_THIRD;
				}
				else if (angle > TWO_PI_THIRD) {
					 axisI=1;
					 axisAngle = TWO_PI_THIRD;
				}
				else {
					axisI = 0;
					axisAngle = 0;
				}
				
				//angle2 = DMOD(angle,TWO_PI_THIRD);
				angle2 = angle - axisAngle;
				
//				if (angle > 2*TWO_PI_THIRD) ftemp = 2*TWO_PI_THIRD;
//    			else if (angle > TWO_PI_THIRD) ftemp = TWO_PI_THIRD;
//    			else ftemp =0; 
				
				//Calculate the relevant line segment:
				
				if (angle2 < PI_THIRD) {
					//axisAngle = ftemp;
					p1y = axisPy[axisI];//sin(ftemp)*maxAccel;
					p1x = axisPx[axisI];//cos(ftemp)*maxAccel;
					p2y = baxPy[axisI];//sin(ftemp+PI_THIRD)*minAccel;
					p2x = baxPx[axisI];//cos(ftemp+PI_THIRD)*minAccel;
				}				
				else {
					//axisAngle = ftemp+TWO_PI_THIRD;
					axisAngle +=TWO_PI_THIRD;
					p2y = baxPy[axisI];//sin(ftemp+PI_THIRD)*minAccel;
					p2x = baxPx[axisI];//cos(ftemp+PI_THIRD)*minAccel;
					axisI = (axisI+1 ) % 3;
					p1y = axisPy[axisI];//sin(ftemp+TWO_PI_THIRD)*maxAccel;
					p1x = axisPx[axisI];//cos(ftemp+TWO_PI_THIRD)*maxAccel;
				}
				//Linear Combination:
				b = (y-x/p1x*p1y) / (p2y-p2x/p1x*p1y);
    			a = (x-b*p2x) / p1x;
    		
    		
    			if (dist <= maxAccel && b <= 1.0) { //vector is within 'green area'
					lookup[curIdx].x = 0;
					lookup[curIdx].y = 0;
					curIdx++;
	    			continue;
    			}
				//simplified table:
				
				a = CLAMP(a,0.0,1.0);
				b = CLAMP(b,0.0,1.0);
				abx = a * p1x + b * p2x;
				aby = a * p1y + b * p2y;
				ftemp = sqrt(abx*abx+aby*aby);
				if (ftemp > maxAccel) {
					ftemp = maxAccel/ftemp;
					abx *= ftemp;
					aby *= ftemp;
				}
				lookup[curIdx].x = (sword)ROUND((float)x-abx);
				lookup[curIdx].y = (sword)ROUND((float)y-aby);
				curIdx++;
				//simplified table end
				/*
				//the point at the edge of the relevant circle segment:
				p3x = p2x + p1x*c;
    			p3y = p2y + p1y*c;				
				
				abx = p3x-p2x;
    			aby = p3y-p2y;
				//the vector distance  along the line parallel to the robots axis
    			ftemp = ( (x - p2x)*(p3x - p2x) + (y - p2y)*(p3y - p2y) )/ (abx*abx + aby*aby);				
				ftemp = CLAMP(ftemp,0.0,1.0);

				
				
				
				
				if (dist >= maxAccel && circAngleDelta >= ABS(angle-axisAngle)) {
				//vector is mapped onto circle segment
					lookup[curIdx].x = (sword)ROUND((float)x-(((float)x)*maxAccel/dist));
					lookup[curIdx].y = (sword)ROUND((float)y-(((float)y)*maxAccel/dist));
					curIdx++;
					continue;
        		}
				lookup[curIdx].x = (sword)ROUND((float)x-(p2x+ftemp*abx));  		
    			lookup[curIdx].y = (sword)ROUND((float)y-(p2y+ftemp*aby));
				curIdx++;
				*/
		}
	}
//	greenLedOn();
#ifdef VMC
redLedOn();
#endif
}

void cn_get_force_correction(sdword* force_vector, sdword* correction) {
	uword idx = (uword)(((sword)force_vector[0]+FORCE_RANGE)*LINE_WIDTH+FORCE_RANGE+(sword)force_vector[1]);
	correction[0] = lookup[idx].x;
	correction[1] = lookup[idx].y;
}
void cn_get_force_correction_by_idx(uword idx, sword* result) {
	result[0] = lookup[idx].x;
	result[1] = lookup[idx].y;
}

