#include "PushData.h"

PushData::PushData
(
    QList<QString>* _p_area_content,
    QPalette* _p_palette
)
{
    // setup this geometry
    this->setAutoFillBackground(true);
    this->setPalette(*(_p_palette));

    // this->resize(100*_p_area_content->size(), 60);
    this->setGeometry(
        0,
        0,
        100*_p_area_content->size(),
        60
        );

    // setup widget layout
    this->p_layout = new QHBoxLayout;

    // setup input area
    this->p_input_areas = new QList<InputArea*>;
    for
    (
        auto iter = _p_area_content->begin();
        iter != _p_area_content->end();
        ++iter
    )
    {
        InputArea* p_inpt = new InputArea(*iter);
        qDebug() << *iter;

        this->p_input_areas->append(p_inpt);
        this->p_layout->addWidget(p_inpt);
        this->p_layout->addWidget(p_inpt->get_edit_area());
    }

    // setup buttons
    this->p_approve_data_btn = new QPushButton("Approve");
    this->p_cancel_btn = new QPushButton("Cancel");

    this->p_layout->addWidget(this->p_approve_data_btn);
    this->p_layout->addWidget(this->p_cancel_btn);

    this->setLayout(this->p_layout);

    // setup connects
    connect // approve data
    (
        this->p_approve_data_btn,
        &QPushButton::clicked,
        this,
        &PushData::slot_approved_btn
    );

    connect // cancel data
    (
        this->p_cancel_btn,
        &QPushButton::clicked,
        this,
        &PushData::slot_cancel_btn
    );
}

PushData::~PushData()
{
    delete this->p_input_areas;
}

QList<QString>* PushData::get_area_data()
{
    // transmission
    QList<QString>* lst = new QList<QString>;

    for
    (
        auto iter = this->p_input_areas->begin();
        iter != this->p_input_areas->end();
        ++iter
    )
    {
        lst->push_back((*iter)->get_edit_area()->text());
    }

    return lst;
}

void PushData::slot_approved_btn()
{
    emit this->sig_approved_data(this->get_area_data());
}

void PushData::slot_cancel_btn()
{
    emit this->sig_cancel(nullptr);
}
