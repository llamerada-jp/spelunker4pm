//
//  object.cpp
//  spelunker
//
//  Created by 祐司 on 2013/08/10.
//
//

#include "object.h"

// コンストラクタ
Object::Object() {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    isDisable = false;
}

// デストラクタ
Object::~Object() {
    // 何もしない
}
