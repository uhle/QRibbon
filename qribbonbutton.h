#ifndef QRIBBONBUTTON_H
#define QRIBBONBUTTON_H

#include "qribbon_global.h"

#include <QToolButton>


class QRIBBON_EXPORT QRibbonButton : public QToolButton
{
    Q_OBJECT

private:
    void init(const QString *_name);

public:
    QRibbonButton(QWidget *parent);
    QRibbonButton(const QString &text, QWidget *parent = Q_NULLPTR);
    QRibbonButton(const QIcon &icon, const QString &text, QWidget *parent = Q_NULLPTR);
    QRibbonButton(const QIcon &icon, const QString &text, const QString &name, QWidget *parent = Q_NULLPTR);

};

#endif // QRIBBONBUTTON_H
