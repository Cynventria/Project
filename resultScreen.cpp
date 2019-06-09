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
	
	
	if(r.passed){

		
		void *ov = malloc(imagesize(0, 0, 1440, 900));
		readimagefile( ".\\resources\\resultBG.jpg", 0, 0, 1440, 900);
		getimage(0, 263, 1440, 580, ov);
		
		
		
		cleardevice();

		void *rk = malloc(imagesize(0, 0, 200, 280));
		sprintf(tmp, ".\\resources\\RA%d.jpg", r.rank);
		readimagefile( tmp, 0, 0, 200, 300);
		getimage(0, 0, 200, 280, rk);
		
		
		cleardevice();
		putimage(0, 750, bk2, XOR_PUT);
		
		
		putimage(0, 0, BG, OR_PUT);
		
		putimage(0, 263, ov, COPY_PUT);
		
		putimage(1100, 283, rk, COPY_PUT);
		
		
		
		setbkcolor(WHITE);
		setcolor(CYAN);
		
		sprintf(tmp, "%d", r.perfect);
		outtextxy(300, 300, tmp);
		sprintf(tmp, "%d", r.great);
		outtextxy(300, 400, tmp);
		sprintf(tmp, "%d", r.good);
		outtextxy(300, 500, tmp);
		sprintf(tmp, "%d", r.bad);
		outtextxy(660, 300, tmp);
		sprintf(tmp, "%d", r.miss);
		outtextxy(660, 400, tmp);
		
		sprintf(tmp, "%d", r.maxcombo);
		outtextxy(660, 520, tmp);
		
		sprintf(tmp, "Score: %d", r.score);
		outtextxy(1900, 280, tmp);
		
		
		
		setbkcolor(BLACK);
		setcolor(WHITE);
		
		free(rk);
		free(ov);
		
		
		ofstream file(".\\data\\records", ios::app | ios::binary);
		//sprintf(tmp, "%d %d %d %d %d %d %d %d %d\n", songs[i].BeatmapID, r.rank, r.score, r.perfect, r.great, r.good, r.bad, r.miss, r.maxcombo);
		//file << tmp;
		int data[10] = {songs[i].BeatmapID, r.rank, r.score, r.perfect, r.great, r.good, r.bad, r.miss, r.maxcombo, 0x0710807};
		
		for(int k = 0; k < 9; k++){
			data[9] += data[k] ^ data[k+1];
			if(data[k] & 1){
				data[9] = !data[9];
			}
		}
		file.write((char *)data, 40);
		
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
		
		putimage(0, 0, BG, OR_PUT);
		
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
