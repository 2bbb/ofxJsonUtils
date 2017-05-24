#include "ofMain.h"

#include "ofxQuickDraw.h"
#include "ofxJsonUtils.h"

class ofApp : public ofBaseApp {
    std::vector<ofxQuickDraw::Drawing> drawings;
    std::size_t index = 0;
public:
    void setup() {
        // ndjson data from https://console.cloud.google.com/storage/browser/quickdraw_dataset/full/simplified
        auto jsons = ofxJsonUtils::loadNDJsonFromFile("apple.ndjson");
        std::for_each(jsons.begin(), jsons.end(), [this](const ofJson &json) {
            ofxQuickDraw::Drawing drawing;
            ofxJsonUtils::load(json, "drawing", drawing);
            drawings.push_back(std::move(drawing));
        });
        ofBackground(0, 0, 0);
    }
    void update() {
        index = (index + 1) % drawings.size();
    }
    void draw() {
        ofSetColor(255);
        drawings[index].draw();
    }
};

int main() {
    ofSetupOpenGL(640, 640, OF_WINDOW);
    ofRunApp(new ofApp());
}
