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
				int p = 0;
				string val;
				TimingPoint tp;
				/*
				deal with timeingpoint data;
				example timeing point:
				Offset, Milliseconds per Beat, Meter, Sample Set, Sample Index, Volume, Inherited, Kiai Mode
				66,315.789473684211,4,2,0,45,1,0
				*/ 
				while(str[p] != ','){val += str [p++];}
				tp.offset = atoi(val.c_str());
				val = "";
				p++;
				
				while(str[p] != '.'){val += str [p++];}
				tp.msPerBeat = atoi(val.c_str());
				val = "";
				p++;
				
				while(str[p] != '.'){p++;}
				p++;
				
				while(str[p] != ','){val += str [p++];}
				tp.meter = atoi(val.c_str());
				val = "";
				p++;
				
				while(str[p] != ','){val += str [p++];}
				tp.sampleSet = atoi(val.c_str());
				val = "";
				p++;
				
				while(str[p] != ','){p++;}
				p++;
				
				while(str[p] != ','){val += str [p++];}
				tp.volume = atoi(val.c_str());
				val = "";
				p++;
				
				while(str[p] != ','){val += str [p++];}
				tp.inherited = atoi(val.c_str());
				val = "";
				p++;
				
				while(str[p] != ','){val += str [p++];}
				tp.kiaiMode = atoi(val.c_str());
				val = "";
				p++;
				
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
				
				//type 1
				//x,y,time,type,hitSound,sliderType|curvePoints,repeat,pixelLength,edgeHitsounds,edgeAdditions,sampleSet:additionSet:customIndex:sampleVolume:filename
				//424,96,66,2,0,B|380:120|332:96|332:96|304:124,1,130,2|0,0:0|0:0,0:0:0:0:
				//sliderType will be L (linear), P (perfect), B (Bezier)
				//int L = 1, P = 2, B = 3
				//store points in vector sliderPoints, like{380, 120, 332, 96, 332, 96, 304, 124}
			
				//type 2
				//x,y,time,type,hitSound,endTime,extras
				//256,192,730,12,8,3983
					
				//type 3
				//x,y,time,type,hitSound,endTime:sampleSet:additionSet:customIndex:sampleVolume:filename
				//329,192,16504,128,0,16620:0:0:0:0:
			
				//type 4
				//example hitObject:
				//x,y,time,type,hitSound,sampleSet:additionSet:customIndex:sampleVolume:filename
				//164,260,2434,1,0,0:0:0:0:
				
				
				
				int p = 0;
				int rec;
				int ccon = 0;
				int con = 0;
				int type;
				string val;
				
				while(str[p] != ','){val += str[p++];}
				obj.x = atoi(val.c_str());
				val = "";
				p++;
				
				while(str[p] != ','){val += str[p++];}
				obj.y = atoi(val.c_str());
				val = "";
				p++;
				
				while(str[p] != ','){val += str[p++];}
				obj.time = atoi(val.c_str());
				val = "";
				p++; 
				
				while(str[p] != ','){val += str [p++];}
				obj.type = atoi(val.c_str());
				val = "";
				p++;
				
				while(str[p] != ','){val += str [p++];}
				obj.hitSound = atoi(val.c_str());
				val = "";
				p++;
				rec = p;
				
				while(str[rec] != '\0'){
					if(str[rec] == '|') {
						type = 1;
						break;
					}
					
					if(str[rec] == ','){ccon++;}
					if(str[rec] == ':'){con++;}
				}
				
				if((type != 1) && (con == 0)){if(con == 0) type = 2;}
				
				else if((type != 1) && (con == 5)) type = 3;
				else type = 4;
				
				if(type == 1) {
					if(str[p] == 'L') obj.sliderType = 1;
					else if (str[p] == 'P') obj.sliderType = 2;
					else if (str[p] == 'B') obj.sliderType = 3;
					p+=2;
					
					while(str[p] != ',') {
						int num;
						while((str[p] != ':')&&(str[p] != '|') ){val += str [p++];}
						num = atoi(val.c_str());
						obj.sliderPoints.push_back(num);
						val = "";
						p++;
					}
					p++;
					
					while(str[p] != ',') {val += str[p++];}
					obj.repeat = atoi(val.c_str());
					val = "";
					p++;
					
					while(str[p] != ','){val += str [p++];}
					obj.length = atoi(val.c_str());
					val = "";
					p++;
					
					while(str[p] != ','){val += str [p++];}
					p++;
					
					while(str[p] != ','){val += str [p++];}
					p++;
					
					while(str[p] != ':'){val += str [p++];}
					obj.sampleSet = atoi(val.c_str());
					val = "";
				}
				
				else if(type == 2){
					while(str[p] != ','&&str[p] != '\0'){val += str [p++];}
					obj.endtime = atoi(val.c_str());
					val = "";
				}
				
				else if(type == 3) {
					while(str[p] != ':'){val += str [p++];}
					obj.endtime = atoi(val.c_str());
					val = "";
					
					while(str[p] != ':'){val += str [p++];}
					obj.sampleSet = atoi(val.c_str());
					val = "";
				}
				
				else if(type == 4){
					while(str[p] != ':'){val += str [p++];}
					obj.sampleSet = atoi(val.c_str());
					val = "";
				}
				
				cout << obj.x << ", " << obj.y << ", " << obj.time << endl;
				
				songs[i].hitobjects.push_back(obj);
				if(!getline(ifs, str))break;
			}
		}
	}
	ifs.close();
	
	
}
