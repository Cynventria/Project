#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"
using namespace std;

int MusicGame::pauseScreen(void *paused, void *pause_back){
	void *frame = malloc(imagesize(0, 0, 1440, 900));
	getimage(0, 0, 1440, 900, frame);
	
	int cur_page=0;
	
	/*void *paused = malloc(imagesize(0, 0, 1240, 200));
	readimagefile( ".\\resources\\paused2.jpg", 200, 350, 1440, 550);  
	getimage(200, 350, 1440, 550, paused);
	
	
	void *pause_back = malloc(imagesize(0, 0, 1440, 200));
	readimagefile( ".\\resources\\pause_back.jpg", 0, 0, 1440, 200);  
	getimage(0, 0, 1440, 200, pause_back);*/
	
	for(int i = 0; i <= 10; i++){
		cur_page = -cur_page + 1;    //0 1 toggle
        setactivepage(cur_page);
   		cleardevice();
   		
   		putimage(1440-i*144, 350, pause_back, COPY_PUT);
   		putimage(0, 0, frame, OR_PUT);
   		putimage(1440-i*144 + 250, 350, paused, COPY_PUT);
   		Sleep(5);
   		
   		setvisualpage(cur_page);
	}
	int clicked = 0;
	while(1){
		if(GetAsyncKeyState(0x01)!=0){
			cout << mousex() << ", " << mousey() << endl;
			if(mousex() > 850 && mousex() < 951 && mousey() > 375 && mousey() < 505){
				clicked = 1;
			}
			else if(mousex() > 1050 && mousex() < 1181 && mousey() > 375 && mousey() < 505){
				clicked = 2;
			}
			else if(mousex() > 1250 && mousex() < 1381 && mousey() > 375 && mousey() < 505){
				clicked = 3;
			}
		}
		if(clicked)  break;
	}
	
	for(int i = 10; i >=0; i--){
		cur_page = -cur_page + 1;    //0 1 toggle
        setactivepage(cur_page);
   		cleardevice();
   		
   		putimage(1440-i*144, 350, pause_back, COPY_PUT);
   		putimage(0, 0, frame, OR_PUT);
   		putimage(1440-i*144 + 250, 350, paused, COPY_PUT);
   		Sleep(5);
   		
   		setvisualpage(cur_page);
	}
	

	return clicked;
	
	
}
