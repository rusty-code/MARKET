#ifndef MENUBAR_H
#define MENUBAR_H

#include "../includes.h"
#include "CustomButton.h"

class MenuBar : public QWidget
{
Q_OBJECT
private:
    QBoxLayout* p_menu_layout;
    QList<CustomButton*>* p_items_list;

    QSize* p_size;
    QSize* p_position;

    // QPair<int, int>* __iter_buttons_sigcluster;
    // int global_buttons_coutner;

public:
    MenuBar
    (
        QSize*,
        QSize*,
        // QPair<int, int>*,
        bool _orient_layout = true/*true -> vertical*/,
        QWidget* _parent = 0
        // int _counter = 0
    );
    ~MenuBar();

    // void appendObject(EMITS_BTN_SIGNALS, QString, QString);
    void appendObject(EMITS_BTN_SIGNALS, QString);
    QList<CustomButton*>* getObjectsList();
    QBoxLayout* get_layout();

protected:
    // show all buttons
    void paintEvent(QPaintEvent*) override
    {
        QPainter painter(this);

        for
        (
            auto beg = this->p_items_list->begin();
            beg != this->p_items_list->end();
            ++beg
        )
        {
            (*beg)->show();
        }
    }

signals:
    void sig_transmission(EMITS_BTN_SIGNALS);

public slots:
    void sig_distrib_handler(EMITS_BTN_SIGNALS);
};


#endif // MENUBAR_H
