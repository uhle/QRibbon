#include "qribbonsection.h"
#include "qribbontest.h"
#include "qribbon.h"

#include <QComboBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <cstdio>

QRibbonTest::QRibbonTest()
{
    QPlainTextEdit *textEdit = new QPlainTextEdit;
    textEdit->insertPlainText("Hallo allemaal!\n\nDit is een tekst!");
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    boundingWindow = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    boundingWindow->setLayout(layout);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(this);

    QPushButton *b1 = new QPushButton("Hi!", this);
    b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton *b2 = new QPushButton("Hallo", this);
    connect(b1, SIGNAL(clicked()), this, SLOT(action()));
    connect(b2, SIGNAL(clicked()), this, SLOT(action()));

    QRibbon *ribbon = new QRibbon(this);
    QWidget* tab = ribbon->addRibbonTab("Start", "start");

    QRibbonSection *one = new QRibbonSection(tab, "Section One", "one");
    one->addWidget(b1, "b1");
    one->addWidget(b2, "b2");

    one->nextRow();
    QAction *a1 = new QAction(QIcon(":/icons/test.svg"), "&Test", one);
    one->addAction(a1, "a1");
    connect(a1, SIGNAL(triggered()), this, SLOT(action()));

    QAction *a2 = new QAction(QIcon(":/icons/test.svg"), "", one);
    one->addLargeAction(a2, "a2");
    connect(a2, SIGNAL(triggered()), this, SLOT(action()));

    QRibbonSection *two = new QRibbonSection(tab, "Section two", "two");
    QAction *aa = new QAction(QIcon(":/icons/test.svg"), "", two);
    aa->setObjectName("aa");
    connect(aa, SIGNAL(triggered()), this, SLOT(action()));
    two->addLargeAction(aa, "aa");
    QAction *bb = new QAction(QIcon(":/icons/RibbonPoint.svg"), "", two);
    bb->setObjectName("bb");
    connect(bb, SIGNAL(triggered()), this, SLOT(action()));
    two->addLargeAction(bb, "bb");
    QAction *det = new QAction(two);
    two->setDetailsAction(det);

    ribbon->addSection("start", one);
    ribbon->addSection("start", two);

    QWidget *tab2 = new QWidget();
    ribbon->addTab(tab2, "Tab 2", "tab2");
    QRibbonSection *three = new QRibbonSection(tab2, "Section 3", "three");
    QAction *a3 = new QAction(QIcon(":/icons/QRibbonDetails.svg"), "", three);
    connect(a3, SIGNAL(triggered()), this, SLOT(action()));
    QComboBox *cbox = new QComboBox();
    cbox->addItem("hi");
    cbox->addItem("hoi");
    cbox->addItem("jae");
    three->addWidget(cbox, "cbox", 2);
    QAction *a4 = new QAction(QIcon(":/icons/test.svg"), "", three);
    connect(a4, SIGNAL(triggered()), this, SLOT(action()));
    three->nextRow();
    three->addAction(a4, "a4");
    three->addWidget(new QLabel("HI"), "");
    three->addLargeAction(a3, "a3");


    ribbon->addSection("tab2", three);
    connect(ribbon,SIGNAL(currentIndexChanged(int)),this,SLOT(indexChanged(int)));


    setMenuWidget(ribbon);

    setCentralWidget(textEdit);

    //boudingWindow->setWindowFlags(Qt::FramelessWindowHint);
}

QRibbonTest::~QRibbonTest()
{

}

QSize QRibbonTest::minimumSizeHint() const
{
    QSize s = QMainWindow::minimumSizeHint();
    QSize ms = menuWidget()->minimumSizeHint();
    s.setWidth(qMax(s.width(), ms.width()));
    return s;
}

QSize QRibbonTest::sizeHint() const
{
    QSize s = QMainWindow::sizeHint();
    QSize ms = menuWidget()->minimumSizeHint();
    s.setWidth(qMax(s.width(), ms.width()));
    return s;
}

void QRibbonTest::setVisible(bool visible)
{
    QMainWindow::setVisible(visible);
    boundingWindow->setVisible(visible);
}

void QRibbonTest::indexChanged(int tab) {
    printf("current tab = %d\n", tab);
    fflush(stdout);
}

void QRibbonTest::action() {
    QAction *a = (QAction *) sender();
    printf("action = %p\n",a);
    if (a->objectName() == "bb") {
        printf("JE!\n");
        QApplication::closeAllWindows();
    }
    fflush(stdout);
}
