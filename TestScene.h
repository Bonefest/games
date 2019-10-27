#ifndef TESTSCENE_H_
#define TESTSCENE_H_

#include "cocos2d.h"
#include "ui/UIButton.h"

class TestScene : public cocos2d::Scene {
public:
    CREATE_FUNC(TestScene);
    bool init();
    void initListeners();
    void setMenuScene(cocos2d::Scene* menuScene);

    void activateDebug(bool activate);

    virtual void onMouseDown(cocos2d::EventMouse* event) {}
    virtual void onMouseUp(cocos2d::EventMouse* event) {}
    virtual void onMouseMove(cocos2d::EventMouse* event) {}

protected:
    void drawChildBoundingBoxes();
    bool drawingBoundingBoxes;
    cocos2d::DrawNode* _debugDrawer;

private:
    void backButtonCallback(cocos2d::Ref* psender);

    cocos2d::ui::Button* _backButton;
};


#endif // TESTSCENE_H_
