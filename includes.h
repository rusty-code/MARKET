#ifndef INCLUDES_H
#define INCLUDES_H

#include <QPair>

#include <QtCore>
#include <QObject>
#include <QApplication>

#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>

#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>

#include <QtSql>
#include <QTableView>

enum class EMITS_BTN_SIGNALS
{
    // Left vertical menu
    SIG0,
    SIG1,
    SIG2,
    SIG3,
    SIG4,
    SIG5,
    SIG6,
    // Top gorizontal menu (view mods)
    EDIT,
    ONLY_VIEW,
};


#endif // INCLUDES_H
