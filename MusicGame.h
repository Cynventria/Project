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
		int type;
		int hitSound;
		int repeat;
		int length;
		int sampleSet;
		int sliderType;
		vector<int> sliderPoints;
		int endtime;
};

class TimingPoint{
	public:
		int offset;
		int msPerBeat;
		int meter;
		int sampleSet;
		int volume;
		int inherited;
		int kiaiMode;
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

/*
class originalBeatmap : public song{
	public:
		float HPDrainRate;
		float CircleSize;
		float OverallDifficulty;
		float ApproachRate;
		float SliderMultiplier;
		float SliderTickRate;

		vector<TimingPoint> timingpoints;
		vector<HitObject> hitobjects;
};*/

/*class beatmap : public originalBeatmap{
	
};*/

class gameResult{
	public:
		int passed;
		int perfect;
		int great;
		int bad;
		int miss;
		int score;
		int life;
		int combo;
		int maxcombo;	
};


class MusicGame{
	private:
		int songcount;   //properties
		song *songs;
		int terminated;
		char tmp[150];
		
		song selectScreen();  //methods
		void readBeatmap(int);
		//beatmap createBeatmap(originalBeatmap);
		//gameResult game(beatmap);
		void resultScreen(song, gameResult);
		
		void pvInOut(int, int, int, void*, void*, void*);  //miscellaneous methods
		int Getdir(string, vector<string> &);
	public:
		MusicGame();
		int GameMain();
}; 
