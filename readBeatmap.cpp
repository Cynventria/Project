#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"
using namespace std;


void MusicGame::readBeatmap(int i){
	ifstream ifs(songs[i].path.c_str());
	string str;
	while(getline(ifs, str)){
		if(str.find("[TimingPoints]") == 0){
			getline(ifs, str);
			while(str[0] >= '0' && str[0] <= '9'){
				TimingPoint tp;
				//deal with timeingpoint data;
				//example timeing point:
				//Offset, Milliseconds per Beat, Meter, Sample Set, Sample Index, Volume, Inherited, Kiai Mode
				//66,315.789473684211,4,2,0,45,1,0
				
				
				
				songs[i].timingpoints.push_back(tp);
				getline(ifs, str);
			}
		}
		else if(str.find("[HitObjects]") == 0){
			getline(ifs, str);
			while(str[0] >= '0' && str[0] <= '9'){
				HitObject obj = {0};
				//obj.hit = 0;
				
				
				
				//deal with hitobject data;
				//ignore filename
				
				//example hitObject:
				//x,y,time,type,hitSound,sampleSet:additionSet:customIndex:sampleVolume:filename
				//164,260,2434,1,0,0:0:0:0:
				
				//x,y,time,type,hitSound,sliderType|curvePoints,repeat,pixelLength,edgeHitsounds,edgeAdditions,sampleSet:additionSet:customIndex:sampleVolume:filename
				//424,96,66,2,0,B|380:120|332:96|332:96|304:124,1,130,2|0,0:0|0:0,0:0:0:0:
				//sliderType will be L (linear), P (perfect), B (Bezier)
				//int L = 1, P = 2, B = 3
				//store points in vector sliderPoints, like{380, 120, 332, 96, 332, 96, 304, 124}
				
				//x,y,time,type,hitSound,endTime,extras
				//256,192,730,12,8,3983
					
				//x,y,time,type,hitSound,endTime:sampleSet:additionSet:customIndex:sampleVolume:filename
				//329,192,16504,128,0,16620:0:0:0:0:
				int p = 0;
				string val;
				while(str[p] != ','){
					val += str[p];
					p++;
				}
				obj.x = atoi(val.c_str());
				val = "";
				p++;
				while(str[p] != ','){
					val += str[p];
					p++;
				}
				obj.y = atoi(val.c_str());
				val = "";
				p++;
				while(str[p] != ','){
					val += str[p];
					p++;
				}
				obj.time = atoi(val.c_str());
				val = "";
				
				cout << obj.x << ", " << obj.y << ", " << obj.time << endl;
				
				songs[i].hitobjects.push_back(obj);
				if(!getline(ifs, str))break;
			}
		}
	}
	ifs.close();
	
	
}
