#pragma once
//
//  spelunker.h
//  spelunker
//
//  Created by 祐司 on 2013/08/10.
//
//

#include "ofMain.h"
#include "object.h"

class Sensei : public Object {
private:
    // 画像
    ofImage imgStand; // 立ち
    ofImage imgWalk[4]; // 歩行アニメ
    ofImage imgJumpUp;  // 垂直ジャンプ
    ofImage imgJumpSide; // 横ジャンプ
    ofImage imgRope[2];  // ロープアニメ
public:
    /** スペランカー先生の状態 */
    enum Status {
        STAND,
        WALK,
        JUMP_UP,
        JUMP_SIDE,
        ROPE,
        DEATH,
    };
    Status status;
    Status statusPrev;
    // 同じ状態が続いている時間
    int duration;
    
    
    /** 方向 */
    enum Direction {
        LEFT,
        RIGHT,
    };
    Direction direction;

    // コンストラクタ
    Sensei();
    
    /**
     */
    void draw();

    /**
     */
    void update();
};