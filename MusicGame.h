//#include <sys/types.h>
#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
//#include <conio.h>
using namespace std;

int Getdir(string, vector<string> &);

class HitObject{
	public:
		int x;
		int y;
		int time;
		int hit;
		int *hits;
		int type;
		int hitSound;
		int repeat;
		int length;
		int sampleSet;
		int sliderType;
		vector<int> sliderPoints;
		int endtime;
		
		HitObject(string); 
};

class TimingPoint{
	public:
		int offset;
		float msPerBeat;
		int meter;
		int sampleSet;
		int volume;
		int inherited;
		int kiaiMode;
		
		TimingPoint(string);
};

class song{
	public:
		string path;
		string dir;
		string backGround;
		string AudioFilename;
		string Title;
		string TitleUnicode;
		string Artist;
		string ArtistUnicode;
		string Version;
		int BeatmapID;
		string PreviewTime;
		
		float HPDrainRate;
		float CircleSize;
		float OverallDifficulty;
		float ApproachRate;
		float SliderMultiplier;
		float SliderTickRate;
		
		vector<TimingPoint> timingpoints;
		vector<HitObject> hitobjects;
};

class gameResult{
	public:
		int passed;
		int perfect;
		int great;
		int good;
		int bad;
		int miss;
		int score;
		int life;
		int combo;
		int maxcombo;	
		int rank;
		int error;
		float unstableRate;
};

class hobj{
	public:
		int time;
		int length;
		int err;
		int enderr;
		
		hobj(int t, int l){ time = t;length = l;err=1000;enderr=1000;}
};


class MusicGame{
	private:
		int songcount;   //properties
		song *songs;
		int gameMode;
		char keys[7];
		float speed;
		int offset;
		int mods;
		int columnWidth;
		int columnPosition;
		int sudden;
		int lift;
		//int skin;
		
		int terminated;
		char tmp[150];
		
		int selectScreen();  //methods
		void readBeatmap(int);
		void freeBeatmap(int);
		//beatmap createBeatmap(originalBeatmap);  //inside game(int);
		gameResult game(int);
		gameResult TKgame(int);
		void resultScreen(gameResult, int);
		int pauseScreen(void*, void*);
		
		void resultScreen(song, gameResult);
		
		int pvScreen(int, int, int, void*, void*, void*, void*, void*);  //miscellaneous methods
		void configScreen(int, void*);
		void KeyconfigScreen(void*);
		void ModconfigScreen(void*);
		void PositionconfigScreen(void*);
		void OffsetTool();
		void saveConfig();
		int Getdir(string, vector<string> &);
	public:
		MusicGame();
		int GameMain();
}; 
