#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"
using namespace std;


#define Z_KEY 0x5A
#define X_KEY 0x58
#define N_KEY 0x4E
#define M_KEY 0x4D

gameResult MusicGame::game(int i){
	cout << "gamestart" << endl;
	int cur_page = 0;
	
	cleardevice();

	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	
	void *BG =malloc(imagesize(0, 0, 1440, 900));     //Check if PV image is PNG
	if(songs[i].backGround.substr(songs[i].backGround.size()-4) != ".png"){
		readimagefile( (songs[i].dir + songs[i].backGround).c_str(), 0, 0, 1440, 900);
	}
	else{
		readimagefile( ".\\resources\\bg.jpg", 0, 0, 1440, 900);
	}
	getimage(0, 0, 1440, 900, BG);
	
	void *N[10];
	for(int j = 0; j < 10; j++){
		N[j] = malloc(imagesize(0, 0, 47 ,64));
		sprintf(tmp, ".\\resources\\%d.jpg", j);
		readimagefile(tmp, 0, 0, 47, 64);
		getimage(0, 0, 47, 64, N[j]);
	}
	
	/*void *zero = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\0.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, zero);
	void *one = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\1.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, one);
	void *two = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\2.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, two);
	void *three = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\3.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, three);
	void *four = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\4.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, four);
	void *five = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\5.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, five);
	void *six = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\6.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, six);
	void *seven = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\7.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, seven);
	void *eight = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\8.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, eight);
	void *nine = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\9.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, nine);*/
	
	void *perfect = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\perfect.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, perfect);
	void *great = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\great.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, great);
	void *good = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\good.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, good);
	void *bad = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\bad.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, bad);
	void *miss = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\miss.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, miss);
	
	
	void *paused = malloc(imagesize(0, 0, 1240, 200));
	readimagefile( ".\\resources\\paused2.jpg", 200, 350, 1440, 550);  
	getimage(200, 350, 1440, 550, paused);
	void *pause_back = malloc(imagesize(0, 0, 1440, 200));
	readimagefile( ".\\resources\\pause_back.jpg", 0, 0, 1440, 200);  
	getimage(0, 0, 1440, 200, pause_back);
	
	putimage(0, 0, BG, COPY_PUT);
	
	
	
	
	

	//load resources;
	//convert beatmap
	
//start music
	char re[20];
	string mciCommand = "open \"" + songs[i].dir + songs[i].AudioFilename + "\" type mpegvideo alias mp3";
	cout << "open mp3 " << songs[i].AudioFilename << endl;
	mciSendString(mciCommand.c_str(), re, 20, NULL);
	cout << "MCI return " << re << endl;
	
	mciSendString("status mp3 length", re, 20, 0);
	int length = atoi(re);
	gameResult result = {0};
	int position = 0;  //music position
	int old = 0;  
	int *keySig = (int*)malloc(sizeof(int)*gameMode);  //key signal
	int *lastkeySig = (int*)malloc(sizeof(int)*gameMode);  //last key signal, for detecting edges
	
	result.life = 1000;
	result.passed = 1;
	int last = 0;
	int esc = 0;  //pause key
	
	
	for(int j = 0; j < songs[i].hitobjects.size(); j++){
		cout << songs[i].hitobjects[j].x << ", " << songs[i].hitobjects[j].y << ", " << songs[i].hitobjects[j].time << endl;
	} 
	
	
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
	mciSendString("play mp3", NULL, 0, NULL);
	while(position+offset < length){
		
		cur_page = -cur_page+1;
		setactivepage(cur_page);
		
		cleardevice();
		putimage(0, 0, BG, COPY_PUT);

		setfillstyle(1, BLACK);
		bar(columnPosition, 0, columnPosition+columnWidth*gameMode, 900);
		
		//settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
		sprintf(tmp, "%dx", result.combo);
		outtextxy(columnPosition+150, 200, tmp);
//put image 
		if(last == 0)	putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, miss, COPY_PUT);
		else if(last == 1)	putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, perfect, COPY_PUT);
		else if(last == 2)	putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, great, COPY_PUT);
		else if(last == 3)	putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, bad, COPY_PUT);

//draw lines	
		setcolor(WHITE);
		for(int j = 0; j <= gameMode; j++){
			line(columnPosition+columnWidth*j, 0, columnPosition+columnWidth*j, 900);
		}
		line(columnPosition, 800, columnPosition+gameMode*columnWidth, 800);
		
				setfillstyle(1, WHITE);
		for(int j = 0; j < 4; j++){
			if(keySig[j]==1){
				bar(columnPosition+columnWidth*j, 800, columnPosition+columnWidth*(j+1), 900);
			}
		}
		
//judgement and print notes start
//cout << "judgement and print notes start" << endl;
		mciSendString("status mp3 position", re,20, 0);
		position = atoi(re);
		
		
		
		position += offset;
		
		 
		
		setfillstyle(1, WHITE);
		//cout << lastkeySig[0]  << keySig[0] << lastkeySig[1]  << keySig[1] <<lastkeySig[2]  << keySig[2] <<lastkeySig[3]  << keySig[3] << endl;
		
		for(int j = 0; j < songs[i].hitobjects.size(); j++){
			if(songs[i].hitobjects[j].hit == 0) continue;
			int ato = songs[i].hitobjects[j].time - position;
			if(ato > 2000) continue;
			
			int y = 800-speed*ato;
			
			int each = 1;
			
			if(j != 0){
				int xOffset = (songs[i].hitobjects[j].x - songs[i].hitobjects[j-1].x);
				int yOffset = (songs[i].hitobjects[j].y - songs[i].hitobjects[j-1].y);
				int timeOffset = (songs[i].hitobjects[j].time - songs[i].hitobjects[j-1].time);
				if(timeOffset != 0) {
					each = (xOffset*xOffset + yOffset*yOffset) / timeOffset;
					if(each < 120) each = 1;
					else if(each < 200) each = 2;
					else if(each < 270) each = 3;
					else each = 4;
				}
				
			}
			//if(songs[i].hitobjects[j].hit == -1)songs[i].hitobjects[j].hit = (1<<(each)) -1;  //if number of multi key hasn't be calculated, set to full in binary
			//minus to 0 means all keys have been hit
//cout << "mk " << songs[i].hitobjects[j].hit << "with each " << each << endl; 
			
			int *Locas = (int*)malloc(sizeof(int)*each);
			Locas[0] = (songs[i].hitobjects[j].x+songs[i].hitobjects[j].time)%gameMode;
			for(int k = 1; k < each; k++){
				Locas[k] = (Locas[0] + (songs[i].hitobjects[j].y*songs[i].hitobjects[j].x)%gameMode)%gameMode;
				for(int l = 0; l < k; l++){
					if(Locas[l] == Locas[k]){
						Locas[k] = (Locas[k]+1)%gameMode;
						l--;
					}
				}
			}
			
			if(songs[i].hitobjects[j].hit == -1){
				songs[i].hitobjects[j].hit = 0;
				for(int k = 0; k < each; k++){
					songs[i].hitobjects[j].hit += 1<<(Locas[k]);
				}
			}
//cout << "multi-key cal finished" << endl;
			for(int k = 0; k < each; k++){ 
				int tmp = (1<<(Locas[k])) & songs[i].hitobjects[j].hit;
				if( tmp == 0) continue;
				//cout << songs[i].hitobjects[j].hit << endl;
				if(keySig[Locas[k]] == 1 && lastkeySig[Locas[k]] == 0){  //detect positive edge
					if(ato < 128 && ato > -128){
//cout << "detected key " << Locas[k] << " pressed" << endl;
//cout << "active note in " << songs[i].hitobjects[j].time << endl;
						songs[i].hitobjects[j].hit-= (1<<(Locas[k]));	
//cout << "hit left " << 	songs[i].hitobjects[j].hit << endl;
						
						if(ato > 84 || ato < -84){
							result.bad++;
							result.life -= 75;
							last = 3;
						}
						else if(ato > 38 || ato < -38){
							result.great++;
							last = 2;
						}
						else {
							result.perfect++;
							result.life += 25;
							if(result.life >= 1000) result.life = 1000;
							last = 1;
						}
						result.combo++;
						if(result.combo>result.maxcombo)result.maxcombo = result.combo;
						lastkeySig[Locas[k]] = 1;

//cout << "key " << Locas[k] << " positive edge removed" << endl;

					}
				}
				

				
				
				if(ato < -128){
					songs[i].hitobjects[j].hit-=(1<<(Locas[k]));
					last = 0;
					result.combo=0;
					result.life -= 100;
				}
				
				
				
				
				bar(columnPosition+Locas[k]*columnWidth , y-20, columnPosition+(Locas[k]+1)*columnWidth, y);
			}
			free(Locas);
			
			
		}
//cout << "judge finished" <<endl; 
		
		
		
//life

		if(result.life < 0){
			cout << "failed" << endl;
			result.passed = 0;
		}		
		
		setvisualpage(cur_page);

		
		lastkeySig[0] = keySig[0];
		lastkeySig[1] = keySig[1];
		lastkeySig[2] = keySig[2];
		lastkeySig[3] = keySig[3];
		
        
        
        if(GetAsyncKeyState(Z_KEY)!=0) keySig[0]=1;
        else keySig[0]=0;
        if(GetAsyncKeyState(X_KEY)!=0) keySig[1]=1;
        else keySig[1]=0;
        if(GetAsyncKeyState(N_KEY)!=0) keySig[2]=1;
        else keySig[2]=0;
        if(GetAsyncKeyState(M_KEY)!=0) keySig[3]=1;
        else keySig[3]=0;
        
        
		if(GetAsyncKeyState(0x1B)!=0 && !esc){  //escape
			mciSendString("pause mp3", NULL, 0, NULL);
			int opt = pauseScreen(paused, pause_back);
			if(opt == 1){
				Sleep(300);
			}
			else if(opt == 2){
				//renew map 
			}
			else if(opt == 3){
				goto END;
			}
			mciSendString("resume mp3", NULL, 0, NULL);
			esc = 1;
		}
		else esc = 0;
		

		Sleep(8);
		
		
	}
	
	
	END:
	songs[i].timingpoints.clear();
	songs[i].hitobjects.clear();
	free(BG);
	mciSendString("stop mp3", NULL, 0, NULL);
	mciSendString("close mp3", NULL, 0, NULL);
	//return result;
	
}
