#include "qribbonbutton.h"
#include "qribbonsection.h"

#include <QVBoxLayout>
#include <QGridLayout>

QRibbonSection::QRibbonSection(QWidget *parent, const QString &_title, const QString &_name) : QWidget(parent)
{
    action = Q_NULLPTR;
    col = 0;
    row = 0;
    colBase = 0;
    _index = -1;

    if (&_name != Q_NULLPTR) {
        this->setObjectName(_name);
    }

    QHBoxLayout *slayout = new QHBoxLayout();
    slayout->setContentsMargins(2,0,2,0);
    slayout->setSpacing(2);
    this->setLayout(slayout);

    //QLabel *lab_line = new QLabel("X", this);
    QFrame *line = new QFrame(this);
    line->setFrameStyle(QFrame::VLine | QFrame::Plain);
    line->setFixedWidth(3);
    line->setContentsMargins(0,3,0,5);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QString sheet = line->styleSheet();
    sheet.append("QFrame { color: #c0c0c0; }");
    line->setStyleSheet(sheet);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    buttons = new QWidget(this);
    QGridLayout *blayout = new QGridLayout();
    blayout->setContentsMargins(0,2,0,2);
    blayout->setSpacing(2);
    buttons->setLayout(blayout);

    QHBoxLayout *lfooter = new QHBoxLayout();
    lfooter->setContentsMargins(0,0,0,0);

    if (&title == Q_NULLPTR) {
        title = new QLabel("", this);
    } else {
        title = new QLabel(_title, this);
    }
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(titleFont.pointSize()*0.98f);
    title->setFont(titleFont);

    details = new QRibbonButton(QIcon(":/icons/QRibbonDetails.svg"), "", this);
    details->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QFont f;
    QFontMetrics metrics(f);
    QSize is = QSize(metrics.boundingRect("^").width(), metrics.boundingRect("X").height());
    is = QSize(is.width()*2, is.height());
    details->setIconSize(is);
    details->setMaximumSize(is);
    details->setVisible(false);
    QObject::connect(details, SIGNAL(clicked()), this, SLOT(activateDetails()));


    lfooter->addWidget(title, 1);
    lfooter->addWidget(details);

    layout->addWidget(buttons, 1);
    layout->addLayout(lfooter);

    slayout->addLayout(layout, 1);
    slayout->addWidget(line, 1);
}

QRibbonSection::~QRibbonSection()
{
}

void QRibbonSection::setDetailsAction(QAction *_action)
{
    action = _action;
    details->setVisible(action != Q_NULLPTR);
}

void QRibbonSection::activateDetails()
{
    if (action) {
        action->trigger();
    }
}

QWidget *QRibbonSection::widget(int index)
{
    return _widgets.value(index, Q_NULLPTR);
}

int QRibbonSection::count()
{
    return _widgets.size();
}

int QRibbonSection::currentIndex()
{
    return _index;
}

void QRibbonSection::setCurrentIndex(int i)
{
    if (i >= 0 && i < _widgets.size()) {
        _index = i;
    }
}

void QRibbonSection::addAction(QAction *a, const QString &name)
{
    QGridLayout *l = qobject_cast<QGridLayout *>(buttons->layout());
    QRibbonButton *btn = new QRibbonButton(a->icon(), a->text(), name, buttons);
    btn->setDefaultAction(a);
    if (a->text().size() > 0) {
        btn->setText(a->text());
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    }
    l->addWidget(btn, row, col, 1, 1);
    col += 1;
    _widgets.append(btn);
}

void QRibbonSection::addLargeAction(QAction *a, const QString &name)
{
    QGridLayout *l = qobject_cast<QGridLayout *>(buttons->layout());
    QRibbonButton *btn = new QRibbonButton(a->icon(), a->text(), name, buttons);
    btn->setDefaultAction(a);
    nextColumn();
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn->setIconSize(QSize(btn->iconSize().width() * 2, btn->iconSize().height() * 2));
    if (a->text().size() > 0) {
        btn->setText(a->text());
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
    l->addWidget(btn, row, col, 2, 2);
    col += 2;
    _widgets.append(btn);
}

void QRibbonSection::addWidget(QWidget *w, const QString &name, int colspan)
{
    QGridLayout *l = qobject_cast<QGridLayout *>(buttons->layout());
    if (&name != Q_NULLPTR) {
        w->setObjectName(name);
    }
    l->addWidget(w, row, col, 1, colspan);
    col += colspan;
    _widgets.append(w);
}

void QRibbonSection::addLargeWidget(QWidget *w, const QString &name)
{
    QGridLayout *l = qobject_cast<QGridLayout *>(buttons->layout());
    if (&name != Q_NULLPTR) {
        w->setObjectName(name);
    }
    nextColumn();
    l->addWidget(w, row, col, 2, 2);
    col += 2;
    _widgets.append(w);
}

void QRibbonSection::addSeparator()
{
    QGridLayout *l = qobject_cast<QGridLayout *>(buttons->layout());
    QFrame *line = new QFrame(this);
    line->setFrameStyle(QFrame::VLine | QFrame::Plain);
    line->setFixedWidth(3);
    line->setContentsMargins(0,3,0,5);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QString sheet = line->styleSheet();
    sheet.append("QFrame { color: #c0c0c0; }");
    line->setStyleSheet(sheet);
    l->addWidget(line, 0, l->columnCount(), l->rowCount(), 1);
    nextColumn();
}

void QRibbonSection::nextColumn()
{
    QGridLayout *l = qobject_cast<QGridLayout *>(buttons->layout());
    colBase = l->columnCount();
    col = colBase;
    row = 0;
}

void QRibbonSection::nextRow()
{
    row += 1;
    col = colBase;
}

void QRibbonSection::setTitle(const QString &_title)
{
    title->setText(_title);
}

