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
		int hitSounds;
		int endime;
};

class song{
	public:
		string path;
		string dir;
		string backGround;
		string AudioFilename;
		string Title;
		string Artist;
		string Version;
		string PreviewTime;
};

class originalBeatmap : public song{
	public:
		float HPDrainRate;
		float CircleSize;
		float OverallDifficulty;
		float ApproachRate;
		float SliderMultiplier;
		int objectsCount;
		HitObject *hitobjects;
};

class beatmap : public originalBeatmap{
	
};

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
		originalBeatmap createOriginalBeatmap(song);
		beatmap createBeatmap(originalBeatmap);
		gameResult game(beatmap);
		void resultScreen(song, gameResult);
		
		void pvInOut(int, int, int, void*, void*, void*);  //miscellaneous methods
		int Getdir(string, vector<string> &);
	public:
		MusicGame();
		int GameMain();
}; 
