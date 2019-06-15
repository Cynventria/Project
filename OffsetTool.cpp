#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"
using namespace std;

void MusicGame::OffsetTool(){
	int cur_page = 0;
	
	setvisualpage(0);
	setactivepage(0);
	
	readimagefile( ".\\resources\\bg.jpg", 0, 0, 1440, 900);
	void *BG = malloc(imagesize(0, 0, 1440, 900));
	getimage(0, 0, 1440, 900, BG);
	
	setactivepage(1);
	void *light = malloc(imagesize(0, 0, columnWidth, 500));
	readimagefile(".\\resources\\light.jpg", 0, 0, columnWidth, 500);
	getimage(0, 0, columnWidth, 500, light);
	

	
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	
	int keySig = 0;
	int lastkeySig = 0;
	int first = 7953;
	
	int sum = 0;
	int clicked = 0;
	
	int position = 0;
	
	
	char re[20];
	mciSendString("open \".\\resources\\adj.mp3\" type mpegvideo alias mp3", re, 20, NULL);
	cout << re << endl;
	mciSendString("play mp3", NULL, 0, NULL);
	//2370 129
	while(position < 39270){
		setvisualpage(cur_page);
		cur_page = -cur_page+1;
		setactivepage(cur_page);
		
		cleardevice();
		putimage(0, 0, BG, COPY_PUT);
		
		setfillstyle(1, BLACK);
		bar(columnPosition, 0, columnPosition+columnWidth, 900);
		line(columnPosition, 800, columnPosition+columnWidth, 800);

		
		setfillstyle(1, WHITE);
		if(keySig){
			putimage(columnPosition, 300, light, COPY_PUT);
			bar(columnPosition, 800, columnPosition+columnWidth, 900);
		}
			
		if(keySig ==1 &&  lastkeySig == 0){
			PlaySound(".\\resources\\normal.wav", NULL, SND_FILENAME | SND_ASYNC);  
		}
		
		mciSendString("status mp3 position", re,20, 0);
		position = atoi(re);
		setfillstyle(1, WHITE);
		
		for(float i = first; i < 37600; i+=465.12){
			if(keySig == 1 && lastkeySig == 0){
				if(i-position < 200 && i-position > -200){
					sum += (i-position);
					clicked++;
					first = i;
				}
			}
			
			bar(columnPosition, 800-speed*(i-position)+20, columnPosition+columnWidth, 800-speed*(i-position));
		}
		
		lastkeySig = keySig;
		if(GetAsyncKeyState(keys[0])!=0) keySig = 1;
		else keySig=0;
		
		if(GetAsyncKeyState(0x1B)!=0){
			mciSendString("stop mp3", NULL, 0, NULL);
			mciSendString("close mp3", NULL, 0, NULL);
			free(BG);
			free(light);
			return;
		}
		
		
		line(columnPosition, 0, columnPosition, 900);
		line(columnPosition+columnWidth, 0, columnPosition+columnWidth, 900);
		Sleep(5);
		
		
	}
	
	mciSendString("stop mp3", NULL, 0, NULL);
	mciSendString("close mp3", NULL, 0, NULL);
	free(BG);
	free(light);
	
	offset = sum/clicked;
	return;
		
}
