#ifndef QRIBBONTEST_H
#define QRIBBONTEST_H

#include <QMainWindow>

class QRibbonTest : public QMainWindow
{
    Q_OBJECT

public slots:
    void action();
    void indexChanged(int tab);

public:
    QRibbonTest();
    ~QRibbonTest();

    virtual QSize minimumSizeHint() const;
    virtual QSize sizeHint() const;
    virtual void setVisible(bool visible);

    QWidget *boundingWindow;
};

#endif // QRIBBONTEST_H
