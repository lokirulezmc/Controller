
#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QDialog>
#include "ui_aboutbox.h"

class QTimer;

/** @addtogroup ui UI
 * @{
 */

class AboutBox : public QDialog, public Ui_AboutBox
{
    Q_OBJECT
    Q_DISABLE_COPY(AboutBox)

public:
    AboutBox(QWidget* parent);
    ~AboutBox();

private slots:
    void slotTimeout();
    void slotItemClicked();
    void slotWebsiteClicked();

private:
    QTimer* m_timer;
    int m_row;
    int m_increment;
};

/** @} */

#endif
