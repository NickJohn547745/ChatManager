#ifndef GFrame_H
#define GFrame_H

#include <QLineEdit>
#include <QFrame>
#include "label.h"
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QDebug>

class GFrame : public QFrame
{
public:
    GFrame(QWidget *parent);

    bool eventFilter(QObject *watched, QEvent *event);
    void resizeEvent(QResizeEvent *e);

    void updateRect();
    void setHeaderText(QString headerText);
    void setText(QString text);
    void setPasswordMode(bool isPassword);
    void showError(QString error);
    void clearError();
    void setColor(QColor color);

private:
    Label *label;
    Label *errorLabel;
    QLineEdit *lineEdit;
    QFont* roboto = new QFont("Roboto Condensed Light");
};

#endif // GFrame_H
