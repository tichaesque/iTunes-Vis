#pragma once

#include "ofMain.h"
#include "ofxSpeech.h"
#include "ofxOculusRift.h"
#include "ofxCsv.h"
#include <stdlib.h>

#include <fstream>

using namespace wng;

typedef struct{
	ofColor color;
	ofVec3f pos;
	ofVec3f floatPos;
	float radius;
    bool bHighlighted;
} DemoSphere;

class testApp : public ofBaseApp
{
  public:
	
	void setup();
    void makeSpheres(); 
	void update();
	void draw();
	
	void drawScene();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxOculusRift		oculusRift;

	ofLight				light;
	ofEasyCam			cam;
	bool showOverlay;
	bool predictive;
	vector<DemoSphere> demos;
    
    ofVec3f cursor2D;
    ofVec3f cursor3D;
    
    ofVec3f cursorRift;
    ofVec3f demoRift;
    
    ofxCsv csv;
    ofxCsv csvRecorder;
    
    //-- Define function to handle the speech recognition event
    void speechRecognized(string & wordRecognized);
    
    string spokenword;
    
    ofxSpeechRecognizer         recognizer;
    
    vector <string> wordlist; //the displayed words
    vector <string> dictionary;
    
    vector<string> songNames;
    
    vector<ofSoundPlayer> songFiles;
    
    float speed = 0.8;
    ofGLRenderer myGLRender;
    int numSongsDownloaded = 150;
    int currentMonth;
    int numSongs = 0;
    float timestamp = 0;
    string currentMonthString;
};
