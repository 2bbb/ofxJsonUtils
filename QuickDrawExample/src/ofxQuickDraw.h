//
//  ofxQuickDraw.h
//
//  Created by Yusuke Tomoto
//
//

#ifndef ofxQuickDraw_h
#define ofxQuickDraw_h

#include "ofxJsonUtils.h"

#define OFX_QUICK_DRAW_BEGIN_NAMESPACE namespace ofx { namespace quickdraw {
#define OFX_QUICK_DRAW_END_NAMESPACE } }

OFX_QUICK_DRAW_BEGIN_NAMESPACE

class Drawing {
    vector<ofPolyline> strokes;
public:
    
    void draw() const {
        for (const auto &stroke : strokes) {
            stroke.draw();
        }
    }
    
    void addStroke(const ofPolyline &stroke) {
        strokes.push_back(stroke);
    }
    
    const vector<ofPolyline>& getStrokes() const {
        return strokes;
    }
    
    void clear() {
        strokes.clear();
    }
};

void parse(const ofJson &json, Drawing &qd) {
    qd.clear();
    vector<vector<vector<int>>> raw_data;
    ofxJsonUtils::parse(json, raw_data);
    for (auto& stroke_data : raw_data) {
        assert(stroke_data.size() == 2);
        const auto &x__ = stroke_data[0];
        const auto &y__ = stroke_data[1];
        ofPolyline stroke;
        for (int i=0; i < x__.size(); i++) {
            stroke.addVertex(x__[i], y__[i]);
        }
        qd.addStroke(stroke);
    }
}

OFX_QUICK_DRAW_END_NAMESPACE

namespace ofxQuickDraw = ofx::quickdraw;

#endif /* ofxQuickDraw_h */
