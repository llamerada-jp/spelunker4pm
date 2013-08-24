#pragma once
//
//  object.h
//  spelunker
//
//  Created by 祐司 on 2013/08/10.
//
//

class Object {
protected:
    /**
     * 基底コンストラクタ。
     */
    Object();
    
public:
     /** 位置 */
    int x, y;
    /** 大きさ */
    unsigned int w, h;
    /** 無効フラグ */
    bool isDisable;

    /**
     * デストラクタ。
     */
    virtual ~Object();
    
    /**
     */
    virtual void draw() = 0;
    
    /**
     */
    virtual void update() = 0;
};