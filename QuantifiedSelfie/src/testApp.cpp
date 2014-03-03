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
    
    csv.loadFile(ofToDataPath("iTunes-log2.csv"));
    
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
    cam.reset();
    
    timestamp = ofGetElapsedTimef();
    
    //loads songs
    for(int i = 1; i < csv.numRows; i++) {
        if (ofToInt(csv.data[i][2]) == currentMonth) {
            ofColor sphereColor; //= ofColor::fromHex(0xFFFF00);
            int rating = ofToInt(csv.data[i][3]);
            string genre = csv.data[i][1];
            
            DemoSphere d;
            
            d.color = ofColor(ofRandom(50,255),
                              ofRandom(200),
                              ofRandom(125));
           
            
            //I decided not to include the genre in the
            //final version because the color scheme would not be
            //as aesthetically pleasing
            //and to allow for easier readability
            /*
            if(genre.find("Alternative") !=std::string::npos) {
                d.color = ofColor::fromHex(0xffb732);
            }
            
            else if(genre.find("Anime")!=std::string::npos) {
                d.color = ofColor::fromHex(0x7d9a54);

            }
            
            else if(genre.find("Classical")!=std::string::npos) {
                d.color = ofColor::fromHex(0x3cb1b6);
                
            }
            
            else if(genre.find("Folk")!=std::string::npos) {
                d.color = ofColor::fromHex(0x894f21);
            }
            
            else if(genre.find("Game")!=std::string::npos) {
                d.color = ofColor::fromHex(0xdd5548);
            }
            
            else if(genre.find("Soundtrack")!=std::string::npos) {
                d.color = ofColor::fromHex(0xD0ED91);
            }
            
            else if(genre.find("Holiday")!=std::string::npos) {
                d.color = ofColor::fromHex(0xF291CF);
            }
            
            else if(genre.find("Indie")!=std::string::npos) {
                d.color = ofColor::fromHex(0xFFFC3B);
            }
            
            else if(genre.find("Instrumental")!=std::string::npos) {
                d.color = ofColor::fromHex(0xB8B5F5);
            }
            
            else if(genre.find("Pop")!=std::string::npos) {
                d.color = ofColor::fromHex(0xD435BE);
            }
            
            else if(genre.find("Oldies")!=std::string::npos) {
                d.color = ofColor::fromHex(0xCFB97C);
            }
            
            else if(genre.find("Rock")!=std::string::npos) {
                d.color = ofColor::fromHex(0x714BDB);
            }
            
            else if(genre.find("Trailer")!=std::string::npos) {
                d.color = ofColor::fromHex(0xFFBDBD);
            }
            
            else {
                d.color = ofColor::fromHex(0x919191);
            }
             */
            
            d.pos = ofVec3f(ofRandom(-200,200), ofRandom(-200, 200), ofRandom(-20000000, -50000));
            
            d.floatPos.y = d.pos.y;
            d.floatPos.x = d.pos.x;
            
            d.radius = ofMap(rating, 10, 100, 5, 20);
            
            d.bHighlighted = false;
            
            string songname = csv.data[i][0];
            
            speeds.push_back(20.0/ofRandom(5, 20));
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
            
    if (wordRecognized == "january") {
        wordlist.push_back(wordRecognized);
        currentMonth = 1;
        currentMonthString = "January";
        makeSpheres();
    }
    
    else if (wordRecognized == "february") {
        wordlist.push_back(wordRecognized);
        currentMonth = 2;
        currentMonthString = "February";
        makeSpheres();
    }
    
    else if (wordRecognized == "march") {
        wordlist.push_back(wordRecognized);
        currentMonth = 3;
        currentMonthString = "March";
        makeSpheres();
    }
    
    else if (wordRecognized == "april") {
        wordlist.push_back(wordRecognized);
        currentMonth = 4;
        currentMonthString = "April";
        makeSpheres();
    }
    
    else if (wordRecognized == "may") {
        wordlist.push_back(wordRecognized);
        currentMonth = 5;
        currentMonthString = "May";
        makeSpheres();
    }
    
    else if (wordRecognized == "june") {
        wordlist.push_back(wordRecognized);
        currentMonth = 6;
        currentMonthString = "June";
        makeSpheres();
    }
    
    else if (wordRecognized == "july") {
        wordlist.push_back(wordRecognized);
        currentMonth = 7;
        currentMonthString = "July";
        makeSpheres();
    }
    
    else if (wordRecognized == "august") {
        wordlist.push_back(wordRecognized);
        currentMonth = 8;
        currentMonthString = "August";
        makeSpheres();
    }
    
    else if (wordRecognized == "september") {
        wordlist.push_back(wordRecognized);
        currentMonth = 9;
        currentMonthString = "September";
        makeSpheres();
    }
    
    else if (wordRecognized == "october") {
        wordlist.push_back(wordRecognized);
        currentMonth = 10;
        currentMonthString = "October";
        makeSpheres();
    }
    
    else if (wordRecognized == "november") {
        wordlist.push_back(wordRecognized);
        currentMonth = 11;
        currentMonthString = "November";
        makeSpheres();
    }
    
    else if (wordRecognized == "december") {
        wordlist.push_back(wordRecognized);
        currentMonth = 12;
        currentMonthString = "December";
        makeSpheres();
    }
    

}


//--------------------------------------------------------------
void testApp::update()
{
    if (ofGetElapsedTimef() - timestamp >= 4.0) {
        for(int i = 0; i < demos.size(); i++){
            float xPos = demos[i].pos.x/100.0;
            float yPos = demos[i].pos.y/100.0;
            //float rad = 20.0/demos[i].radius; //bigger spheres move more slowly
            //demos[i].floatPos.z += speed * rad;
            demos[i].floatPos.z += speed * speeds[i];
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
    if(key == ' ')
    {
        speed = 0;
    }
    
    //testing
    if(key == '1')
    {
        currentMonth = 1;
        currentMonthString = "January";
        makeSpheres();
    }
    
    if(key == '2')
    {
        currentMonth = 2;
        currentMonthString = "February";
        makeSpheres();
    }
    
    if(key == '3')
    {
        currentMonth = 3;
        currentMonthString = "March";
        makeSpheres();
    }
    
    if(key == '4')
    {
        currentMonth = 4;
        currentMonthString = "April";
        makeSpheres();
    }
    
    if(key == '5')
    {
        currentMonth = 5;
        currentMonthString = "May";
        makeSpheres();
    }
    
    if(key == '6')
    {
        currentMonth = 6;
        currentMonthString = "June";
        makeSpheres();
    }
    
    if(key == '7')
    {
        currentMonth = 7;
        currentMonthString = "July";
        makeSpheres();
    }
    
    if(key == '8')
    {
        currentMonth = 8;
        currentMonthString = "August";
        makeSpheres();
    }
    
    if(key == '9')
    {
        currentMonth = 9;
        currentMonthString = "September";
        makeSpheres();
    }
    
    if(key == '0')
    {
        currentMonth = 10;
        currentMonthString = "October";
        makeSpheres();
    }
    
    if(key == '-')
    {
        currentMonth = 11;
        currentMonthString = "November";
        makeSpheres();
    }
    
    if(key == '=')
    {
        currentMonth = 12;
        currentMonthString = "December";
        makeSpheres();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
    
    if(key == ' ')
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
