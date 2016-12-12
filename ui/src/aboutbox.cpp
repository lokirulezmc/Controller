#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>

#include "qlcconfig.h"
#include "aboutbox.h"

AboutBox::AboutBox(QWidget* parent) : QDialog (parent)
{
    setupUi(this);

    QAction* action = new QAction(this);
    action->setShortcut(QKeySequence(QKeySequence::Close));
    connect(action, SIGNAL(triggered(bool)), this, SLOT(reject()));
    addAction(action);

    m_titleLabel->setText(APPNAME);
    m_versionLabel->setText(APPVERSION);
    m_copyrightLabel->setText(QString("Copyright &copy; <B>Chris Mowers</B> %1")
                              .arg(tr("and contributors:")));
    m_websiteLabel->setText(tr("Website: %1").arg("<A HREF=\"#"));
    connect(m_websiteLabel, SIGNAL(linkActivated(QString)),
            this, SLOT(slotWebsiteClicked()));

    connect(m_contributors, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(slotItemClicked()));
    m_contributors->clear();
    m_contributors->addItem("Contributors:");
    m_contributors->addItem("Chris Mowers");;

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
    m_row = -1;
    m_increment = 1;
    m_timer->start(500);
}

AboutBox::~AboutBox()
{
}

void AboutBox::slotTimeout()
{
    if (m_row <= 0)
        m_increment = 1;
    else if (m_row >= m_contributors->count())
        m_increment = -1;

    m_row += m_increment;
    m_contributors->scrollToItem(m_contributors->item(m_row));
}

void AboutBox::slotItemClicked()
{
    if (m_timer != NULL)
    {
        m_timer->stop();
        delete m_timer;
        m_timer = NULL;
    }
}

void AboutBox::slotWebsiteClicked()
{
    QDesktopServices::openUrl(QUrl("#"));
}
