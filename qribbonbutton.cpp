#include "qribbonbutton.h"

#include <QAction>
#include <QEvent>

QRibbonButton::QRibbonButton(QWidget *parent) : QToolButton(parent)
{
    init(Q_NULLPTR);
}

QRibbonButton::QRibbonButton(const QString &text, QWidget *parent) : QToolButton(parent)
{
    init(Q_NULLPTR);
    setText(text);
}

QRibbonButton::QRibbonButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    init(Q_NULLPTR);
    setIcon(icon);
    setText(text);
}

QRibbonButton::QRibbonButton(const QIcon &icon, const QString &text, const QString &name, QWidget *parent)
    : QToolButton(parent)
{
    init(&name);
    setIcon(icon);
    setText(text);
}

void QRibbonButton::init(const QString *_name)
{
    setAutoRaise(true);

    static int button_number = 0;
    button_number += 1;

    QString name;
    if (_name == Q_NULLPTR || _name->size() == 0) {
        name = name.sprintf("%s_%04d", "qribbonbut", button_number);
    } else {
        name = *_name;
    }
    this->setObjectName(name);
    this->setStyleSheet("#" + name + ":hover { background: #d5e1f2;border: none; }");
}

