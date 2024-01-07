#ifndef HOVERLABEL_H_
#define HOVERLABEL_H_
#include <QLabel>
#include <QEvent>
#include <QString>


class HoverLabel : public QLabel {
public:
    HoverLabel(const QString& text, QWidget* parent = nullptr) : QLabel(text, parent) {}

protected:
    bool event(QEvent* event) override;
};


#endif /* HOVERLABEL_H_ */