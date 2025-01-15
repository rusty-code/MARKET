#ifndef TOPBAR_H
#define TOPBAR_H

#include "../includes.h"


class InputArea : public QLabel
{
Q_OBJECT
private:
    QLineEdit* p_ledit;

public:
    InputArea(QString);
    ~InputArea();
    QLineEdit* get_edit_area();

public slots:
    void slot_enter_pressed();

signals:
    void sig_get_text(const QString&);
};


class TopBar : public QWidget
{
Q_OBJECT
private:
    QHBoxLayout* p_layout;

    QLabel* p_curr_tname;
    InputArea* p_filter;
    InputArea* p_delete_line;
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
    void slot_filter_transmitter(const QString&);
    void slot_delete_rownum_transmitter(const QString&);
    void slot_add_new_row();

signals:
    void sig_filter_data_transmitter(const QString&);
    void sig_delete_rownum_transmitter(const QString&);
    void sig_add_new_row();
};


#endif // TOPBAR_H
