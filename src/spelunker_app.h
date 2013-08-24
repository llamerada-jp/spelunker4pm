#pragma once

// std
#include <list>
// of
#include "ofMain.h"
// local
#include "const.h"
#include "object.h"
#include "sensei.h"

class SpelunkerApp : public ofBaseApp{
private:
    /** フィールド上のオブジェクト一覧 */
    typedef std::list<Object*> Objects;
    Objects objects;
    
    /** キー入力 */
    int keyState;
    
    /** スペランカー先生 */
    Sensei* sensei = NULL;
    
    /** ジャンプで落下した高さ */
    int dropHeight;
    
    /** 地図データ */
    char map[SCREEN_W / SCALE][ SCREEN_H / SCALE];
    
    
public:
    //
    void setup();
    void update();
    void draw();
    
    //
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    /**
     * 地面からの高さを計算。
     * @param dx x座標の補正値
     * @return 地面からの高さ
     */
    int getGroundHeight(int dx = 0);
    
    void createMap();
    
    void updateSensei();
};
