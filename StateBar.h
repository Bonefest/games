#ifndef STATEBAR_H_INCLUDED
#define STATEBAR_H_INCLUDED

#include "cocos2d.h"
#include "ui/UIText.h"

/*

Полоска состояния, наблюдатель, который добавляется к какому-угодно
реализующему субъекта объекту. При изменение субъекта, он оповещает
об этом эту полоску.

*/

/*

class Observer {
public:
    virtual void onNotifyMessage(Subject* subject,void* data);
}

*/

class StateBar: public cocos2d::DrawNode {
public:
    static StateBar* createStateBar(cocos2d::Size size,cocos2d::Color4F color = cocos2d::Color4F::WHITE,
                                    float borderSize = 10.0f,
                                    cocos2d::Color4F borderColor = cocos2d::Color4F::WHITE);
    virtual bool init();


    void setValue(double value);
    void setMaxValue(double value);

    void setBarColor(cocos2d::Color4F color);
    cocos2d::Color4F getBarColor() const { return color; }

    void setBorderBarColor(cocos2d::Color4F color);
    cocos2d::Color4F getBorderBarColor() const { return borderColor; }

    double getMaxValue() const { return maximalValue; }
    double getCurrentValue() const { return currentValue; }
    double getPercentValue() const;

    void setEnableText(bool show);
    bool isTextEnabled() const { return textEnabled; }

    virtual void setContentSize(const cocos2d::Size& size);
    void setBorderSize(float size);

    float getBorderSize() const { return borderSize; }

    void drawBar();

private:
    void updateText();

    double currentValue;
    double maximalValue;

    cocos2d::Color4F color;
    cocos2d::Color4F borderColor;

    float borderSize;

    cocos2d::ui::Text* valueText;
    bool textEnabled;

};

#endif // STATEBAR_H_INCLUDED
