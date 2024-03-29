#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"
using namespace std;

void MusicGame::resultScreen(gameResult r, int i){
	
	if(r.passed == -100) return;
	
	void *BG =malloc(imagesize(0, 0, 1440, 900));     //Check if PV image is PNG
	if(songs[i].backGround.substr(songs[i].backGround.size()-4) != ".png"){
		readimagefile( (songs[i].dir + songs[i].backGround).c_str(), 0, 0, 1440, 900);
	}
	else{
		readimagefile( ".\\resources\\bg.jpg", 0, 0, 1440, 900);
	}
	getimage(0, 0, 1440, 900, BG);
	
	void *bk = malloc(imagesize(0, 0 ,300, 150));
	readimagefile(".\\resources\\BACK2.jpg", 0, 750, 300, 900);
	getimage(0, 750, 300, 900, bk);
		
	void *bk2 = malloc(imagesize(0, 0 ,300, 150));
	readimagefile(".\\resources\\BACK22.jpg", 0, 750, 300, 900);
	getimage(0, 750, 300, 900, bk2);
	
	void *resultF = malloc(imagesize(0, 0, 1440, 900));
	readimagefile( ".\\resources\\result.jpg", 0, 0, 1440, 900);
	getimage(0, 0, 1440, 900, resultF);
	
	void *resultB = malloc(imagesize(0, 0, 1440, 900));
	readimagefile( ".\\resources\\result2.jpg", 0, 0, 1440, 900);
	getimage(0, 0, 1440, 900, resultB);
	
	
	if(r.passed){


		
		cleardevice();

		void *rk = malloc(imagesize(0, 0, 300, 275));
		sprintf(tmp, ".\\resources\\RA%d.jpg", r.rank);
		readimagefile( tmp, 0, 0, 300, 350);
		getimage(0, 75, 300, 350, rk);
		
		
		cleardevice();
		putimage(0, 750, bk2, XOR_PUT);
		putimage(0, 0, resultB, OR_PUT);
		
		
		putimage(0, 0, BG, OR_PUT);
		
		putimage(0, 0, resultB, XOR_PUT);
		putimage(0, 0, resultF, OR_PUT);
		
		
		putimage(1150, 300, rk, COPY_PUT);
		
		
		
		setbkcolor(WHITE);
		setcolor(CYAN);
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
		//setusercharsize(1, 5, 1, 1);
		
		sprintf(tmp, "%4d", r.perfect);
		outtextxy(230, 340, tmp);
		sprintf(tmp, "%4d", r.great);
		outtextxy(230, 390, tmp);
		sprintf(tmp, "%4d", r.good);
		outtextxy(230, 440, tmp);
		sprintf(tmp, "%4d", r.bad);
		outtextxy(230, 490, tmp);
		sprintf(tmp, "%4d", r.miss);
		outtextxy(230, 540, tmp);
		
		
		float acc = r.perfect*1200 + r.great*600 + r.good*300 + r.bad *100;
		acc /= 12*(r.perfect + r.great + r.good + r.bad + r.miss);
		
		sprintf(tmp, "%.2f%%", acc);
		outtextxy(630, 425, tmp);
		sprintf(tmp, "%4dx", r.maxcombo);
		outtextxy(660, 475, tmp);
		
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
		
		if(r.error > 0) sprintf(tmp, "%.2f(+%d)", r.unstableRate, r.error);
		else sprintf(tmp, "%.2f(%d)", r.unstableRate, r.error);
		outtextxy(580, 540, tmp);
		
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 6);
		
		
		sprintf(tmp, "%9d", r.score);
		for(int j = 0; j < 9; j++){
			if(tmp[j] == ' ') tmp[j] = '0'; 
		}
		outtextxy(600, 350, tmp);
		
		
		
		setbkcolor(BLACK);
		setcolor(WHITE);
		
		free(rk);
		
		
		
		ofstream file(".\\data\\records", ios::out | ios::app | ios::binary);
		//sprintf(tmp, "%d %d %d %d %d %d %d %d %d\n", songs[i].BeatmapID, r.rank, r.score, r.perfect, r.great, r.good, r.bad, r.miss, r.maxcombo);
		//file << tmp;
		int data[11] = {songs[i].BeatmapID, gameMode, r.rank, r.score, r.perfect, r.great, r.good, r.bad, r.miss, r.maxcombo, 0x0710807};
		
		for(int k = 0; k < 10; k++){
			data[10] += (data[k] ^ !data[k+1]);
			data[10] = data[10] << k;

		}
		file.write((char *)data, 44);
		
		cout << "key " << data[10] << endl;
		
		cout << "error = " << r.error << endl << "unstable rate=" << r.unstableRate << endl;
		
		//file << songs[i].BeatmapID;
		file.close();
		
	}
	else{  //FAILED
		cleardevice();
		
		void *ov = malloc(imagesize(0, 0, 1440, 900));
		readimagefile( ".\\resources\\resultBG-FAIL.jpg", 0, 0, 1440, 900);
		getimage(0, 263, 1440, 580, ov);
		
		cleardevice();
		putimage(0, 750, bk2, XOR_PUT);
		putimage(0, 750, resultB, XOR_PUT);
		
		putimage(0, 0, BG, OR_PUT);
		
		putimage(0, 750, resultB, XOR_PUT);
		putimage(0, 263, ov, COPY_PUT);
		
		free(ov);
		
	}

	putimage(0, 750, bk2, XOR_PUT);
	putimage(0, 750, bk, OR_PUT);
	
	
	
	while(1){
		if(ismouseclick(WM_LBUTTONDOWN)){
			clearmouseclick(WM_LBUTTONDOWN);
			if(mousex() < 300 && mousey() > 750)  break;
		}
		
	}
	
	
	free(BG);
	free(bk2);
	free(bk);
	
}
