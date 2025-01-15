#ifndef INPUTAREA_H
#define INPUTAREA_H

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

#endif
