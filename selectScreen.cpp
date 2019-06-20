#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"
using namespace std;

int MusicGame::selectScreen(){
	int page = 0;
	int cur_page=0;
	int scrollGain = 0;
	int on = -1;
	int clicked = -1;
	
	setactivepage(0);
	readimagefile(".\\resources\\LOADING.jpg", 0, 0, 1440, 900);
	setvisualpage(0);
	setactivepage(1);

	readimagefile( ".\\resources\\bg.jpg", 0, 0, 1440, 900);  //copy bg image to memory
	void *bg = malloc(imagesize(0, 0, 1440, 900));
	getimage(0, 0, 1440, 900, bg);
	
	readimagefile( ".\\resources\\bar3.jpg", 0, 0, 1440, 70);  //selection bar
	void *bar = malloc(imagesize(0, 0, 1440, 70));
	getimage(0, 0, 1440, 70, bar);
	
	readimagefile( ".\\resources\\up.jpg", 0, 0, 65, 65);  //up arrow
	void *up = malloc(imagesize(0, 0, 65, 65));
	getimage(0, 0, 65, 65, up);
	
	readimagefile( ".\\resources\\down.jpg", 0, 0, 65, 65);  //doen arrow
	void *down = malloc(imagesize(0, 0, 65, 65));
	getimage(0, 0, 65, 65, down);
	
	readimagefile( ".\\resources\\cantReadPNG.jpg", 0, 0, 624, 351);  //can't read PNG
	void *cantReadPNG = malloc(imagesize(0, 0, 624, 351));
	getimage(0, 0, 624, 351, cantReadPNG);
	
	readimagefile( ".\\resources\\PREV_BG_3.jpg", 0, 0, 1440, 900);  //subscreen of PV
	void *PREVback = malloc(imagesize(0, 0, 1440, 900));
	getimage(0, 0, 1440, 900, PREVback);
	
	readimagefile( ".\\resources\\START.jpg", 0, 0, 300, 100);  //subscreen of PV
	void *START = malloc(imagesize(0, 0, 300, 100));
	getimage(0, 0, 300, 100, START);
	
	readimagefile( ".\\resources\\START2.jpg", 0, 0, 300, 100);  //subscreen of PV
	void *START2 = malloc(imagesize(0, 0, 300, 100));
	getimage(0, 0, 300, 100, START2);
	
	Sleep(200);
	
	

	cleardevice();
	
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	
	clearmouseclick(WM_LBUTTONDOWN);
	
	
	while(1){

//preview screen 	
		if(clicked != -1){
		
			void *frame = malloc(imagesize(0, 0, 1440, 900));
			getimage(0, 0, 1440, 900, frame);	
						

			void *songBG =malloc(imagesize(0, 0, 624, 351));     //Check if PV image is PNG
			if(songs[page+clicked].backGround.substr(songs[page+clicked].backGround.size()-4) != ".png"){
				readimagefile( (songs[page+clicked].dir + songs[page+clicked].backGround).c_str(), 0, 0, 624, 351);
				getimage(0, 0, 624, 351, songBG);
				putimage(0, 0, frame, COPY_PUT);
			}
			else{
				memcpy(songBG, cantReadPNG, imagesize(0, 0, 624, 351));    //copy memory from "can't read PNG", can't do songBG=cantReadPNG since cantReadPNG will be free
			}
			
			
			cout << "read image file: " << (songs[page+clicked].dir + songs[page+clicked].backGround) << endl;
			
			readBeatmap(page+clicked);
			if(pvScreen(1, cur_page, page+clicked, PREVback, songBG, frame, START, START2) ){
				free(bg);
				free(bar);
				free(up);
				free(down);
				free(cantReadPNG);
				free(PREVback);
				
				return page+clicked;
			}
			else{
				free(frame);
				free(songBG);
				clicked = -1;
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
			}
		}
		

//refresh start
		
		cur_page = -cur_page + 1;    //0 1 toggle
        setactivepage(cur_page);
   		cleardevice();
		
	
		for(int i = 0; i < 14; i++){           //PRINT LIST
			
			int pos = page+i;
			int x = 100+(14-(i-scrollGain*0.2))*(1+(i-scrollGain*0.2))*4;
			int y = (i-scrollGain*0.2)*70 +10;
			
			if(pos >= songcount) break;
			
			strcpy(tmp, (songs[pos].Artist + "-" + songs[pos].Title + " [" + songs[pos].Version +"]").c_str());
			outtextxy(x, y, tmp);
			
			if(on == i){
				putimage(x-45, y-15, bar, OR_PUT);
			}
			
		}
		
		
		putimage(5, 10, up, OR_PUT);
		putimage(5, 825, down, OR_PUT);
		line(20, 150, 20, 750);
		pieslice(20, 150+ 1.0*page/(songcount-13)*600, 0, 360, 5);
		putimage(0, 0, bg, OR_PUT);  //background
		
		
		setvisualpage(cur_page);
		
//refresh end
//detection start

//config page
		if(GetAsyncKeyState(0x20)!=0){  //SPACEBAR
			void *frame = malloc(imagesize(0, 0, 1440, 900));
			getimage(0, 0, 1440, 900, frame);
			configScreen(1, frame);
			clearmouseclick(WM_LBUTTONDOWN);
			free(frame);
			GetAsyncKeyState(0x20); //prevent re-detecting
			setbkcolor(BLACK);
			setcolor(WHITE);
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
		}




		
		on = -1;   //init cursor on
		
		if(ismouseclick(WM_LBUTTONDOWN)){   //detect mouse click 
        	clearmouseclick(WM_LBUTTONDOWN);
	        int mx = mousex(), my = mousey();
	        cout << "Left Pressed:" << mx << ", " << my << endl;
			            
			for(int i = 0; i < 13; i++){
				int x = 100+(13-i)*(i)*4;
				int y = i*70 + 10;
				if(mx > x && my > y && my < y+70 ){
					clicked = i;
				}
			}
		}
		
	    for(int i = 0; i < 14; i++){   //detect cursor on
			int x = 100+(14-i)*(i)*4;
			int y = i*70 + 10;
			if(mousex() > x && mousey() > y && mousey() < y+70){
				on = i;
			}
		}
		if(mousex()>5 && mousex()<70 && mousey()>10 && mousey()<75){  //scroll up
			if(page > 0)  scrollGain-=1;
			if(scrollGain <= -5){
	    		page--;
	    		scrollGain = 0;
	    	}
		}
		else if(mousex()>5 && mousex()<70 && mousey()>825 && mousey()<890){  //scroll down
			if(page + 14 <= songcount)  scrollGain+=1;
			if(scrollGain >= 5){
				page++;
				scrollGain = 0;
			}
		}
		else 	scrollGain=0;
		
//detection end
		
		Sleep(5);

	}
	
}

int MusicGame::pvScreen(int direction, int cur_page, int index, void *PREVback, void *songBG, void *frame, void *START, void *START2){   //direction = 1 or -1
	
	clearmouseclick(WM_LBUTTONDOWN);
	//if(direction > 0) readBeatmap(page+clicked);
	for(int j = 0; j < 10; j++){
		int i = j+1;

		cur_page = -cur_page+1;
		setactivepage(cur_page);
			
		putimage(1000 - 100*i, 0, PREVback, COPY_PUT );
			
			
		putimage(0, 0, frame, OR_PUT);
		putimage( 1850 - 100*i, 30 ,songBG , COPY_PUT);
			
		setbkcolor(WHITE);
		setcolor(CYAN);
		sprintf(tmp, songs[index].Artist.c_str());
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 0);
		setusercharsize(1, 5, 5, 6);
		outtextxy(1850-100*i, 400, tmp);  //Artist
		
		sprintf(tmp, songs[index].Title.c_str());
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 0);
		setusercharsize(1, 5, 1, 1);
		outtextxy(1855-100*i, 425, tmp); //Title
		
		int itmp = songs[index].hitobjects.back().time -  songs[index].hitobjects[0].time;
		sprintf(tmp, "Time : %d : %d", itmp/60000, (itmp%60000)/1000);
		outtextxy(1750-100*i, 850, tmp);
		
		itmp = 1.0 * 1000 / songs[index].timingpoints[0].msPerBeat * 60;
		sprintf(tmp, "BPM : %d", itmp);
		outtextxy(1950-100*i, 850, tmp);
		
		
		//outtextxy(2150-100*i, 850, "PLAY");
		//putimage(2100-100*i, 800, START, COPY_PUT);
		
		setbkcolor(BLACK);
		setcolor(WHITE);
			
			
		setvisualpage(cur_page);
		Sleep(10);
		
	}
	
	putimage(1120, 800, START, COPY_PUT);
	char re[20];
	
	string mciCommand = "open \"" + songs[index].dir + songs[index].AudioFilename + "\" type mpegvideo alias mp3";
	cout << "open mp3 " << songs[index].AudioFilename << endl;
	mciSendString(mciCommand.c_str(), re, 20, NULL);
	cout << "MCI return " << re << endl;
	
	
	
	
	if(re[0] == '1'){
		mciSendString(("seek mp3 to " + songs[index].PreviewTime).c_str(), NULL, 0, NULL);
		mciSendString("play mp3", NULL, 0, NULL);
		
		
		
		ifstream record(".\\data\\records", ios::in | ios::binary);
		int buf2[11] = {0};
		char buf[44] = {0};
		int nowrank = 1;
		vector <gameResult> r;
		
		
		if(record){

		
			while(1){
				for(int j = 0; j < 44; j++){
					record.get(buf[j]);
				}
				memcpy(buf2, buf, 44);
				
				if(record.eof()) break;
				cout << "ID " << buf2[0]  << " " << songs[index].BeatmapID << endl ; 
				
				if(buf2[0] == songs[index].BeatmapID){
					//cout << "found record" << endl;
					int key = buf2[10];
					buf2[10] = 0x0710807;
					for(int k = 0; k < 10; k++){
						buf2[10] += (buf2[k] ^ !buf2[k+1]);
						buf2[10] = buf2[10] << k;
					}
					cout << buf2[10] << endl;
					cout << key << endl;
					//songs[i].BeatmapID, r.rank, r.score, r.perfect, r.great, r.good, r.bad, r.miss, r.maxcombo, 0x0710807}
					if(buf2[10] == key && buf2[1] == gameMode){
						gameResult result = {1, buf2[4], buf2[5], buf2[6], buf2[7], buf2[8], buf2[3], 0, 0, buf2[9], buf2[2], 0};
						r.push_back(result);
					}
					
					//cout <<"key"<< key << "data" << buf2[9] << endl;
					//if(key == buf2[9]){
					
						
						//cout << "found record" << endl;
						//cout << buf[0] << buf[1] << buf[2];
					//}
				}
			}
		}
		record.close();
		for(int k = 0; k < r.size(); k++){
			for(int l = k; l <r.size(); l++ ){
				if(r[k].score < r[l].score){
					swap(r[k], r[l]);
				}
			}
		}
		setbkcolor(WHITE);
		setcolor(CYAN);
		
		if(r.size() == 0){
			outtextxy(1000, 600, "No record set!");
		}

		
		for(int  k = 0; k <= 5 && k < r.size(); k++){
			
			float acc = r[k].perfect*1200 + r[k].great*600 + r[k].good*300 + r[k].bad *100;
			acc /= 12*(r[k].perfect + r[k].great + r[k].good + r[k].bad + r[k].miss);
			sprintf(tmp, "#%d    %c %12d    %.2f%%   %4dx", k+1, r[k].rank==1 ? 'S':'A'+r[k].rank-2, r[k].score, acc, r[k].maxcombo);
			outtextxy(900-15*k, 500+50*k, tmp);
			line(850 - 15*k, 490+50*k, 1400 -15*k, 490+50*k);
		}
		r.clear();
		
		setbkcolor(BLACK);
		setcolor(WHITE);
		
		
		int click = 0, lastc = 0;
	
		while(1){    //detect back button on PV screen
			if(mousex() > 1120 && mousey() > 800){
				putimage(1120, 800, START2, COPY_PUT);
			}
			else putimage(1120, 800, START, COPY_PUT);
			
			if(click == 1 && lastc == 0){


				if(mousex() >700 && mousex() < 831 && mousey() > 375 && mousey() < 506){
					
					mciSendString("stop mp3", NULL, 0, NULL);
					mciSendString("close mp3", NULL, 0, NULL);
					break;
				}
				else if(mousex() > 1120 && mousey() > 800){
					cout << "returned" << endl;
					
					//readBeatmap(page+clicked);
					mciSendString("stop mp3", NULL, 0, NULL);
					mciSendString("close mp3", NULL, 0, NULL);
					
			
					return 1;
				}
			}
//MOD config page
			if(GetAsyncKeyState(0x20)!=0){  //SPACEBAR
				void *Cframe = malloc(imagesize(0, 0, 1440, 900));
				getimage(0, 0, 1440, 900, Cframe);
				ModconfigScreen(Cframe);
				clearmouseclick(WM_LBUTTONDOWN);
				free(Cframe);
				GetAsyncKeyState(0x20);  //prevent re-detecting
			}			
			
			Sleep(10);
			lastc = click;
			click = (int)ismouseclick(WM_LBUTTONDOWN);
			clearmouseclick(WM_LBUTTONDOWN);
			
		}
		
		
	}
	
	
	
	
	
	for(int j = 0; j < 10; j++){
		int i = 10-j;

		cur_page = -cur_page+1;
		setactivepage(cur_page);
			
		putimage(1000 - 100*i, 0, PREVback, COPY_PUT );
			
			
		putimage(0, 0, frame, OR_PUT);
		putimage( 1850 - 100*i, 30 ,songBG , COPY_PUT);
			
		setbkcolor(WHITE);
		setcolor(CYAN);
		sprintf(tmp, songs[index].Artist.c_str());
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 0);
		setusercharsize(1, 5, 5, 6);
		outtextxy(1850-100*i, 400, tmp);  //Artist
		
		sprintf(tmp, songs[index].Title.c_str());
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 0);
		setusercharsize(1, 5, 1, 1);
		outtextxy(1855-100*i, 425, tmp); //Title
		
		int itmp = songs[index].hitobjects.back().time -  songs[index].hitobjects[0].time;
		sprintf(tmp, "Time : %d : %d", itmp/60000, (itmp%60000)/1000);
		outtextxy(1750-100*i, 850, tmp);
		
		itmp = 1.0 * 1000 / songs[index].timingpoints[0].msPerBeat * 60;
		sprintf(tmp, "BPM : %d", itmp);
		outtextxy(1950-100*i, 850, tmp);
		
		
		//outtextxy(2150-100*i, 850, "PLAY");
		//putimage(2100-100*i, 800, START, COPY_PUT);
		
		setbkcolor(BLACK);
		setcolor(WHITE);
			
			
		setvisualpage(cur_page);
		Sleep(10);
		
	}
	
	return 0;
	
	
}
