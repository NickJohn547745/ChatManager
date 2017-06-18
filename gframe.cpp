#include "gframe.h"

GFrame::GFrame(QWidget *parent)
{
    setParent(parent);

    label = new Label(this);
    errorLabel = new Label(this);
    lineEdit = new QLineEdit(this);

    roboto->setPixelSize(16);
    label->setFont(*roboto);
    lineEdit->setFont(*roboto);

    label->setAttribute(Qt::WA_TransparentForMouseEvents);
    label->setStyleSheet("QLabel {\n  color: rgb(0, 0, 0);\n   background-color: rgba(0, 0, 0, 0);\n}");
    label->setFocus();

    lineEdit->installEventFilter(this);
    lineEdit->setStyleSheet("QLineEdit {\n	border: 0px solid rgb(0, 0, 0);\n	background-color: rgba(0, 0, 0, 0);\n	border-bottom: 2px solid rgb(0, 0, 0);\n	color: rgb(0, 0, 0);\n}");
    //lineEdit->clearFocus();

    errorLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    errorLabel->setStyleSheet("QLabel {\n  color: rgb(0, 0, 0);\n   background-color: rgba(0, 0, 0, 0);\n}");

    updateRect();

    errorLabel->hide();
    label->show();
    lineEdit->show();
}

void GFrame::setHeaderText(QString headerText)
{
    roboto->setPixelSize(16);
    label->setFont(*roboto);
    label->setText(headerText);
    label->move(0, lineEdit->y());
    QFontMetrics fm(*roboto);
    label->resize(fm.width(label->text()), label->height());

    updateRect();
}

void GFrame::setText(QString text)
{
    lineEdit->setText(text);
    lineEdit->move(0, label->height()-15);

    updateRect();
}

void GFrame::resizeEvent(QResizeEvent *e)
{
    int width = e->size().width();
    QFontMetrics fm(*roboto);

    label->raise();
    label->setFocus();
    label->resize(fm.width(label->text()), label->height());
    label->move(0, lineEdit->y());

    lineEdit->resize(width, lineEdit->height());
    lineEdit->move(0, label->height()-15);

    errorLabel->raise();
    errorLabel->resize(fm.width(errorLabel->text()), errorLabel->height());
    errorLabel->move((lineEdit->width()/2)-(errorLabel->width()/2), lineEdit->rect().bottom()+10);

    updateRect();
}

void GFrame::updateRect()
{
    if (errorLabel->isVisible())
    {
        QRect labelRect = label->rect();
        QRect lineEditRect = lineEdit->rect().adjusted(0, 0, 0, 10);
        QRect errorLabelRect = errorLabel->rect();

        setMinimumSize(
                    labelRect.united(errorLabelRect).width(),
                    labelRect.united(lineEditRect.united(errorLabelRect.adjusted(0, 0, 0, errorLabelRect.height()*2))).height());
    }
    else
    {
        QRect labelRect = label->rect();
        QRect lineEditRect = lineEdit->rect().adjusted(0, 0, 0, 10);

        setMinimumSize(
                    labelRect.width(),
                    labelRect.united(lineEditRect).height());
    }
    adjustSize();
}

bool GFrame::eventFilter(QObject *watched, QEvent *event)
{
    QFont pix16 = QFont(roboto->family(), 16);
    QFont pix12 = QFont(roboto->family(), 12);
    if (event->type() == event->FocusIn && watched == lineEdit)//Clicked into lineedit
    {
        lineEdit->setFocus();
        qDebug() << "Focused in  " << objectName();

        QParallelAnimationGroup *group = new QParallelAnimationGroup;

        QPropertyAnimation *posAnimation = new QPropertyAnimation(label, "pos");
        posAnimation->setStartValue(label->pos());
        posAnimation->setEndValue(QPoint(0, 0));
        group->addAnimation(posAnimation);

        QPropertyAnimation *sizeAnimation = new QPropertyAnimation(label, "size");
        sizeAnimation->setStartValue(label->size());
        sizeAnimation->setEndValue(QSize(QFontMetrics(pix12).width(label->text()), QFontMetrics(pix12).height()));
        group->addAnimation(sizeAnimation);

        QPropertyAnimation *fontAnimation = new QPropertyAnimation(label, "fontPixelSize");
        fontAnimation->setStartValue(16);
        fontAnimation->setEndValue(12);
        group->addAnimation(fontAnimation);

        group->start(QAbstractAnimation::DeleteWhenStopped);

        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        updateRect();

        return lineEdit->eventFilter(watched, event);
    }
    else if (event->type() == event->FocusOut && watched == lineEdit && lineEdit->text() == "")//Clicked somewhere else
    {
        lineEdit->clearFocus();
        qDebug() << "Focused out " << objectName();

        QParallelAnimationGroup *group = new QParallelAnimationGroup;

        QPropertyAnimation *posAnimation = new QPropertyAnimation(label, "pos");
        posAnimation->setStartValue(QPoint(0, 0));
        posAnimation->setEndValue(QPoint(5, 5));
        group->addAnimation(posAnimation);

        QPropertyAnimation *sizeAnimation = new QPropertyAnimation(label, "size");
        sizeAnimation->setStartValue(label->size());
        sizeAnimation->setEndValue(QSize(QFontMetrics(pix16).width(label->text()), QFontMetrics(pix16).height()));
        group->addAnimation(sizeAnimation);

        QPropertyAnimation *fontAnimation = new QPropertyAnimation(label, "fontPixelSize");
        fontAnimation->setStartValue(12);
        fontAnimation->setEndValue(16);
        group->addAnimation(fontAnimation);

        group->start(QAbstractAnimation::DeleteWhenStopped);

        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        updateRect();

        return lineEdit->eventFilter(watched, event);
    }
    else if (event->type() == event->Resize)
    {
        QResizeEvent *e = static_cast<QResizeEvent*>(event);
        resizeEvent(e);
    }
    return lineEdit->eventFilter(watched, event);
}

void GFrame::setPasswordMode(bool isPassword)
{
    if (isPassword)
        lineEdit->setEchoMode(QLineEdit::Password);
    else
        lineEdit->setEchoMode(QLineEdit::Normal);
}

void GFrame::showError(QString error)
{
    errorLabel->move(lineEdit->width()/3, 0);
    errorLabel->setText(error);
    errorLabel->show();

    updateRect();
}

void GFrame::clearError()
{
    errorLabel->clear();
    errorLabel->hide();

    updateRect();
}

void GFrame::setColor(QColor color)
{
    QString rgb = "rgb(" +
            QString::number(color.red()) + ", " +
            QString::number(color.green()) + ", " +
            QString::number(color.blue()) + ")";

    label->setStyleSheet("QLabel {\n  color: " + rgb + ";\n   background-color: rgba(0, 0, 0, 0);\n}");
    lineEdit->setStyleSheet("QLineEdit {\n	border: 0px solid " + rgb + ";\n	background: rgba(0, 0, 0, 0);\n	border-bottom: 2px solid " + rgb + ";\n	color: " + rgb + ";\n}");
    errorLabel->setStyleSheet("QLabel {\n  color: " + rgb + ";\n   background-color: rgba(0, 0, 0, 0);\n}");

}
