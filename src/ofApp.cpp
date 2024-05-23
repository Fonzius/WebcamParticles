#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    webcam.setup(ofGetWidth(), ofGetHeight());
    
    edge.load("./shaders/edge");
        
    camFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    outFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    
    //number of particles
    unsigned w = 1000;
    unsigned h = 900;
    
    particles.init(w, h, ofPrimitiveMode::OF_PRIMITIVE_POINTS, 2);

    //POSITIONS
    float* particlePosns = new float[w * h * 4];
    for (unsigned y = 0; y < h; ++y)
    {
        for (unsigned x = 0; x < w; ++x)
        {
            unsigned idx = y * w + x;
            particlePosns[idx * 4] =     ofRandom(ofGetWidth());
            particlePosns[idx * 4 + 1] = ofRandom(ofGetHeight());
            particlePosns[idx * 4 + 2] = 0.f;
            particlePosns[idx * 4 + 3] = ofRandom(-5.5, -2.5);
        }
    }
    particles.loadDataTexture(FastParticleSystem::POSITION, particlePosns);
    delete[] particlePosns;
    
    particles.addUpdateShader("./shaders/updateParticles");
    particles.addDrawShader("./shaders/drawParticles");
    
    //MATRIX
    projection.makeIdentityMatrix();
    projection.set(ofGetCurrentMatrix(OF_MATRIX_PROJECTION));
    projection.preMult(ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
    
    modelView.makeIdentityMatrix();
    
    ofSetFrameRate(60);
         
}

//--------------------------------------------------------------
void ofApp::update(){
    webcam.update();
    
    particles.loadDataTexture(FastParticleSystem::VELOCITY, outFbo);

    ofShader &shader = particles.getUpdateShader();
    shader.begin();
    shader.setUniform1f("width", ofGetWidth());
    shader.setUniform1f("height", ofGetHeight());
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform2f("mouse", ofGetMouseX(), ofGetMouseY());
    
    particles.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    outFbo.begin();
    
        camFbo.begin();
            webcam.draw(0,0);
        camFbo.end();
    
        edge.begin();
            camFbo.draw(0,0);
        edge.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
        edge.setUniformTexture("fboTexture", camFbo.getTexture(0), 0);
        edge.end();
     
    outFbo.end();

    
    ofShader &shader = particles.getDrawShader();
    shader.begin();
    shader.setUniformMatrix4f("projection", projection);
    shader.setUniformMatrix4f("modelview", modelView);
    shader.end();
    
    ofBackground(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);
    particles.draw();
    glDisable(GL_PROGRAM_POINT_SIZE);
    glDisable(GL_BLEND);
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255, 255, 255, 5);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    outFbo.getTexture(0).draw(0,0);

    ofDisableBlendMode();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
 
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
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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
