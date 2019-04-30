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
	
	
	/*void *perfect = malloc(imagesize(0, 0, 256, 72));
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
	getimage(0, 0, 256, 72, miss);*/
	
	void *judge[5][2];
	judge[0][0] = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\B_perfect.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, judge[0][0]);
	judge[0][1] = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\F_perfect.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, judge[0][1]);
	judge[1][0] = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\B_great.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, judge[1][0]);
	judge[1][1] = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\F_great.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, judge[1][1]);
	judge[2][0] = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\B_good.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, judge[2][0]);
	judge[2][1] = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\F_good.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, judge[2][1]);
	judge[3][0] = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\B_bad.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, judge[3][0]);
	judge[3][1] = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\F_bad.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, judge[3][1]);
	judge[4][0] = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\B_miss.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, judge[4][0]);
	judge[4][1] = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\F_miss.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, judge[4][1]);

	
	
	
	
	
	
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
	int last = -1;
	int esc = 0;  //pause key
	
	
	/*for(int j = 0; j < songs[i].hitobjects.size(); j++){
		cout << songs[i].hitobjects[j].x << ", " << songs[i].hitobjects[j].y << ", " << songs[i].hitobjects[j].time << endl;
	} */
	
	
	
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
	mciSendString("play mp3", NULL, 0, NULL);
	
	
//start loop
	while(songs[i].hitobjects.back().time - offset > position/*position+offset < length*/){
		
		cur_page = -cur_page+1;
		setactivepage(cur_page);
		
		cleardevice();
		putimage(0, 0, BG, COPY_PUT);

		setfillstyle(1, BLACK);
		bar(columnPosition, 0, columnPosition+columnWidth*gameMode, 900);
		
		//settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
		//sprintf(tmp, "%dx", result.combo);
		//outtextxy(columnPosition+150, 200, tmp);
		int t = 100000;
		
		for(int j = 6; j > 0; j--){
			if(result.combo % t != result.combo){
				int t2 = j;
				t*=10;
				for(; j >0; j--){
					putimage(columnPosition+((columnWidth*gameMode)-(t2*47))/2 + 47*(t2-j), 200, N[(result.combo % t )/(t/10)], COPY_PUT);
					t/=10;
				}
				break;
			}
			t/=10;
		}
		
		t = 10;
		for(int j = 0; j < 10; j++){
			putimage(1440-47*j, 0, N[result.score%t / (t/10)], COPY_PUT);
			t*=10;
		}
		
		setcolor(CYAN);
		arc(columnPosition+columnWidth*gameMode/2, 232, 90, result.life*360/1000+90, 110);//life
		setcolor(WHITE);
		
//put judgement image back
		t = last;
		if(t != -1){
			putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, judge[t][0], XOR_PUT);
		}
		

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
					if(each < 150) each = 1;
					else if(each < 220) each = 2;
					else if(each < 300) each = 3;
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
					if(ato < 135 && ato > -135){
//cout << "detected key " << Locas[k] << " pressed" << endl;
//cout << "active note in " << songs[i].hitobjects[j].time << endl;
						songs[i].hitobjects[j].hit-= (1<<(Locas[k]));	
//cout << "hit left " << 	songs[i].hitobjects[j].hit << endl;
						
						if(ato > 75 || ato < -75){
							result.bad++;
							result.life -= 35;
							result.score += 100+100.0*(result.combo*result.combo)/(5000*5000);
							last = 3;
						}
						else if(ato > 50 || ato < -50){
							result.good++;
							result.score += 300+300.0*(result.combo*result.combo)/(5000*5000);
							last = 2;
						}
						
						else if(ato > 25 || ato < -25){
							result.great++;
							result.life += 5;
							result.score += 600+600.0*(result.combo*result.combo)/(5000*5000);
							last = 1;
						}
						else {
							result.perfect++;
							result.life += 25;
							if(result.life >= 1000) result.life = 1000;
							result.score += 1200+1200.0*(result.combo*result.combo)/(5000*5000);
							last = 0;
							
						}
						result.combo++;
						if(result.combo>result.maxcombo)result.maxcombo = result.combo;
						lastkeySig[Locas[k]] = 1;

//cout << "key " << Locas[k] << " positive edge removed" << endl;

					}
				}
				if(ato < -135){
					songs[i].hitobjects[j].hit-=(1<<(Locas[k]));
					last = 4;
					result.miss++;
					result.combo=0;
					result.life -= 75;
				}
				
				
				
				
				bar(columnPosition+Locas[k]*columnWidth , y-20, columnPosition+(Locas[k]+1)*columnWidth, y);
			}
			free(Locas);
			
			
		}
//cout << "judge finished" <<endl; 

//put judgement image front
		if(t != -1){
			putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, judge[t][0], XOR_PUT);
			putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, judge[t][1], OR_PUT);
		}
		
		
		
		
//life

		setvisualpage(cur_page);

		if(result.life < 0){
			cout << "failed" << endl;
			result.passed = 0;
			goto RESULT;
		}
		else if(result.life > 1000){
			result.life = 1000;
		}	
		//cout << result.life << endl;
		

		
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
	
	Sleep(1000);
	RESULT:
		
	putimage(0, 0, BG, COPY_PUT);
	
	sprintf(tmp, "%d", result.perfect);
	outtextxy(550, 300, tmp);
	sprintf(tmp, "%d", result.great);
	outtextxy(550, 400, tmp);
	sprintf(tmp, "%d", result.good);
	outtextxy(550, 500, tmp);
	sprintf(tmp, "%d", result.bad);
	outtextxy(550, 600, tmp);
	sprintf(tmp, "%d", result.miss);
	outtextxy(550, 700, tmp);
	if(result.passed == 0){
		outtextxy(200, 200, "FAILED");
	}
	else{
		sprintf(tmp, "%d", result.score);
		outtextxy(200, 200, tmp);
		
	}
	
	
	putimage(200, 300, judge[0][1], COPY_PUT);
	putimage(200, 400, judge[1][1], COPY_PUT);
	putimage(200, 500, judge[2][1], COPY_PUT);
	putimage(200, 600, judge[3][1], COPY_PUT);
	putimage(200, 700, judge[4][1], COPY_PUT);
	
	getch();

	
	
	END:
	songs[i].timingpoints.clear();
	songs[i].hitobjects.clear();
	free(BG);
	for(int j = 0; j < 10; j++){
		free(N[j]);
	}
	for(int j = 0; j < 5; j++){
		free(judge[j][0]);
		free(judge[j][1]);
	}
	free(paused);
	free(pause_back);
	mciSendString("stop mp3", NULL, 0, NULL);
	mciSendString("close mp3", NULL, 0, NULL);
	//return result;
	
}
