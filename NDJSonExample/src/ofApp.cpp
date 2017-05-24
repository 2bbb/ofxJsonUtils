#include "ofMain.h"
#include "ofxJsonUtils.h"

class ofApp : public ofBaseApp {
    void loadNDJson() {
        std::vector<ofJson> ndjson = ofxJsonUtils::loadNDJsonFromFile("example.ndjson");
        for(const auto &json : ndjson) {
            ofLogNotice("loaded") << json.dump();
        }
    }
    
    void writeNDJson() {
        std::vector<ofJson> jsons;
        jsons.resize(10);
        for(std::size_t i = 0; i < 10; i++) {
            jsons[i]["foo"] = i;
        }
        ofxJsonUtils::writeToNDJsonFile("write_test.ndjson", jsons);
    }
public:
    void setup() {
        loadNDJson();
        writeNDJson();
        
        ofExit();
    }
};

int main() {
    ofSetupOpenGL(1280, 720, OF_WINDOW);
    ofRunApp(new ofApp());
}
