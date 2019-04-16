#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"


int MusicGame::Getdir(string dir, vector<string> &files){
    DIR *dp;//創立資料夾指標
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL){
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while((dirp = readdir(dp)) != NULL){//如果dirent指標非空
        files.push_back(string(dirp->d_name));//將資料夾和檔案名放入vector
    }
    closedir(dp);//關閉資料夾指標
    return 0;
}


MusicGame::MusicGame(){  //建構式，初始化songs陣列 
	terminated = 0;
	cout << "start game" << endl;
	
//LOADING
	sprintf(tmp, "LOADING");
	outtextxy(700, 400, tmp);
	
    string dir = ".\\song";//資料夾路徑(絕對位址or相對位址)
    vector<string> dirs = vector<string>(); //第一層資料夾名稱 
    vector<string> files = vector<string>();  //第二層所有資料名稱 
    vector<string> maps = vector<string>();  //所有.osu檔 
    vector<string> mapsDIR = vector<string>();
    
    Getdir(dir, dirs);
    for(int i = 0; i < dirs.size(); i++){
        cout << dir+"\\"+dirs[i] << endl;
        if(dirs[i] != ".." && dirs[i] != ".")Getdir(dir+"\\"+dirs[i], files);
        for(int j = 0; j < files.size(); j++){
        	if(files[j].find(".osu", 0) != string::npos){
        		maps.push_back( ".\\song\\" + dirs[i]+"\\"+files[j] );
        		mapsDIR.push_back(".\\song\\" + dirs[i]+"\\");
        		cout << "found beatmap: " << dirs[i]+"\\"+files[j] << endl;
			}
		}
		files.clear();
    }
    songs = new song[maps.size()];
    for(int i = 0; i < maps.size(); i++){
    	songs[i].path = maps[i];
    	songs[i].dir = mapsDIR[i];
    	ifstream ifs(maps[i].c_str());  //讀檔，取得基本歌曲資訊 
    	string str;
    	while(getline(ifs, str)){
    		if(str.find("AudioFilename:") == 0){
    			songs[i].AudioFilename = str.substr(15);
    		}
    		else if(str.find("Title:") == 0){
    			songs[i].Title = str.substr(6);
			}
			else if(str.find("Artist:") == 0){
				songs[i].Artist = str.substr(7);
			}
			else if(str.find("Version:") == 0){
				songs[i].Version = str.substr(8);
			}
			else if(str.find("PreviewTime:") == 0){
    			songs[i].PreviewTime = str.substr(13);
    		}
    		else if(str.find("0,0,\"") == 0){
    			songs[i].backGround = str.substr(5, str.substr(5).find('\"'));
			}
		}
		ifs.close();
		cout << "loaded beatmap: " << endl;
		cout << songs[i].Title << " " << songs[i].Artist << " " << songs[i].Version << " " << songs[i].AudioFilename << " " <<  songs[i].PreviewTime << " " << songs[i].backGround << endl;
	}
	songcount = maps.size();
	cout << "Construction finished" << endl;
}


int MusicGame::GameMain(){
	while(terminated != 1){
		song selected = selectScreen();
		//gameResult result = Mug.game(selected);
		//Mug.resultScreen(result);	
	}
	return 0;
}


void MusicGame::pvInOut(int direction, int cur_page, int index, void *PREVback, void *songBG, void *frame){   //direction = 1 or -1
	
	for(int j = 0; j < 10; j++){
		int i = 0;
		if(direction > 0)	i = j+1;
		else	i = 10-j;
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
		outtextxy(1850-100*i, 400, tmp);
		
		sprintf(tmp, songs[index].Title.c_str());
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 0);
		setusercharsize(1, 5, 1, 1);
		outtextxy(1855-100*i, 425, tmp);
			
		setbkcolor(BLACK);
		setcolor(WHITE);
			
			
		setvisualpage(cur_page);
		Sleep(10);
	}
}


song MusicGame::selectScreen(){
	int page = 0;
	int cur_page=0;
	int scrollGain = 0;
	int on = -1;
	int clicked = -1;

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
	



	cleardevice();
	
	
	while(1){

//preview screen 	
		if(clicked != -1){
		
			void *frame = malloc(imagesize(0, 0, 1440, 900));
			getimage(0, 0, 1440, 900, frame);	
						

			void *songBG =malloc(imagesize(0, 0, 624, 351));     //Check if PV image is PNG
			if(songs[page+clicked].backGround.substr(songs[page+clicked].backGround.size()-4) != ".png"){
				readimagefile( (songs[page+clicked].dir + songs[page+clicked].backGround).c_str(), 0, 0, 624, 351);
				getimage(0, 0, 624, 351, songBG);
				cleardevice();
			}
			else{
				memcpy(songBG, cantReadPNG, imagesize(0, 0, 624, 351));    //copy memory from "can't read PNG", can't do songBG=cantReadPNG since cantReadPNG will be free
			}
			
			
			cout << "read image file: " << (songs[page+clicked].dir + songs[page+clicked].backGround) << endl;
			
			
			pvInOut(1, cur_page, page+clicked, PREVback, songBG, frame);
			
		
			char re[20];
			string mciCommand = "open \"" + songs[page+clicked].dir + songs[page+clicked].AudioFilename + "\" type mpegvideo alias mp3";
			cout << "open mp3 " << songs[page+clicked].AudioFilename << endl;
			mciSendString(mciCommand.c_str(), re, 20, NULL);
			cout << "MCI return " << re << endl;
			if(re[0] == '1'){
				mciSendString(("seek mp3 to " + songs[page+clicked].PreviewTime).c_str(), NULL, 0, NULL);
				mciSendString("play mp3", NULL, 0, NULL);
				
				
				
				while(1){    //detect back button on PV screen
					if(ismouseclick(WM_LBUTTONDOWN)){
						clearmouseclick(WM_LBUTTONDOWN);
						cout << "Left Pressed:" << mousex() << ", " << mousey() << endl;
						if(mousex() >700 && mousex() < 831 && mousey() > 375 && mousey() < 506){
							break;
						}
					}
					
				}
				
				
				//stop and close music
				mciSendString("stop mp3", NULL, 0, NULL);
				mciSendString("close mp3", NULL, 0, NULL);
				
//resune to selection page
				setactivepage(-cur_page+1);
			}
			else{
				cout << "ERROR PLAYING MP3" << endl;
				setactivepage(-cur_page+1);
				//outtextxy(0, 0, "ERROR PLAYING MUSIC");
				Sleep(500);
				setactivepage(-cur_page+1);
			}

		
		pvInOut(-1, cur_page, page+clicked, PREVback, songBG, frame);
			
			free(frame);
			free(songBG);
			clicked = -1;
		}
		

//refresh start
		
		cur_page = -cur_page + 1;    //0 1 toggle
        setactivepage(cur_page);
   		cleardevice();
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
		
	
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
		cout << "selection page refreshed" << endl;
		cout << page/songcount << endl;
		
		cout << "cursor now on " << on%100 << endl;
		
//refresh end
//detection start
		
		on = -1;   //init cursor on
		
		if(ismouseclick(WM_LBUTTONDOWN)){   //detect mouse click 
        	clearmouseclick(WM_LBUTTONDOWN);
	        int mx = mousex(), my = mousey();
	        cout << "Left Pressed:" << mx << ", " << my << endl;
			            
	        /*if(mx>5 && mx<120 && my>5 && my<120){
	           	if(page > 1) page--;
			}
			else if(mx>5 && mx<120 && my>735 && my<850){
	           	if(page + 13 < songcount) page++;
			}*/
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
			if(page > 0)  scrollGain--;
			if(scrollGain <= -5){
	    		page--;
	    		scrollGain = 0;
	    	}
		}
		else if(mousex()>5 && mousex()<70 && mousey()>825 && mousey()<890){  //scroll down
			if(page + 14 < songcount)  scrollGain++;
			if(scrollGain >= 5){
				page++;
				scrollGain = 0;
			}
		}
		else 	scrollGain=0;
		
//detection end
		
		Sleep(10);

	}
	
}
