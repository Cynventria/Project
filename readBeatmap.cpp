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
	cout << "start reading beatmap" << endl;
	
	ifstream ifs(songs[i].path.c_str());
	
	cout << "file read" << endl;
	
	string str;
	while(getline(ifs, str)){
		if(str.find("[TimingPoints]") == 0){
			getline(ifs, str);
			while(str[0] >= '0' && str[0] <= '9'){
				TimingPoint tp(str);	
				songs[i].timingpoints.push_back(tp);
				getline(ifs, str);
			}
		}
		else if(str.find("[HitObjects]") == 0){
			//HitObject &obj  = *(new HitObject());
			getline(ifs, str);
			while(str[0] >= '0' && str[0] <= '9'){
				HitObject obj(str);
				songs[i].hitobjects.push_back(obj);
				if(!getline(ifs, str))break;
			}
		}
	}
	ifs.close();
	
	
	
	//for(int j = 0; j < songs[i].hitobjects.size(); j++){
		//cout << /*songs[i].hitobjects[j].x << ", " << songs[i].hitobjects[j].y << ", " << songs[i].hitobjects[j].time << */endl;
	//} 
	
	
}

HitObject::HitObject(string str){
	x = 0;
	y = 0;
	time = 0;
	hit = -1;
	type = 0;
	hitSound = 0;
	repeat = 0;
	length = 0;
	sampleSet = 0;
	sliderType = 0;
	endtime = 0;

	int p = 0;
	int rec;
	int ccon = 0;
	int con = 0;
	int type;
	string val;
	
	while(str[p] != ','){val += str[p++];}
	x = atoi(val.c_str());
	val = "";
	p++;
	
	while(str[p] != ','){val += str[p++];}
	y = atoi(val.c_str());
	val = "";
	p++;
	
	while(str[p] != ','){val += str[p++];}
	time = atoi(val.c_str());
	val = "";
	p++; 
	
	while(str[p] != ','){val += str [p++];}
	type = atoi(val.c_str());
	val = "";
	p++;
	
	while(str[p] != ','){val += str [p++];}
	hitSound = atoi(val.c_str());
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
		rec++; 
	}
	
	if((type != 1) && (con == 0)){if(con == 0) type = 2;}
	
	else if((type != 1) && (con == 5)) type = 3;
	else type = 4;
	
	if(type == 1) {
		if(str[p] == 'L') sliderType = 1;
		else if (str[p] == 'P') sliderType = 2;
		else if (str[p] == 'B') sliderType = 3;
		p+=2;
		
		while(str[p] != ',') {
			int num;
			while((str[p] != ':')&&(str[p] != '|') ){val += str [p++];}
			num = atoi(val.c_str());
			sliderPoints.push_back(num);
			val = "";
			p++;
		}
		p++;
		
		while(str[p] != ',') {val += str[p++];}
		repeat = atoi(val.c_str());
		val = "";
		p++;
		
		while(str[p] != ','){val += str [p++];}
		length = atoi(val.c_str());
		val = "";
		p++;
		
		while(str[p] != ','){val += str [p++];}
		p++;
		
		while(str[p] != ','){val += str [p++];}
		p++;
		
		while(str[p] != ':'){val += str [p++];}
		sampleSet = atoi(val.c_str());
		val = "";
	}
	
	else if(type == 2){
		while(str[p] != ','&&str[p] != '\0'){val += str [p++];}
		endtime = atoi(val.c_str());
		val = "";
	}
	
	else if(type == 3) {
		while(str[p] != ':'){val += str [p++];}
		endtime = atoi(val.c_str());
		val = "";
		
		while(str[p] != ':'){val += str [p++];}
		sampleSet = atoi(val.c_str());
		val = "";
	}
	
	else if(type == 4){
		while(str[p] != ':'){val += str [p++];}
		sampleSet = atoi(val.c_str());
		val = "";
	}


	//cout << x << ", " << y << ", " << time << ", " << type << ", " << hitSound << ", " << repeat << ", " << length << ", " << sampleSet<< ", " <<sliderType<< endl;
}

TimingPoint::TimingPoint(string str){
	int p = 0;
	string val;

	while(str[p] != ','){val += str [p++];}
	offset = atoi(val.c_str());
	val = "";
	p++;
	
	while(str[p] != ','){val += str [p++];}
	msPerBeat = atof(val.c_str());
	val = "";
	p++;
	
/*	while(str[p] != ','){p++;}
	p++;*/
	
	while(str[p] != ','){val += str [p++];}
	meter = atoi(val.c_str());
	val = "";
	p++;
	
	while(str[p] != ','){val += str [p++];}
	sampleSet = atoi(val.c_str());
	val = "";
	p++;
	
	while(str[p] != ','){p++;}
	p++;
	
	while(str[p] != ','){val += str [p++];}
	volume = atoi(val.c_str());
	val = "";
	p++;
	
	while(str[p] != ','){val += str [p++];}
	inherited = atoi(val.c_str());
	val = "";
	p++;
	
	while(str[p] != ','){val += str [p++];}
	kiaiMode = atoi(val.c_str());
	val = "";
	p++;
	
	cout << offset << ", " << msPerBeat << ", " << meter << ", " << sampleSet << ", " << volume << ", " << kiaiMode << endl;

}

