#ifndef LABEL_H
#define LABEL_H

#include <QLabel>

class Label: public QLabel {
    Q_OBJECT
    Q_PROPERTY (double fontPixelSize READ fontPixelSize WRITE setFontPixelSize)

public:
    Label(QWidget* parent = 0): QLabel(parent)
    {

    }
    double fontPixelSize() const
    {
        return font().pixelSize();
    }
    Q_SLOT void setFontPixelSize(int size)
    {
        QFont f = font();
        f.setPixelSize(size);
        setFont(f);
    }
};

#endif // LABEL_H
