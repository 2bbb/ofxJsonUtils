#include "ofMain.h"
#include "ofxJsonUtils.h"

// 1.1 define custom struct

struct custom_struct {
    float value;
    float other_value;
};

// 1.2 define convert and parse function for custom struct

ofJson convert(const custom_struct &ps) {
    ofJson json;
    json["value"] = ps.value;
    json["other_value"] = ps.other_value;
    return json;
}

void parse(const ofJson &json, custom_struct &ps) {
    ps.value = json["value"];
    ps.other_value = json["other_value"];
}

// 2.1 define other custom struct.
// this struct has 2 methods `toJson` and `loadJson`

struct other_custom_struct {
    float value;
    float other_value;
    ofJson toJson() const {
        ofJson json;
        json["value"] = value;
        json["other_value"] = other_value;
        return json;
    }
    void loadJson(const ofJson &json) {
        value = json["value"];
        other_value = json["other_value"];
    }
};

// 3.1 define nested struct
// this can use ofxJsonUtils::create, ofxJsonUtils::load

struct nested_custom_struct : ofxJsonify<nested_custom_struct> {
    ofVec2f v;
    custom_struct cs;
    other_custom_struct ocs;
    ofJson toJson() const {
        return ofxJsonUtils::create(kv(v), kv(cs), kv(ocs));
    }
    void loadJson(const ofJson &json) {
        ofxJsonUtils::load(json, kv(v), kv(cs), kv(ocs));
    }
};

// 4.1 ofxJsonify

struct jsonify_test : ofxJsonify<jsonify_test> {
    int x{8};
    ofJson toJson() const {
        return ofxJsonUtils::create(kv(x));
    }
    void loadJson(const ofJson &json) {
        ofxJsonUtils::load(json, kv(x));
    }
};

class ofApp : public ofBaseApp {
public:
    void setup() {
        {
            // simple load
            ofJson json = ofxJsonUtils::loadFromFile("example.json");
            ofLogNotice("load test") << json.dump();
        }
        
        {
            std::vector<int> xs{1, 2, 3, 4, 5};
            ofJson json = ofxJsonUtils::convert(xs);
            ofLogNotice("vector<int>") << json.dump();
        }
        
        {
            std::vector<ofVec3f> vs;
            for(std::size_t i = 0; i < 4; i++) vs.emplace_back(i, i * i, i * i * i);
            ofJson json = ofxJsonUtils::convert(vs);
            ofLogNotice("vector<ofVec3f> dump") << json.dump();
        }
        
        {
            other_custom_struct p{1, 2};
            ofLogNotice("other_custom_struct: initialized") << p.toJson().dump();
            ofJson json({
                {"value", 2},
                {"other_value", 3}
            });
            p.loadJson(json);
            ofLogNotice("other_custom_struct: after load") << p.toJson().dump();
        }
        
        {
            jsonify_test jt;
            jt.x = 26;
            ofLogNotice("jsonify_test: jt") << jt.toJson().dump();
            jt.writeToJsonFile("test.json");
            jsonify_test jt2;
            jt2.loadFromJsonFile("test.json");
            ofLogNotice("jsonify_test: jt2") << jt2.toJsonString();
        }
        
        ofExit(0);
    }
};

int main() {
    ofSetupOpenGL(1280, 720, OF_WINDOW);
    ofRunApp(new ofApp);
}
