#ifndef PUSHDATA_H
#define PUSHDATA_H

#include "../includes.h"
#include "menu_bar/InputArea.h"

class PushData : public QFrame
{
    Q_OBJECT
private:
    QList<InputArea*>* p_input_areas;
    QHBoxLayout* p_layout;

    QPushButton* p_approve_data_btn;
    QPushButton* p_cancel_btn;

public:
    explicit PushData(QList<QString>*, QPalette*);
    ~PushData();

    QList<QString>* get_area_data();

public slots:
    void slot_approved_btn();
    void slot_cancel_btn();

signals:
    void sig_approved_data(QList<QString>*, PushData*);
    void sig_cancel(QList<QString>*, PushData*);
};

#endif // PUSHDATA_H
