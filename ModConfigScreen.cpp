#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"
using namespace std;

void MusicGame::ModconfigScreen(void *frame){
	/*
	1-NF
	2-No-Line
	3-reverse
	4-free drop
	5-shiver
	6-dynamic
	7-earthquake
	8-twist	
	*/
	
	int curpage = 0;
	setactivepage(0);
	setvisualpage(0);
	putimage(0, 0, frame, COPY_PUT);
	
	
	setactivepage(1);
	void *MODconfig = malloc(imagesize(0, 0, 1440, 200));
	readimagefile(".\\resources\\config-3.jpg", 0, 700, 1440, 900);
	getimage(0, 700, 1440, 900, MODconfig);
	
	void *resetClicked = malloc(imagesize(0, 0, 200, 100));
	readimagefile(".\\resources\\config-3-2.jpg", 0, 700, 1440, 900);
	getimage(0, 800, 200, 900, resetClicked);
	
	cout << imagesize(0, 0, 100, 0) << endl;
	
	void *ModClicked[6][200];
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 200; j++){
			ModClicked[i][j] = malloc(imagesize(0, 0, 100, 0));
			getimage(400+ (100*i) -(j/2), 700+j , 500 + (100*i) -(j/2), 700+j, ModClicked[i][j]);
		}
	}
	
		
	for(int i = 1; i <= 5; i++){
		curpage = (curpage+1) % 2;
		setactivepage(curpage);
		
		putimage(0, 700, MODconfig, COPY_PUT);
		putimage(0, 0- (i*40), frame, COPY_PUT);
		
		setvisualpage(curpage);
		Sleep(10);
	} 
	

	
	int mx, my;
	int on = -5;
	
	while(1){
		mx = mousex();
		my = mousey();
		
		if(my < 700){
			if(ismouseclick(WM_LBUTTONDOWN)){
				clearmouseclick(WM_LBUTTONDOWN);
				break;
			}
		}
		if(mx > 10 && mx < 190 && my > 810 && my < 875){
			on = -1;
			if(ismouseclick(WM_LBUTTONDOWN)){
				clearmouseclick(WM_LBUTTONDOWN);
				mods = 0;	
				cout << "0" << endl;
			}
		}
		for(int i = 0; i < 6; i++){
			if(mx > 300 && my > 700 &&
			 2*(mx-300) + (my-700) -200 > 200*i && 
			 2*(mx-300) + (my-700) -200 < 200+200*i){
				on = i;
				if(ismouseclick(WM_LBUTTONDOWN)){
					clearmouseclick(WM_LBUTTONDOWN);
					mods = mods ^ (1<<i);
					cout << mods << endl;
				}
			}
		}
		
		setactivepage(curpage);
		
		setbkcolor(BLACK);
		setcolor(WHITE);
		cleardevice();
		
		putimage(0, -200, frame, COPY_PUT);
		putimage(0, 700, MODconfig, COPY_PUT);
		
		if(on == -1){
			putimage(0, 800, resetClicked, COPY_PUT);
		}
		for(int i = 0; i <6; i++){
			if(mods & (1<<i) || on == i){
				for(int j = 0; j < 200; j++){
					putimage(400+ (100*i) -(j/2), 700+j , ModClicked[i][j], COPY_PUT);
				}
			}
		}
		
		setvisualpage(curpage);
		curpage = (curpage+1) % 2;
		
		on = -5;
		Sleep(10);
		
	}
	
	

	
	
	for(int i = 5; i >= 0 ; i--){

		curpage = (curpage+1) % 2;
		setactivepage(curpage);
		
		putimage(0, 700, MODconfig, COPY_PUT);
		putimage(0, 0- (i*40), frame, COPY_PUT);
		
		setvisualpage(curpage);
		Sleep(10);
	}
	
	free(MODconfig);
	free(resetClicked);
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 200; j++){
			free(ModClicked[i][j]);
		}
	}
	
	
}
