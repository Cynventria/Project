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
	
	readimagefile( ".\\resources\\START.jpg", 0, 0, 200, 100);  //subscreen of PV
	void *START = malloc(imagesize(0, 0, 200, 100));
	getimage(0, 0, 200, 100, START);
	
	Sleep(200);
	
	

	cleardevice();
	
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	
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
			if(pvScreen(1, cur_page, page+clicked, PREVback, songBG, frame, START) ){
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
			int x = 100+(14-(i-scrollGain*0.2))*(i-scrollGain*0.2)*4;
			int y = (i-scrollGain*0.2)*70 +10;
			
			if(pos >= songcount) break;
			
			strcpy(tmp, (songs[pos].Artist + "-" + songs[pos].Title + " [" + songs[pos].Version +"]").c_str());
			outtextxy(x, y, tmp);
			
			if(on == i){
				putimage(x-35, y-15, bar, OR_PUT);
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
			if(page + 14 < songcount)  scrollGain+=1;
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

int MusicGame::pvScreen(int direction, int cur_page, int index, void *PREVback, void *songBG, void *frame, void *START){   //direction = 1 or -1
	
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
		putimage(2240-100*i, 800, START, COPY_PUT);
		
		setbkcolor(BLACK);
		setcolor(WHITE);
			
			
		setvisualpage(cur_page);
		Sleep(10);
		
	}
	
	
	char re[20];
	
	string mciCommand = "open \"" + songs[index].dir + songs[index].AudioFilename + "\" type mpegvideo alias mp3";
	cout << "open mp3 " << songs[index].AudioFilename << endl;
	mciSendString(mciCommand.c_str(), re, 20, NULL);
	cout << "MCI return " << re << endl;
	
	
	
	
	if(re[0] == '1'){
		mciSendString(("seek mp3 to " + songs[index].PreviewTime).c_str(), NULL, 0, NULL);
		mciSendString("play mp3", NULL, 0, NULL);
		
		
		
		ifstream record(".\\data\\records");
		int buf[10] = {0};
		
		record.read((char*)buf, 10);
		if(buf[1] == songs[index].BeatmapID){
			int key = 0x0710807;
			for(int k = 0; k < 9; k++){
				key += buf[k] ^ buf[k+1];
				if(buf[k] & 1){
					key = !key;
				}
			}
			if(key == buf[9]){
				cout << buf[0] << buf[1] << buf[2];
			}
		}
		
		int click = 0, lastc = 0;
	
		while(1){    //detect back button on PV screen
			if(click == 1 && lastc == 0){


				if(mousex() >700 && mousex() < 831 && mousey() > 375 && mousey() < 506){
					
					mciSendString("stop mp3", NULL, 0, NULL);
					mciSendString("close mp3", NULL, 0, NULL);
					break;
				}
				else if(mousex() > 1240 && mousey() > 800){
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
				//free(Cframe);
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
		putimage(2240-100*i, 800, START, COPY_PUT);
		
		setbkcolor(BLACK);
		setcolor(WHITE);
			
			
		setvisualpage(cur_page);
		Sleep(10);
		
	}
	
	return 0;
	
	
}
				
				

	
	

