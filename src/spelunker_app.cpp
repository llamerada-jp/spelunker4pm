
#include "spelunker_app.h"
#include "rope.h"

/** 地図データ */
static const char MAP_NONE   = 0x00;
static const char MAP_GROUND = 0x01;

/** キー入力 */
static const int KEY_UP    = 0x01;
static const int KEY_DOWN  = 0x02;
static const int KEY_LEFT  = 0x04;
static const int KEY_RIGHT = 0x08;
static const int KEY_A     = 0x10;
static const int KEY_B     = 0x20;

//--------------------------------------------------------------
void SpelunkerApp::setup(){
    // 背景を黒に
    ofBackground(0, 0, 0);
    // 透明色を有効
    ofEnableAlphaBlending();
    
    ofSetFrameRate(60);
    
    // 画面を作成
    createMap();
    
    // スペランカー先生を作成
    sensei = new Sensei();
    sensei->x = 0;
    sensei->y = 0;
    sensei->direction = Sensei::RIGHT;
    
    objects.push_back(sensei);
}

//--------------------------------------------------------------
void SpelunkerApp::update(){
    if (sensei == NULL) {
        return;
    }
    
    { // オブジェクトの更新
        updateSensei();
        Objects::iterator it = objects.begin();
        while (it != objects.end()) {
            (*it)->update();
            it ++;
        }
    }
    
    { // 無効になったオブジェクトを削除
        Objects::iterator it = objects.begin();
        while (it != objects.end()) {
            if ((*it)->isDisable) {
                delete (*it);
                it = objects.erase(it);
                continue;
            }
            it ++;
        }
    }
}

//--------------------------------------------------------------
void SpelunkerApp::draw(){
    // 背景の描画
    for (int x = 0; x < SCREEN_W / SCALE; x ++) {
        for (int y = 0; y < SCREEN_H / SCALE ; y ++) {
            switch (map[x][y]) {
                case MAP_GROUND:
                    ofSetHexColor(OUTPUT_COLOR_GROUND);
                    break;
                    
                default:
                    continue;
                    break;
            }
            ofRect(x * SCALE, y * SCALE, SCALE, SCALE);
        }
    }
    
    // オブジェクトの描画
    for(Objects::iterator it = objects.begin(); it != objects.end(); it ++) {
        (*it)->draw();
    }
}

//--------------------------------------------------------------
void SpelunkerApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_UP:
            keyState = keyState | KEY_UP;
            break;
            
        case OF_KEY_DOWN:
            keyState = keyState | KEY_DOWN;
            break;
            
        case OF_KEY_LEFT:
            keyState = keyState | KEY_LEFT;
            break;
            
        case OF_KEY_RIGHT:
            keyState = keyState | KEY_RIGHT;
            break;
            
        case (int)'z':
            keyState = keyState | KEY_A;
            break;
            
        case (int)'x':
            keyState = keyState | KEY_B;
            break;
    }
}

//--------------------------------------------------------------
void SpelunkerApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_UP:
            keyState = keyState & ~KEY_UP;
            break;
            
        case OF_KEY_DOWN:
            keyState = keyState & ~KEY_DOWN;
            break;
            
        case OF_KEY_LEFT:
            keyState = keyState & ~KEY_LEFT;
            break;
            
        case OF_KEY_RIGHT:
            keyState = keyState & ~KEY_RIGHT;
            break;
            
        case (int)'z':
            keyState = keyState & ~KEY_A;
            break;
            
        case (int)'x':
            keyState = keyState & ~KEY_B;
            break;
            
        case (int)'f':
            ofToggleFullscreen();
            break;
            
    }
}

//--------------------------------------------------------------
void SpelunkerApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void SpelunkerApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void SpelunkerApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void SpelunkerApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void SpelunkerApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void SpelunkerApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void SpelunkerApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
int SpelunkerApp::getGroundHeight(int dx) {
    // スペランカー先生の絶対X座標
    int sx = sensei->x + sensei->w / 2 + dx;
    // スペランカー先生の絶対Y座標
    int sy = sensei->y + sensei->h;
    
    if (map[sx][sy] == MAP_GROUND) {
        int h;
        
        for (h = 0; sy > h; h ++) {
            if (map[sx][sy - h - 1] != MAP_GROUND) {
                break;
            }
        }
        
        return -h;
        
    } else {
        int h;
        
        for (h = 0; sy + h < SCREEN_H / SCALE; h ++) {
            if (map[sx][sy + h] == MAP_GROUND) {
                break;
            }
        }
        
        return h;
    }
}

//--------------------------------------------------------------
void SpelunkerApp::createMap() {
    // マップ画像をロード
    ofImage img;
    img.loadImage("map.png");
    for (int y = 0; y < SCREEN_H / SCALE; y ++) {
        int y1 =  y      * img.height * SCALE / SCREEN_H;
        int y2 = (y + 1) * img.height * SCALE / SCREEN_H;
        
        for (int x = 0; x < SCREEN_W / SCALE; x ++) {
            int x1 =  x      * img.width * SCALE / SCREEN_W;
            int x2 = (x + 1) * img.width * SCALE / SCREEN_W;
        
            char cell = MAP_NONE;
            bool ground = false;
            bool rope   = false;
            
            // セルに含まれる色を
            for (int dx = x1; dx < x2; dx ++) {
                for (int dy = y1; dy < y2; dy ++) {
                    ofColor_<unsigned char> color = img.getColor(dx, dy);
                    switch (color.getHex()) {
                        case INPUT_COLOR_GROUND:
                            ground = true;
                            break;
                            
                        case INPUT_COLOR_ROPE:
                            rope = true;
                            break;
                    }
                }
            }
            
            if (ground) { // 地面
                cell = MAP_GROUND;
                
            } else if (rope) { // ロープ
                // ロープのx座標補正
                int rx = (x / BASE) * BASE + BASE / 2 - 2;
                int ry;
                // ロープの上端を決定
                for (ry = y; ry > 0; ry --) {
                    printf("%d %d %d\n", rx, ry, map[rx][ry]);
                    if (map[rx][ry] != MAP_NONE) {
                        break;
                    }
                }
                // ロープ長(高さ)
                int len = (y / BASE) * BASE - ry;

                // 同じ位置にロープがあった場合キャンセル
                bool overlap = false;
                for (Objects::iterator it = objects.begin(); it != objects.end(); it ++) {
                    // ロープを探す
                    Rope* r = dynamic_cast<Rope*>(*it);
                    if (r == NULL) continue;
                    
                    // 同じ位置
                    if (r->x == rx && r->y == ry) {
                        overlap = true;
                    }
                }
                // 重複がなかった場合、登録
                if (!overlap) {
                    Rope* r = new Rope();
                    r->x = rx;
                    r->y = ry;
                    r->w = 4;
                    r->h = len;
                    objects.push_back(r);
                }
            }
            
            //
            map[x][y] = cell;
        }
    }
}

//--------------------------------------------------------------
void SpelunkerApp::updateSensei() {
    // 死んでいるときは操作不能
    if (sensei->status == Sensei::DEATH) {
        if (sensei->duration > 50) {
            sensei->status = Sensei::STAND;
            sensei->direction = Sensei::RIGHT;
            sensei->x = 0;
            sensei->y = 0;
        }
        return;
    }
    
    // ジャンプ中の場合位置を更新
    if (sensei->status == Sensei::JUMP_UP) {
        // 垂直ジャンプ
        if (sensei->duration < JUMP_HEIGHT) {
            sensei->y --;
        } else if (sensei->duration == JUMP_HEIGHT) {
            dropHeight = 0;
        } else {
            dropHeight ++;
            sensei->y ++;
        }
    }
    if (sensei->status == Sensei::JUMP_SIDE) {
        // 横に飛ぶ
        if (sensei->duration < JUMP_HEIGHT) {
            sensei->y --;
        } else if (sensei->duration == JUMP_HEIGHT) {
            dropHeight = 0;
        } else {
            dropHeight ++;
            sensei->y ++;
        }
        if (sensei->direction == Sensei::RIGHT) {
            if (getGroundHeight(1) > 0 && sensei->x + sensei->w < SCREEN_W / SCALE) {
                sensei->x ++;
            }
        } else {
            if (getGroundHeight(-1) > 0 && sensei->x > 0) {
                sensei->x --;
            }
        }
    }
    
    // ロープを掴んでいるか?
    Rope* handling;
    if (sensei->status == Sensei::ROPE) sensei->status = Sensei::STAND;
    for (Objects::iterator it = objects.begin(); it != objects.end(); it ++) {
        // ロープに対してのみ処理
        Rope* rope = dynamic_cast<Rope*>(*it);
        if (rope == NULL) continue;
        // 先生の足元とロープが交差していること
        if (rope->x <= sensei->x + sensei->w / 2 &&
            sensei->x + sensei->w / 2 <= rope->x + rope->w &&
            rope->y <= sensei->y &&
            sensei->y + sensei->h <= rope->y + rope->h) {
            sensei->status = Sensei::ROPE;
            handling = rope;
            break;
        }
    }
    
    if (sensei->status == Sensei::JUMP_UP || sensei->status == Sensei::JUMP_SIDE) {
        // ジャンプ中
        if (getGroundHeight() <= 0) { // 着地
            sensei->status = Sensei::STAND;
            if (dropHeight > DEATH_HEIGHT) {
                // 死亡
                sensei->status = Sensei::DEATH;
            }
        }
    } else if (sensei->status == Sensei::ROPE) {
        // ロープ中
        if ((keyState & KEY_LEFT) && !(keyState & KEY_RIGHT)) { // 左に進む
            sensei->direction = Sensei::LEFT;
            sensei->x --;
        } else if (!(keyState & KEY_LEFT) && (keyState & KEY_RIGHT)) { // 右に進む
            sensei->direction = Sensei::RIGHT;
            sensei->x ++;
        } else if (!(keyState & KEY_UP) && (keyState & KEY_DOWN)) { // 降りる
            if (getGroundHeight() > 0) {
                sensei->y ++;
            }
        } else if (!(keyState & KEY_DOWN) && (keyState & KEY_UP)) { // 登る
            if (sensei->y > handling->y) {
                sensei->y --;
            }
        }
    } else {
        // 歩行中
        if ((keyState & KEY_LEFT) && !(keyState & KEY_RIGHT)) { // 左に進む
            sensei->status = Sensei::WALK;
            sensei->direction = Sensei::LEFT;
            if (getGroundHeight(-1) > -2 && sensei->x > 0) { // 高さor画面制限を許容する場合進む
                sensei->x --;
            }
        } else if (!(keyState & KEY_LEFT) && (keyState & KEY_RIGHT)) { // 右に進む
            sensei->status = Sensei::WALK;
            sensei->direction = Sensei::RIGHT;
            if (getGroundHeight(1) > -2 &&
                sensei->x + sensei->w< SCREEN_W / SCALE) { // 高さor画面制限の許容する場合進む
                sensei->x ++;
            }
        } else { // 移動しない
            sensei->status = Sensei::STAND;
        }
        if (getGroundHeight() > DEATH_HEIGHT) {
            // 高すぎるので死亡
            sensei->status = Sensei::DEATH;
        } else if (getGroundHeight() > 2) {
            // 空中滑空
            sensei->y += 2;
        } else {
            sensei->y += getGroundHeight();
        }
        
        if (keyState & KEY_B) { // ジャンプ
            if (sensei->status == Sensei::STAND) {
                sensei->status = Sensei::JUMP_UP;
            } else {
                sensei->status = Sensei::JUMP_SIDE;
            }
        }
    }
}