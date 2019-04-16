#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"

int main(){
	initwindow(1440,900);
	MusicGame MuG;
	MuG.GameMain();
	return 0;
}
