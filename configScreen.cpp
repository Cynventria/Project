#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"
using namespace std;


void MusicGame::configScreen(void *frame){
	int curpage = 0;
	setactivepage(0);
	setvisualpage(0);
	putimage(0, 0, frame, COPY_PUT);
	
	setactivepage(1);
	
	void *configPage = malloc(imagesize(0, 0, 1440, 200));
	readimagefile(".\\resources\\config-1.jpg", 0, 700, 1440, 900);
	getimage(0, 700, 1440, 900, configPage);
	
	void *bt1_1clicked = malloc(imagesize(0, 0, 700, 100));
	void *bt1_2clicked = malloc(imagesize(0, 0, 700, 100));
	readimagefile(".\\resources\\config-1-1.jpg", 0, 700, 1440, 900);
	getimage(700, 700, 1400, 800, bt1_1clicked);
	getimage(700, 800, 1400, 900, bt1_2clicked);
	
	for(int i = 1; i <= 5; i++){
		curpage = (curpage+1) % 2;
		setactivepage(curpage);
		
		putimage(0, 700, configPage, COPY_PUT);
		putimage(0, 0- (i*40), frame, COPY_PUT);
		
		setvisualpage(curpage);
		Sleep(10);
	} 
	
	int click = 0;
	int lastclick = 0;
	int mx, my;
	
	while(1){
		lastclick = click;
		click = GetAsyncKeyState(0x01)!=0 ;
		
		mx = mousex();
		my = mousey();
		
		if(mx > 750 && mx < 1380 && my > 738 && my < 780){
			putimage(700, 700, bt1_1clicked, COPY_PUT);
			
			if(click == 1 && lastclick == 0){
				void *keyConf = malloc(imagesize(0, 0, 1440, 200));
				readimagefile(".\\resources\\config-2.jpg", 0, 700, 1440, 900);
				getimage(0, 700, 1440, 900, keyConf);
				
				void *resetC = malloc(imagesize(0, 0, 200, 100));
				void *saveC = malloc(imagesize(0, 0, 200, 100));
				void *keyC = malloc(imagesize(0, 0, 171, 135));
				
				readimagefile(".\\resources\\config-2-2.jpg", 0, 700, 1440, 900);
				
				getimage(0, 700, 200, 800, resetC);
				getimage(0, 800, 200, 900, saveC);
				getimage(215, 765, 386, 900, keyC);
				
				
				
				while(1){
					lastclick = click;
					click = GetAsyncKeyState(0x01)!=0 ;
					
					mx = mousex();
					my = mousey();
					
					if(mx > 30 && mx < 190 && my > 730 && my < 790){  //RESET
						putimage(0, 700, resetC, COPY_PUT);
						if(click == 1 && lastclick == 0){
							keys[0] = 'Z';
							keys[1] = 'X';
							keys[2] = 'C';
							keys[3] = 'V';
							keys[4] = 'B';
							keys[5] = 'N';
							keys[6] = 'M';
						}
						
						cleardevice();
						setbkcolor(BLACK);
						setcolor(WHITE);
						for(int i = 0; i < 7; i++){
							sprintf(tmp, "%c", keys[i]);
							outtextxy(245 + 175*i, 800, tmp);
						}
						putimage(0, 700, keyConf, OR_PUT);
						
						
					}
					else if(mx > 30 && mx < 190 && my > 810 && my < 870){  //SAVE & EXIT
						putimage(0, 700, saveC, COPY_PUT);
						
						free(keyConf);
						free(resetC);
						free(saveC);
						free(keyC);
						break;
						
					}
					for(int i = 0; i < 7; i++){
						if((mx > 225 +  175*i && mx < 375 + 175*i && my > 773 && my < 873)){
							putimage(215 + 175*i, 765, keyC, COPY_PUT);
							
							
							if(click == 1 && lastclick == 0){
								char newkey = 0;
								while(1){
									if(GetAsyncKeyState(0x1B)!=0){ //esc
									
										newkey = keys[i];
										break;
										
									}
									
									
									for(int j = 'A'; j < 'Z'; j++ ){
										if(GetAsyncKeyState(j)!=0){
											newkey = j;
											goto NK;
										}
									}
									for(int j = '0'; j < '*'; j++){
										if(GetAsyncKeyState(j)!=0){
											newkey = j;
											goto NK;
										}
									}
									for(int j =0x61; j <= 0x69; j++){
										if(GetAsyncKeyState(j)!=0){
											newkey = j;
											goto NK;
											
											//num pad
										}
									}
									
									
									for(int j = 0xBA; j <= 0xC0; j++){
										if(GetAsyncKeyState(j)!=0){
											newkey = j;
											goto NK;
											
											//0xBA ;
											//0xBB +
											//0xBC ,
											//0XBD -
											//0xBE .
											//0xBF /
											//0xC0 ` ~
										}
									}
									
								}
								NK:
							}
		
							setbkcolor(WHITE);
							setcolor(CYAN);
							sprintf(tmp, "%c", keys[i]);
							outtextxy(245 + 175*i, 800, tmp);

							
						}
					}
					
					
					
					
					
					
				}
				
				
				
			}
			
		}
		else if(mx > 750 && mx < 1380 && my > 938 && my < 980){
			putimage(700, 700, bt1_1clicked, COPY_PUT);
			if(click == 1 && lastclick == 0){
				
			}
			
		}
		
		if(click == 1 && lastclick == 0){
			if(my < 700)  break;
			
			
			if(my > 825 && my < 855){
				if(mx > 20 && mx < 50){
					gameMode--;
					if(gameMode < 3) gameMode = 7;
				}
				else if(mx > 160 && mx < 190){
					gameMode--;
					if(gameMode > 7) gameMode = 3;
				}
				else if(mx > 240 && mx < 270){
					if(speed > 0.1)
						speed -= 0.1;
				}
				else if(mx > 390 && mx < 420){
					speed += 0.1;
				}
				else if(mx > 475 && mx < 505){
					offset --;
				}
				else if(mx > 640 && mx < 670){
					offset ++;
				}
				
				putimage(0, 700, configPage, COPY_PUT);
				sprintf(tmp, "%d", gameMode);
				outtextxy(60, 800, tmp);
				
				sprintf(tmp, "%d", speed * 10);
				outtextxy(250, 800, tmp);	
				
				sprintf(tmp, "%d", offset);
				outtextxy(490, 800, tmp);
			}
		}
		
		
		
		
	}
		 
	
	
}
