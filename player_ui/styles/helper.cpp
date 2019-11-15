#include "helper.h"

/*
original:   #37474f
hover:      #455a64
pressed:    #78909c
*/
/*
original:   #F5F5F5
hover:      #E0E0E0
pressed:    #E0E0E0
*/

QString StyleHelper::getWindowStyleSheet()
{
    return "QWidget { "
           "background-color: rgb(236,239,241, 90);"
            "background-position: center;"
            "border: 1px solid black;"
            "}"
            "#centralWidget { "
            "border-image: url(:/images_folder/background.jpg) 0 0 0 0 stretch stretch;"
            "}";
}

QString StyleHelper::getLabelStyleSheet(){
    return "QLabel { "
            "color: #e1f5fe; "
            "background-color: rgb(0,0,0, 0);"
            "border: none; "
            "margin: 6px; "
            "}";
}

QString StyleHelper::getBarStyleSheet(){
    return "QProgressBar { "
            "background-color: rgb(0,0,0, 0);"
            "border: none;"
            "}"
            "QProgressBar:chunk { "
            "background-color: rgb(225,245,254, 95);"
            "}";
}

QString StyleHelper::getSliderStyleSheet()
{
    return "QSlider {"
            "border: none;"
            "background-color: rgb(0,0,0, 0);"
            "}"
            "QSlider::groove:horizontal {"
            "border: 1px solid #bbb;"
            "background: white;"
            "height: 10px;"
            "border-radius: 4px;"
            "}"
            "QSlider::sub-page:horizontal {"
            "background: rgb(77,208,225, 70);"
            "border: 1px solid #777;"
            "height: 10px;"
            "border-radius: 4px;"
            "}"
            "QSlider::add-page:horizontal {"
            "background: #fff;"
            "border: 1px solid #777;"
            "height: 10px;"
            "border-radius: 4px;"
            "}"
            "QSlider::handle:horizontal {"
            "background: rgb(0,188,212);"
            "width: 13px;"
            "margin-top: -2px;"
            "margin-bottom: -2px;"
            "border-radius: 4px;"
            "}"
            "QSlider::handle:horizontal:hover {"
            "background: rgb(0,188,212);"
            "border: 1px solid #444;"
            "border-radius: 4px;"
            "}"
            "QSlider::sub-page:horizontal:disabled {"
            "background: #bbb;"
            "border-color: #999;"
            "}"
            "QSlider::add-page:horizontal:disabled {"
            "background: #eee;"
            "border-color: #999;"
            "}"
            "QSlider::handle:horizontal:disabled {"
            "background: rgb(207,216,220,70);"
            "border: 1px solid #aaa;"
            "border-radius: 4px;"
            "}";
}

QString StyleHelper::getCloseStyleSheet()
{
    return "QToolButton {"
           "image: url(:/images_folder/btnClose_original.png);"
           "icon-size: 32px;"
           "padding: 6px;"
           "border: none;"
           "background-color: rgb(0,0,0,0);"
           "}"
           "QToolButton:hover {"
           "image: url(:/images_folder/btnClose_hover.png);"
           "}"
           "QToolButton:pressed {"
           "image: url(:/images_folder/btnClose_pressed.png);"
           "}";
}

QString StyleHelper::getMaximizeStyleSheet(){
    return "QToolButton {"
           "image: url(:/images_folder/btnSize_original.png);"
           "icon-size: 32px;"
           "padding: 6px;"
           "border: none;"
           "background-color: rgb(0,0,0,0);"
           "}"
           "QToolButton:hover {"
           "image: url(:/images_folder/btnSize_hover.png);"
           "}"
           "QToolButton:pressed {"
           "image: url(:/images_folder/btnSize_pressed.png);"
           "}";
}

QString StyleHelper::getSettingsStyleSheet(){
    return "QToolButton {"
           "image: url(:/images_folder/btnSettings_original.png);"
           "icon-size: 32px;"
           "padding: 6px;"
           "border: none;"
           "background-color: rgb(0,0,0,0);"
           "}"
           "QToolButton:hover {"
           "image: url(:/images_folder/btnSettings_hover.png);"
           "}"
           "QToolButton:pressed {"
           "image: url(:/images_folder/btnSettings_pressed.png);"
           "}";
}

QString StyleHelper::getMinimizeStyleSheet(){
    return "QToolButton {"
           "image: url(:/images_folder/btnMin_original.png);"
           "icon-size: 32px;"
           "padding: 6px;"
           "border: none;"
           "background-color: rgb(0,0,0,0);"
           "}"
           "QToolButton:hover {"
           "image: url(:/images_folder/btnMin_hover.png);"
           "}"
           "QToolButton:pressed {"
           "image: url(:/images_folder/btnMin_pressed.png);"
           "}";
}

QString StyleHelper::getNextStyleSheet(){
    return "QToolButton {"
           "image: url(:/images_folder/btnNext_original.png);"
           "icon-size: 16px;"
           "padding: 6px;"
           "border: none;"
           "background-color: rgb(0,0,0, 0);"
           "}"
           "QToolButton:hover {"
           "image: url(:/images_folder/btnNext_hover.png);"
           "}"
           "QToolButton:pressed {"
           "image: url(:/images_folder/btnNext_pressed.png);"
           "}";
}

QString StyleHelper::getPreviousStyleSheet(){
    return "QToolButton {"
           "image: url(:/images_folder/btnPrevious_original.png);"
           "icon-size: 16px;"
           "padding: 6px;"
           "border: none;"
           "background-color: rgb(0,0,0, 0);"
           "}"
           "QToolButton:hover {"
           "image: url(:/images_folder/btnPrevious_hover.png);"
           "}"
           "QToolButton:pressed {"
           "image: url(:/images_folder/btnPrevious_pressed.png);"
           "}";
}

QString StyleHelper::getStopStyleSheet(){
    return "QToolButton {"
           "image: url(:/images_folder/btnStop_original.png);"
           "icon-size: 16px;"
           "padding: 6px;"
           "border: none;"
           "background-color: rgb(0,0,0, 0);"
           "}"
           "QToolButton:hover {"
           "image: url(:/images_folder/btnStop_hover.png);"
           "}"
           "QToolButton:pressed {"
           "image: url(:/images_folder/btnStop_pressed.png);"
           "}";
}

QString StyleHelper::getPlayStyleSheet(){
    return "QToolButton {"
           "image: url(:/images_folder/btnPlay_original.png);"
           "icon-size: 22px;"
           "padding: 6px;"
           "border: none;"
           "background-color: rgb(0,0,0,0);"
           "}"
           "QToolButton:hover {"
           "image: url(:/images_folder/btnPlay_hover.png);"
           "}"
           "QToolButton:pressed {"
           "image: url(:/images_folder/btnPlay_pressed.png);"
           "}";
}

QString StyleHelper::getPauseStyleSheet(){
    return "QToolButton {"
           "image: url(:/images_folder/btnPause_original.png);"
           "icon-size: 16px;"
           "padding: 6px;"
           "border: none;"
           "background-color: rgb(0,0,0, 0);"
           "}"
           "QToolButton:hover {"
           "image: url(:/images_folder/btnPause_hover.png);"
           "}"
           "QToolButton:pressed {"
           "image: url(:/images_folder/btnPause_pressed.png);"
           "}";
}

QString StyleHelper::getMenuStyleSheet(){
    return "QToolButton {"
            "color:#8f8f8f;"
            "background-color: #292929;"
            "icon-size: 12px;"
            "padding-left: 10px;"
            "padding-right: 10px;"
            "padding-top: 5px;"
            "padding-bottom: 5p;"
            "border: 1px solid #292929;"
            "}"
            "QToolButton:hover {"
            "color: white;"
            "}"
            "QToolButton:pressed {"
            "color: white;"
            "background-color: #de8e37;"
            "}";
}

QString StyleHelper::getTableStyleSheet(){
    return "QTableView {"
           "border: none;"
           "color: rgb(225,245,254);"
           "background-color: rgb(225,245,254, 50);"
           "border: none;"
           "}"
           "QTableView::item {"
           "background-color: rgb(224,247,250, 70);"
           "}"
           "QTableView::item:selected {"
           "background-color: rgb(128,222,234, 95);"
           "}"
           "QHeaderView:section:horizontal {"
           "background-color: rgb(225,245,254, 50);"
           "border: none;"
           "color: black;"
           "padding: 6px;"
           "}";
}

QString StyleHelper::getButtonAddStyleSheet()
{
    return "QToolButton {"
            "color: rgb(225,245,254);"
            "background-color: rgb(225,245,254, 90);"
            "border: none;"
            "}"
            "QToolButton:hover {"
            "background-color: rgb(225,245,254, 70);"
            "}"
            "QToolButton:pressed {"
            "background-color: rgb(207,216,220, 70);"
            "}";
}

QString StyleHelper::getReconnectStyleSheet()
{
    return "QToolButton {"
           "image: url(:/images_folder/btnReconnect_original.png);"
           "icon-size: 22px;"
           "padding: 6px;"
           "border: none;"
           "background-color: rgb(0,0,0,0);"
           "}"
           "QToolButton:hover {"
           "image: url(:/images_folder/btnReconnect_hover.png);"
           "}"
           "QToolButton:pressed {"
           "image: url(:/images_folder/btnReconnect_pressed.png);"
           "}";
}
