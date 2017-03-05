#include "ofMain.h"
#include "ofxJsonUtils.h"

class ofApp : public ofBaseApp {
    void loadExample() {
        ofJson json = ofxJsonUtils::loadFromFile("data.json");
        
        int foo = json["foo"];
        ofLogNotice() << "foo: " << foo;
        
        std::vector<int> bar = json["bar"];
        for(auto i : bar) ofLogNotice() << "bar: " << i;
        
        ofJson::object_t baz = json["baz"];
        ofLogNotice() << "baz: " << baz;
        
        float fuga = baz["fuga"];
        ofLogNotice() << "fuga: " << fuga;
        
        std::string piyo = baz["piyo"];
        ofLogNotice() << "piyo: " << piyo;
    }
    
    void writeExample() {
        ofVec3f v(1, 2, 3);
        ofVec4f w(4, 5, 6, 7);
        ofColor c(0, 255, 0);
        std::vector<int> xs{10, 11, 12, 13};
        
        ofJson json = ofxJsonUtils::create("vec3", v, "vec4", w, "color", c, "int_array", xs);
        ofxJsonUtils::writeToFile("save_data.json", json);
        
        ofJson json2 = ofxJsonUtils::create(kv(v), kv(w), kv(c), kv(xs));
        ofxJsonUtils::writeToFile("save_data2.json", json2);
    }
public:
    void setup() {
        loadExample();
        writeExample();
        
        ofExit();
    }
};

//========================================================================
int main() {
    ofSetupOpenGL(200, 200, OF_WINDOW);
    ofRunApp(new ofApp());
}
