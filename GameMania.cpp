#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <Math.h>
#include "MusicGame.h"
using namespace std;


#define Z_KEY 0x5A
#define X_KEY 0x58
#define N_KEY 0x4E
#define M_KEY 0x4D

gameResult MusicGame::game(int i){
	START:
	cout << "gamestart" << endl;
	
	int cur_page = 0;
	
	cleardevice();

	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	
	setvisualpage(0);
	setactivepage(0);
	
	void *BG =malloc(imagesize(0, 0, 1440, 900));     //Check if PV image is PNG
	if(songs[i].backGround.substr(songs[i].backGround.size()-4) != ".png"){
		readimagefile( (songs[i].dir + songs[i].backGround).c_str(), 0, 0, 1440, 900);
	}
	else{
		readimagefile( ".\\resources\\bg.jpg", 0, 0, 1440, 900);
	}
	getimage(0, 0, 1440, 900, BG);
	
	setvisualpage(0);
	setactivepage(1);
	
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

	
	void *light = malloc(imagesize(0, 0, columnWidth, 500));
	if(mods & 4) readimagefile(".\\resources\\light-reverse.jpg", 0, 0, columnWidth, 500);
	else readimagefile(".\\resources\\light.jpg", 0, 0, columnWidth, 500);
	getimage(0, 0, columnWidth, 500, light);
	
	/*void *lights[4];
	lights[0] = malloc(imagesize(0, 0, columnWidth, 500));
	readimagefile(".\\resources\\light-PERFECT.jpg", 0, 0, columnWidth, 500);
	getimage(0, 0, columnWidth, 500, lights[0]);
	lights[1] = malloc(imagesize(0, 0, columnWidth, 500));
	readimagefile(".\\resources\\light-PERFECT.jpg", 0, 0, columnWidth, 500);
	getimage(0, 0, columnWidth, 500, lights[1]);
	lights[2] = malloc(imagesize(0, 0, columnWidth, 500));
	readimagefile(".\\resources\\light-PERFECT.jpg", 0, 0, columnWidth, 500);
	getimage(0, 0, columnWidth, 500, lights[2]);
	lights[3] = malloc(imagesize(0, 0, columnWidth, 500));
	readimagefile(".\\resources\\light-PERFECT.jpg", 0, 0, columnWidth, 500);
	getimage(0, 0, columnWidth, 500, lights[3]);*/
	
	
	
	void *paused = malloc(imagesize(0, 0, 1240, 200));
	readimagefile( ".\\resources\\paused2.jpg", 200, 350, 1440, 550);  
	getimage(200, 350, 1440, 550, paused);
	void *pause_back = malloc(imagesize(0, 0, 1440, 200));
	readimagefile( ".\\resources\\pause_back.jpg", 0, 0, 1440, 200);  
	getimage(0, 0, 1440, 200, pause_back);
	
	
	
	
	putimage(0, 0, BG, COPY_PUT);
	
	
	

	//load resources;
//convert beatmap
	
	vector< vector<hobj> > map(gameMode);
	
	for(int j = 0; j < songs[i].hitobjects.size(); j++){

	
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
		
		for(int k = 0; k < each; k++){
			map[Locas[k]].push_back( hobj(songs[i].hitobjects[j].time, songs[i].hitobjects[j].length * songs[i].hitobjects[j].repeat / (100.0*songs[i].SliderMultiplier) * songs[i].timingpoints[0].msPerBeat ) );
			//cout << songs[i].hitobjects[j].time << endl;
			//cout << map[k].back().time << endl;
			//cout << map[k].back().length << endl;
		}
		
		free(Locas);
	}
	
//convert beatmap finished	

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
	float dspeed = speed;
	int last = -1;
	int esc = 0;  //pause key
	long long sum = 0,  sumsq = 0;
	int item = 0;
	
	
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

//print combo
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
		
//draw life
		if(result.life > 0){
			setcolor(CYAN);
			arc(columnPosition+columnWidth*gameMode/2, 232, 90, result.life*360/1000+90, 110);//life
			setcolor(WHITE);
		}
	
//draw light	
		for(int k = 0;  k< gameMode ; k++){
			if(keySig[k]){
				if(mods & 4) putimage(columnPosition+(columnWidth*k), 0, light, COPY_PUT);
				 else putimage(columnPosition+(columnWidth*k), 400, light, COPY_PUT);
			}
			
		}
//put judgement image back
		t = last;
		if(t != -1){
			putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, judge[t][0], XOR_PUT);
		}
		

//draw lines	
		setcolor(WHITE);
		if(!(mods & 2)){
			for(int j = 0; j <= gameMode; j++){
				line(columnPosition+columnWidth*j, 0, columnPosition+columnWidth*j, 900);
			}
			if(mods & 4) line(columnPosition, 100, columnPosition+gameMode*columnWidth, 100);
			else line(columnPosition, 800, columnPosition+gameMode*columnWidth, 800);
		}
		
		setfillstyle(1, WHITE);

				
//play eff sound
		for(int j = 0; j < 4; j++){
			if(keySig[j]==1){
				if(mods & 4) bar(columnPosition+columnWidth*j, 0, columnPosition+columnWidth*(j+1), 100);
				else bar(columnPosition+columnWidth*j, 800, columnPosition+columnWidth*(j+1), 900);
			}
			if(keySig[j] ==1 &&  lastkeySig[j] == 0){
				PlaySound(".\\resources\\normal.wav", NULL, SND_FILENAME | SND_ASYNC);  
			}
		}
		
//judgement and print notes start

		mciSendString("status mp3 position", re,20, 0);
		position = atoi(re);
		
		
		
		position += offset;
		
		 
		
		setfillstyle(1, WHITE);

			
		for(int k = 0; k < gameMode; k++){
			for(int j = 0; j < map[k].size(); j++){
				if(map[k][j].err != 1000){
					if(map[k][j].length == 0) continue;
					else if(map[k][j].enderr != 1000) continue;
				}
				int ato = map[k][j].time - position;
				int holdato = map[k][j].length + ato;
				if(ato + map[k][j].length < -2000)	continue;
				if(ato > 2000)	break;

//positive edge
				if(keySig[k] == 1 && lastkeySig[k] == 0){
					if(ato < 150 && ato > -150){
						map[k][j].err =  ato;
					
						if(ato > 100 || ato < -100){
							result.bad++;
							result.life -= 10;
							result.score += 100+100.0*(result.combo*result.combo)/(5000*5000);
							last = 3;
						}
						else if(ato > 75 || ato < -75){
							result.good++;
							result.score += 300+300.0*(result.combo*result.combo)/(5000*5000);
							last = 2;
						}
						else if(ato > 50 || ato < -50){
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
						lastkeySig[k] = 1;
					}
					
				}
//keep pressing
				else if(keySig[k] == 1 && lastkeySig[k] == 1){
					
				}
//negetive edge
				else if(keySig[k] == 0 && lastkeySig[k] == 1){

					if(map[k][j].length != 0 && map[k][j].err != 1000 && map[k][j].enderr == 1000){
						
						if(holdato > 100 || holdato < -100){
							result.bad++;
							result.life -= 10;
							result.score += 100+100.0*(result.combo*result.combo)/(5000*5000);
							last = 3;
							result.combo++;
							map[k][j].enderr = ato;
						}
						else if(holdato > 75 || holdato < -75){
							result.good++;
							result.score += 300+300.0*(result.combo*result.combo)/(5000*5000);
							last = 2;
							result.combo++;
							map[k][j].enderr = ato;
						}
						else if(holdato > 50 || holdato < -50){
							result.great++;
							result.life += 5;
							result.score += 600+600.0*(result.combo*result.combo)/(5000*5000);
							last = 1;
							result.combo++;
							map[k][j].enderr = ato;
						}
						else {
							result.perfect++;
							result.life += 25;
							if(result.life >= 1000) result.life = 1000;
							result.score += 1200+1200.0*(result.combo*result.combo)/(5000*5000);
							last = 0;
							result.combo++;
							map[k][j].enderr = ato;
							
						}

						PlaySound(".\\resources\\normal.wav", NULL, SND_FILENAME | SND_ASYNC);  
						
						
						if(holdato > 150){
							map[k][j].enderr = ato;
							last = 4;
							result.miss++;
							result.combo=0;
							result.life -= 75;
						}
					}
				}
				
				
				if(ato < -150){
					if(map[k][j].err == 1000){
						map[k][j].err = ato;
						last = 4;
						result.miss++;
						result.combo=0;
						result.life -= 75;
					}
				}
				if(ato != holdato && holdato < -150 && map[k][j].err == 1000){
					map[k][j].err = ato;
					last = 4;
					result.miss++;
					result.combo=0;
					result.life -= 75;
					
				}
				
				
				int y = 800-speed*ato;
				int x = columnPosition+k*columnWidth;
				
				if(mods & 32){  //DYNAMIC
					dspeed = speed  + ( 1.0*((map[k][j].time*k) % 50) /50 )-1;
					y = 800 - dspeed*ato;
				}
				
				if(mods & 8){  //FREE FALL
				
					if(mods & 32){
						dspeed = speed  + ( 1.0*((map[k][j].time*k) % 50) /50 )-1;
						float g = (dspeed*dspeed / 400);
						int t = ((800/dspeed) - ato);
						
						y =  0.5 * g * t * t;
						if(ato > (800/dspeed)){
							y = -y;
						}
					}
					else{
						float g = (speed*speed / 400);
						int t = ((800/speed) - ato);
					
						y =  0.5 * g * t * t;
						if(ato > (800/speed)){
							y = -y;
						}
					}
				}
				if(mods & 16){ //SHIVER
					x+= 30 * sin(1.0* ato / (map[k][j].time % 50)  + map[k][j].time);
				}

				
				
				if(mods & 4){  //REVERSE
					y = 900-y;
					
					bar(x , y+20, x+columnWidth, y); //normal / head
					bar(x+15 , y + (dspeed * map[k][j].length), x+columnWidth-15, y); //body
					bar(x , y + (dspeed * map[k][j].length)+20 , x+columnWidth, y + (dspeed * map[k][j].length)); //tail
				}
				
				else{
					bar(x , y-20, x+columnWidth, y); //normal / head
					bar(x+15 , y - (dspeed * map[k][j].length), x+columnWidth-15, y); //body
					bar(x , y - (dspeed * map[k][j].length)-20 , x+columnWidth, y - (dspeed * map[k][j].length)); //tail
				}
			}
		}
		
		
		
		
		
		
		
//judge finished and print notes finished

//put judgement image front
		if(t != -1){
			putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, judge[t][0], XOR_PUT);
			putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, judge[t][1], OR_PUT);
		}
		
		
		
		
//life

		setvisualpage(cur_page);

		if(result.life <= 0){
			result.life = 0;
			if(!(mods & 1)){
				result.passed = 0;
				goto END;
			}
		}
		else if(result.life > 1000){
			result.life = 1000;
		}	
		//cout << result.life << endl;
		

		for(int j = 0; j < gameMode; j++){
			lastkeySig[j] = keySig[j];
			if(GetAsyncKeyState(keys[j])!=0) keySig[j]=1;
       			else keySig[j]=0;
		}
		
		
        
      
	  
//PAUSE SCREEN 
		if(GetAsyncKeyState(0x1B)!=0 && !esc){  //escape
			mciSendString("pause mp3", NULL, 0, NULL);
			int opt = pauseScreen(paused, pause_back);
			if(opt == 1){
				Sleep(300);
			}
			else if(opt == 2){
				//renew map 
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
				
				readBeatmap(i);
				
				goto START;
			}
			else if(opt == 3){
				result.passed = -100;
				goto END;
				
			}
			mciSendString("resume mp3", NULL, 0, NULL);
			esc = 1;
		}
		else esc = 0;
		

		Sleep(8);
		
		
	}
	
//caculate result and accuaracy 
	if(result.rank != -1){
	
		float acc = result.perfect*12 + result.great*6 + result.good*3 + result.bad;
		acc/=12;
		acc/= result.perfect + result.great + result.good + result.bad + result.miss;
		acc *= 100;
		if(acc > 95) result.rank = 1;
		else if(acc > 90) result.rank = 2;
		else if(acc > 80) result.rank = 3;
		else if(acc > 70) result.rank = 4;
		else result.rank = 5;
		cout << acc << endl; 
	}
	
//caculate unstable rate;

	for(int k = 0; k < gameMode; k++){
		for(int j = 0; j < map[j].size(); j++){
			if(map[k][j].err >= -150 && map[k][j].err <= 150){
				sum += map[k][j].err;
				sumsq += map[k][j].err * map[k][j].err;
				item++;
				if(map[k][j].length != 0){
					if(map[k][j].err <= 150 && map[k][j].err >= -150){
						sum += map[k][j].err;
						sumsq += map[k][j].err * map[k][j].err;
						item++;
					}
				}
			}
		}
	}
	result.unstableRate = pow(sumsq/item -  pow((sum/item), 2), 0.5);
	result.error = sum/item;
	
	
	END:
	freeBeatmap(i);
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
	return result;
	
}
