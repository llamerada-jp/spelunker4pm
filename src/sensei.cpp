//
//  sensei.cpp
//  spelunker
//
//  Created by 祐司 on 2013/08/13.
//
//

#include "const.h"
#include "sensei.h"

// コンストラクタ
Sensei::Sensei() {
    // キャラクタのイメージは16*16pxとする
    w = 16;
    h = 16;
    // 画像のロード
    imgStand.loadImage("sensei0.png");
    imgWalk[0].loadImage("sensei1.png");
    imgWalk[1].loadImage("sensei2.png");
    imgWalk[2].loadImage("sensei3.png");
    imgWalk[3].loadImage("sensei2.png");
    imgJumpUp.loadImage("sensei5.png");
    imgJumpSide.loadImage("sensei6.png");
    imgRope[0].loadImage("sensei8.png");
    imgRope[1].loadImage("sensei9.png");
}

//
void Sensei::draw() {
    // 画像イメージはどれか
    ofImage* target;
    switch (status) {
        case WALK:
            target = &imgWalk[(x / 4) % 4];
            break;
            
        case JUMP_UP:
            target = &imgJumpUp;
            break;
            
        case JUMP_SIDE:
            target = &imgJumpSide;
            break;
            
        case ROPE:
            target = &imgRope[(y / 4) % 2];
            break;
            
        case DEATH:
            if ((duration / 4) % 2 == 0) {
                target = NULL;
            } else {
                target = &imgStand;
            }
            break;
            
        default:
            target = &imgStand;
            break;
    }
    
    // 画像がない場合貼り付けを行わない
    if (target == NULL) {
        return;
    }
    // 貼り付け処理
    ofSetHexColor(0xffffff);
    if (direction == LEFT) {
        // 左向きの場合、画像を反転して作成
        target->mirror(false, true);
        target->draw(x * SCALE, y * SCALE, w * SCALE, h * SCALE);
        target->mirror(false, true);
    } else {
        target->draw(x * SCALE, y * SCALE, w * SCALE, h * SCALE);
    }
}

//
void Sensei::update() {
    // コマ送り
    if (status == statusPrev) {
        duration ++;
    } else {
        duration = 0;
        statusPrev = status;
    }
}