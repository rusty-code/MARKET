#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include "../includes.h"

class CustomButton : public QPushButton
{
Q_OBJECT

private:
    QPixmap* ico_obj;
    EMITS_BTN_SIGNALS btn_sig;
    // QString btn_text;

protected:
    virtual void paintEvent(QPaintEvent*) override
    {
        QPainter painter;

        // offsets for scale image in ellipse
        int sqr_offset = 10;
        int sqr_volume = 20;

        // get button rect
        QRect menuItem_draw_ellipse
        (
            this->rect().x(),
            this->rect().y(),
            this->rect().width(),
            this->rect().height()
        );
        // draw grey rect if enable
        painter.begin(this);
        {
            if(this->isChecked())
                painter.setBrush(QBrush(Qt::black));
            else if(this->underMouse() && !this->isChecked() )
            {
                painter.setBrush(QBrush(Qt::lightGray));
            }
            else
                painter.setBrush(QBrush(Qt::white));
            painter.drawEllipse
            (
                menuItem_draw_ellipse.x(),
                menuItem_draw_ellipse.y(),
                menuItem_draw_ellipse.width(),
                menuItem_draw_ellipse.height()
            );
        }
        painter.end();

        // define draw area for image
        if(this->ico_obj != nullptr)
        {
            painter.begin(this);
                painter.drawPixmap
                (
                    QRect
                    (
                        menuItem_draw_ellipse.x()+sqr_offset,
                        menuItem_draw_ellipse.y()+sqr_offset,
                        menuItem_draw_ellipse.width()-sqr_volume,
                        menuItem_draw_ellipse.height()-sqr_volume
                    ),
                    *(this->ico_obj)
                );
            painter.end();
        }
    }

public:
    CustomButton
    (
        EMITS_BTN_SIGNALS,
        QString& _ico_path
        // QString& _btn_text
    );
    ~CustomButton();

    QPixmap* get_ico_obj();
    void set_ico_obj(QPixmap*);
    EMITS_BTN_SIGNALS get_emitted_sig();

public slots:
    void checked();

signals:
    void is_be_checked(EMITS_BTN_SIGNALS);
};

// ================

class AugmentButton : public QPushButton
{
Q_OBJECT
private:
    EMITS_BTN_SIGNALS btn_sig;
    QString btn_txt;

public:
    AugmentButton(EMITS_BTN_SIGNALS, QString&);
    ~AugmentButton();

public slots:
    void checked();

signals:
    void is_be_checked(EMITS_BTN_SIGNALS);

};

#endif // CUSTOMBUTTON_H
