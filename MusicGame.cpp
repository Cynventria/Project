#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"
using namespace std;

int MusicGame::Getdir(string dir, vector<string> &files){
    DIR *dp;//�Х߸�Ƨ�����
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL){
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while((dirp = readdir(dp)) != NULL){//�p�Gdirent���ЫD��
        files.push_back(string(dirp->d_name));//�N��Ƨ��M�ɮצW��Jvector
    }
    closedir(dp);//������Ƨ�����
    return 0;
}


MusicGame::MusicGame(){  //�غc���A
	terminated = 0; //whether the game is end
	gameMode = 4; //keys
	speed = 2; //drop speed
	columnWidth = 90;
	columnPosition = 400;
	offset = -70;
	cout << "start game" << endl;
	
//LOADING
	sprintf(tmp, "LOADING");
	outtextxy(700, 400, tmp);
	
//�غc��
	
    string dir = ".\\song";//��Ƨ����|(�����}or�۹��})
    vector<string> dirs = vector<string>(); //�Ĥ@�h��Ƨ��W�� 
    vector<string> files = vector<string>();  //�ĤG�h�Ҧ���ƦW�� 
    vector<string> maps = vector<string>();  //�Ҧ�.osu�� 
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
    	ifstream ifs(maps[i].c_str());  //Ū�ɡA���o�򥻺q����T 
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
    		else if(str.find("HPDrainRate:") == 0){
    			songs[i].HPDrainRate = atof(str.substr(13).c_str());
    		}
    		else if(str.find("CircleSize:") == 0){
    			songs[i].CircleSize = atof(str.substr(11).c_str());
			}
			else if(str.find("OverallDifficulty:") == 0){
    			songs[i].OverallDifficulty = atof(str.substr(18).c_str());
			}
			else if(str.find("ApproachRate:") == 0){
    			songs[i].ApproachRate = atof(str.substr(13).c_str());
			}
			else if(str.find("SliderMultiplier:") == 0){
    			songs[i].SliderMultiplier = atof(str.substr(17).c_str());
			}
			else if(str.find("SliderTickRate:") == 0){
    			songs[i].SliderTickRate = atof(str.substr(15).c_str());
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
		int selected = selectScreen();
		gameResult result = game(selected);
		//Mug.resultScreen(result);	
	}
	return 0;
}

