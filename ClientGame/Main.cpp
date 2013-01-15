
#include "stdafx.h"
#include "SnakesGameManager.h"


int main(int argc, char* argv[])
{
    const int kScreenWidth = 1024, kScreenHeight = 768;
    
	// get things going
	//  optional parameters:
	//		int windowWidth			default: 1024
	//		int windowHeight		default: 768
	//		std::string windowName	default: "Angel Engine"
	//		bool antiAliasing		default: false
	//		bool fullScreen			default: false
	theWorld.Initialize(kScreenWidth, kScreenHeight, "Blindschleiche", true, false);
	
	//adds the default grid so you can more easily place Actors
	//theWorld.Add(new GridActor(), -1);
    
    //Register Fonts
    RegisterFont("Resources/Fonts/slkscrb.ttf", 30, "standard");
    RegisterFont("Resources/Fonts/slkscrb.ttf", 50.f, "popup");
    
    SnakesGameManager gameManager;
	theWorld.SetGameManager(&gameManager);
	
	// do all your setup first, because this function won't return until you're exiting
	theWorld.StartGame();
	
	// any cleanup can go here
	theWorld.Destroy();
	
	return 0;
}
