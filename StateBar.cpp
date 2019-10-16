#include "StateBar.h"
#include <sstream>

StateBar* StateBar::createStateBar(cocos2d::Size size,cocos2d::Color4F color,
                                    float borderSize,
                                    cocos2d::Color4F borderColor) {
    StateBar* bar = new StateBar;
    if(bar->init()) {
        bar->setBarColor(color);
        bar->setContentSize(size);

        bar->setBorderBarColor(borderColor);
        bar->setBorderSize(borderSize);

        return bar;
    }
    CC_SAFE_DELETE(bar);
    return nullptr;
}

bool StateBar::init() {
    if(cocos2d::DrawNode::init()) {
        valueText = cocos2d::ui::Text::create("","fonts/arial.ttf",14);
        if(valueText) {
            valueText->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
            setEnableText(true);
            addChild(valueText);

            return true;
        }
        return false;

    }
    return false;
}
void StateBar::setBarColor(cocos2d::Color4F color) {
    this->color = color;
}

void StateBar::setBorderBarColor(cocos2d::Color4F color) {
    this->borderColor = color;
}

void StateBar::setBorderSize(float size) {
    borderSize = size;
}

void StateBar::setEnableText(bool show) {
    textEnabled = show;
    if(!textEnabled) {
        valueText->setString("");
    }
}

void StateBar::setValue(double value) {
    currentValue = value;
    updateText();
}

void StateBar::setMaxValue(double value) {
    maximalValue = value;
    updateText();
}

double StateBar::getPercentValue() const {
    return getCurrentValue()/getMaxValue();
}

void StateBar::setContentSize(const cocos2d::Size& size) {
    cocos2d::DrawNode::setContentSize(size);
    valueText->setPosition(0.5*size);
}


void StateBar::drawBar() {
    clear();
    cocos2d::Size barSize = getContentSize();


    if(getBorderSize() > 0.0f) {
        drawRect(cocos2d::Vec2::ZERO,barSize,getBorderBarColor());
    }

    drawSolidRect(cocos2d::Vec2::ZERO,cocos2d::Vec2(std::max(float(barSize.width*getPercentValue()),0.0f),std::max(float(barSize.height),0.0f)),getBarColor());
}

void StateBar::updateText() {
    if(isTextEnabled()) {
        std::stringstream format;
        format.precision(2);
        format.setf(std::ios::fixed);
        format << currentValue << "/" << maximalValue;
        valueText->setString(format.str());
        cocos2d::Size barSize = getContentSize();
        cocos2d::Size textSize = valueText->getContentSize() + cocos2d::Size(2.0f,2.0f);
        setContentSize(cocos2d::Size(std::max(barSize.width,textSize.width),
                                     std::max(barSize.height,textSize.height)));

    }
}
