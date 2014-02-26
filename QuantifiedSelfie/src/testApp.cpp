#include "testApp.h"
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------
void testApp::setup()
{
	ofBackground(0);
	ofSetLogLevel( OF_LOG_VERBOSE );
	showOverlay = true;
	predictive = true;
	
	ofHideCursor();
	
	oculusRift.baseCamera = &cam;
	oculusRift.setup();
    
    csv.loadFile(ofToDataPath("iTunes-log.csv"));
    
    ofAddListener(recognizer.speechRecognizedEvent, this, &testApp::speechRecognized);
    recognizer.initRecognizer();
    
    string dict = "dictionary.txt";
    
    //dictionary is loaded here
    recognizer.loadDictionaryFromFile(dict);
    
    ifstream fin; //declare a file stream
    fin.open( ofToDataPath(dict).c_str() );
    
    while(fin != NULL) //as long as theres still text to be read
    {
        string str; //declare a string for storage
        getline(fin, str); //get a line from the file, put it in the string
        dictionary.push_back(str); //push the string onto a vector of strings
    }
    
    recognizer.startListening();
    
    ofSetVerticalSync(true);
	ofBackgroundHex(0x0);
	ofSetLogLevel(OF_LOG_NOTICE);
    
	//enable mouse;
	cam.begin();
	cam.end();
}

//--------------------------------------------------------------
void testApp::makeSpheres()
{
    //in case songs from previous months were loaded before
    demos.clear();
    songNames.clear();
    
    timestamp = ofGetElapsedTimef();
    
    //loads songs
    for(int i = 1; i < csv.numRows; i++) {
        if (ofToInt(csv.data[i][4]) == currentMonth) {
            DemoSphere d;
            
            d.color = ofColor(ofRandom(50,255),
                              ofRandom(200),
                              ofRandom(125));
            
            d.pos = ofVec3f(ofRandom(-200,200), ofRandom(-200, 200), ofRandom(-20000000, -50000));
            
            d.floatPos.y = d.pos.y;
            d.floatPos.x = d.pos.x;
            
            d.radius = ofRandom(5, 20);
            
            d.bHighlighted = false;
            
            string songname = csv.data[i][0];
            
            demos.push_back(d);
            songNames.push_back(songname);
        }
    } 
    numSongs = songNames.size();
    
    random_shuffle(demos.begin(), demos.end());
    
    if(demos.size() > 120)
        demos.erase(demos.begin()+120, demos.end());
    
}

//--------------------------------------------------------------
void testApp::speechRecognized(string & wordRecognized)
{
    cout << wordRecognized << endl;
    
    for (int i = 0; i < dictionary.size(); i++) {
        if(wordRecognized == dictionary[i])
        {
            wordlist.push_back(wordRecognized);
            
            if (wordRecognized == "january") {
                currentMonth = 1;
                currentMonthString = "January";
            }
            
            else if (wordRecognized == "february") {
                currentMonth = 2;
                currentMonthString = "February";
            }
            
            else if (wordRecognized == "march") {
                currentMonth = 3;
                currentMonthString = "March";
            }
            
            else if (wordRecognized == "april") {
                currentMonth = 4;
                currentMonthString = "April";
            }
            
            else if (wordRecognized == "may") {
                currentMonth = 5;
                currentMonthString = "May";
            }
            
            else if (wordRecognized == "june") {
                currentMonth = 6;
                currentMonthString = "June";
            }
            
            else if (wordRecognized == "july") {
                currentMonth = 7;
                currentMonthString = "July";
            }
            
            else if (wordRecognized == "august") {
                currentMonth = 8;
                currentMonthString = "August";
            }
            
            else if (wordRecognized == "september") {
                currentMonth = 9;
                currentMonthString = "September";
            }
            
            else if (wordRecognized == "october") {
                currentMonth = 10;
                currentMonthString = "October";
            }
            
            else if (wordRecognized == "november") {
                currentMonth = 11;
                currentMonthString = "November";
            }
            
            else if (wordRecognized == "december") {
                currentMonth = 12;
                currentMonthString = "December";
            }
            
            makeSpheres();
            
        }
    }
    
}


//--------------------------------------------------------------
void testApp::update()
{
    if (ofGetElapsedTimef() - timestamp >= 4.0) {
        for(int i = 0; i < demos.size(); i++){
            float xPos = demos[i].pos.x/100.0;
            float yPos = demos[i].pos.y/100.0;
            float rad = 20.0/demos[i].radius; //bigger spheres move more slowly
            demos[i].floatPos.z += speed * rad;
        }
    }
    
}


//--------------------------------------------------------------
void testApp::draw()
{
	if(oculusRift.isSetup()) {
        
		glEnable(GL_DEPTH_TEST);
		oculusRift.beginLeftEye();
		drawScene();
		oculusRift.endLeftEye();
		
		oculusRift.beginRightEye();
		drawScene();
		oculusRift.endRightEye();
		
		oculusRift.draw();
		
		glDisable(GL_DEPTH_TEST);
	}
	else {
		cam.begin();
		drawScene();
		cam.end();
        
	}
	
}

//--------------------------------------------------------------
void testApp::drawScene()
{ 
    if (ofGetElapsedTimef() - timestamp < 4.0 && timestamp != 0) {
        ofPushStyle();
        ofPushMatrix();
        ofRotateX(180); //I need to rotate it otherwise the text will be upside-down on the oculus (???)
        
        ofSetColor(255,255);
        ofFill();
        ofScale(3, 3);
        myGLRender.drawString("Ticha's " + currentMonthString + " Songs\n" +
                           ofToString(numSongs) + " songs downloaded\n" +
                           ofToString(demos.size())+" songs displayed" , -100, 0, 0, OF_BITMAPMODE_SIMPLE);
        
        
        ofPopMatrix();
        ofPopStyle();
    }
    else {
        ofPushMatrix();
        ofRotate(90, 0, 0, -1);
        ofPopMatrix();
        
        ofPushStyle();
        ofNoFill();
        for(int i = 0; i < demos.size(); i++){
            ofPushMatrix();
            ofTranslate(demos[i].floatPos);
            ofSetColor(demos[i].bHighlighted ? ofColor::white.getLerped(ofColor::red, sin(ofGetElapsedTimef()*10.0)*.5+.5) : demos[i].color);
            ofSphere(demos[i].radius);
            ofPushMatrix();
            ofRotateX(180); //I need to rotate it otherwise the text will be upside-down on the oculus (???)
            myGLRender.drawString(songNames[i], 0, -(demos[i].radius+5), demos[i].radius, OF_BITMAPMODE_SIMPLE);
            ofPopMatrix();
            ofPopMatrix();
        
        }

        ofPopStyle();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    if(key == 'a')
    {
        speed = 0;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
    
    if(key == 'a')
    {
        speed = 0.8;
    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
 //   cursor2D.set(x, y, cursor2D.z);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
//    cursor2D.set(x, y, cursor2D.z);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
