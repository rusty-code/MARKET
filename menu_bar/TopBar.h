#ifndef TOPBAR_H
#define TOPBAR_H

#include "../includes.h"
#include "InputArea.h"


class TopBar : public QWidget
{
Q_OBJECT
private:
    QHBoxLayout* p_layout;

    QLabel* p_curr_tname;
    // InputArea* p_filter;
    // InputArea* p_delete_line;
    QPushButton* p_delete_row;
    QPushButton* p_add_new_row;

    QSize* pos;
    QSize* size;

public:
    TopBar
    (
        QSize* _pos,
        QSize* _size,
        QWidget* _parent = nullptr
    );
    ~TopBar();

public slots:
    void slot_set_tname(QString&);

    void slot_add_new_row(void);
    void slot_delete_selected_row(void);

signals:
    void sig_add_new_row();
    void sig_delete_selected_row();
};


#endif // TOPBAR_H
