//
//  rope.cpp
//  spelunker
//
//  Created by 祐司 on 2013/08/17.
//
//

#include "ofMain.h"

#include "rope.h"
#include "const.h"

//
void Rope::draw() {
    for (int i = 0; i < h; i ++) {
        int r = (y + i) % BASE;
        if (r >= (BASE / 2)) {
            ofSetHexColor(OUTPUT_COLOR_ROPE1);
            ofRect((x + 1) * SCALE, (y + i) * SCALE, SCALE, SCALE);
        } else {
            ofSetHexColor(OUTPUT_COLOR_ROPE2);
            ofRect((x + 2) * SCALE, (y + i) * SCALE, SCALE, SCALE);
        }
    }
}

//
void Rope::update() {
    
}