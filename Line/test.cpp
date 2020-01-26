#include <bits/stdc++.h>
using namespace std;

void drawline4(int x0,int y0,int x1,int y1){
    int dx = x1-x0;
    int dy = y1-y0;
    int x=x0;
    int y=y0;
    int d = -2*dy+dx;
    int dSW = -2*(dy-dx);
    int dW = -2*dy;
    //glVertex2i(x, y);
    while(x>=x1){
    	cout<<d<<endl;
    	
        if(d<0){  //dW
            x--;
            d+=dW;
            cout<<"dw "<<dW<<" d = "<<d<<endl;
        }
        else{		//dSW
            x--;
            y--;
            d+=dSW;
            cout<<"dw "<<dSW<<" d = "<<d<<endl;
        }
        cout<<"("<<x<<","<<y<<")"<<endl;
    }
}


void findzone(int x0,int y0,int x1,int y1){
    int dx = x1-x0;
    int dy = y1-y0;
    if (dx >= 0 && dy >= 0){        //zone 0 or zone 1
        if (dx>=dy) {                //zone 0
            //drawline0( x0, y0, x1, y1);
        }
        else{} //drawline1( x0, y0, x1, y1);        //zone 1
    }
    else if (dx<0 && dy>=0){        //zone 2 or zone 3
        if(abs(dx)>=dy) {			//zone 3
        	//drawline3( x0, y0, x1, y1);     
        	//glVertex2i(-20, 10);
        	}   
        else {       //zone 2
        	//drawline2( x0, y0, x1, y1);
        	//glVertex2i(-10, 20);       
        }
    }
    else if (dx<0 && dy<0){         //zone 4 or zone 5
        if(abs(dx)>=abs(dy)) drawline4( x0, y0, x1, y1);        //zone 4
        else {}//drawline5( x0, y0, x1, y1);      //zone 5
    }
    else{                            // zone 6 or zone 7
    
        if(dx>=abs(dy)){} //drawline7( x0, y0, x1, y1);        //zone 7
        else {}//drawline6( x0, y0, x1, y1);              //zone 6
    }
    
    return;
}


int main()
{

	cout<<"check"<<endl;
	findzone(0,0,-5,-3);
	return 0;

}