#include "ofApp.h"

#include <glm/gtx/string_cast.hpp>

const float kWorldSize = 500.0f;

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (numToAdd)
    {
        glm::vec3 v = { ofRandom(rangeMin.x, rangeMax.x),
                        ofRandom(rangeMin.y, rangeMax.y),
                        ofRandom(rangeMin.z, rangeMax.z) };
        mesh.addVertex(ofVec3f(v.x, v.y, v.z));
        set3f.add(v);

        --numToAdd;
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    camera.begin();
    {
        ofSetColor(ofColor::white);
        glPointSize(4.0f);
        mesh.draw(OF_MESH_POINTS);

        ofNoFill();

        ofSetColor(ofColor::crimson);
        ofDrawBox(set3f.getCenter().x, set3f.getCenter().y, set3f.getCenter().z,
                  set3f.getSpan().x, set3f.getSpan().y, set3f.getSpan().z);

        ofSetColor(ofColor::gold);
        ofDrawLine(set3f.getMin().x, set3f.getCenter().y, set3f.getCenter().z,
                   set3f.getMax().x, set3f.getCenter().y, set3f.getCenter().z);
        ofDrawLine(set3f.getCenter().x, set3f.getMin().y, set3f.getCenter().z,
                   set3f.getCenter().x, set3f.getMax().y, set3f.getCenter().z);
        ofDrawLine(set3f.getCenter().x, set3f.getCenter().y, set3f.getMin().z,
                   set3f.getCenter().x, set3f.getCenter().y, set3f.getMax().z);

        ofSetColor(ofColor::limeGreen);
        ofDrawLine(set3f.getMin().x, set3f.getMean().y, set3f.getMean().z,
                   set3f.getMax().x, set3f.getMean().y, set3f.getMean().z);
        ofDrawLine(set3f.getMean().x, set3f.getMin().y, set3f.getMean().z,
                   set3f.getMean().x, set3f.getMax().y, set3f.getMean().z);
        ofDrawLine(set3f.getMean().x, set3f.getMean().y, set3f.getMin().z,
                   set3f.getMean().x, set3f.getMean().y, set3f.getMax().z);

        ofSetColor(ofColor::blueSteel);
        ofDrawLine(set3f.getMin().x, set3f.getMedian().y, set3f.getMedian().z,
                   set3f.getMax().x, set3f.getMedian().y, set3f.getMedian().z);
        ofDrawLine(set3f.getMedian().x, set3f.getMin().y, set3f.getMedian().z,
                   set3f.getMedian().x, set3f.getMax().y, set3f.getMedian().z);
        ofDrawLine(set3f.getMedian().x, set3f.getMedian().y, set3f.getMin().z,
                   set3f.getMedian().x, set3f.getMedian().y, set3f.getMax().z);
    }
    camera.end();

    const float kLeft = 10;
    const float kTop = 20;
    const float kLineHeight = 20;
    int currLine = 0;

    ofSetColor(ofColor::white);
    ofDrawBitmapString(ofToString(set3f.size()) + " Vertices", kLeft, kTop + kLineHeight * currLine++);

    ofSetColor(ofColor::crimson);
    ofDrawBitmapString("Min:    " + glm::to_string(set3f.getMin()), kLeft, kTop + kLineHeight * currLine++);
    ofDrawBitmapString("Max:    " + glm::to_string(set3f.getMax()), kLeft, kTop + kLineHeight * currLine++);
    ofDrawBitmapString("Span:   " + glm::to_string(set3f.getSpan()), kLeft, kTop + kLineHeight * currLine++);

    ofSetColor(ofColor::gold);
    ofDrawBitmapString("Center: " + glm::to_string(set3f.getCenter()), kLeft, kTop + kLineHeight * currLine++);

    ofSetColor(ofColor::limeGreen);
    ofDrawBitmapString("Mean:   " + glm::to_string(set3f.getMean()), kLeft, kTop + kLineHeight * currLine++);

    ofSetColor(ofColor::blueSteel);
    ofDrawBitmapString("Median: " + glm::to_string(set3f.getMedian()), kLeft, kTop + kLineHeight * currLine++);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == OF_KEY_BACKSPACE)
    {
        mesh.clear();
        set3f.clear();
        
        numToAdd = 0;
    }
    else if (key == ' ')
    {
        numToAdd += 100;

        // Adjust the range for fun.
        rangeMin.set(ofRandom(-kWorldSize * 0.5f, 0.0f),
                     ofRandom(-kWorldSize * 0.5f, 0.0f),
                     ofRandom(-kWorldSize * 0.5f, 0.0f));
        rangeMax.set(ofRandom(0.0f, kWorldSize * 0.5f),
                     ofRandom(0.0f, kWorldSize * 0.5f),
                     ofRandom(0.0f, kWorldSize * 0.5f));
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
