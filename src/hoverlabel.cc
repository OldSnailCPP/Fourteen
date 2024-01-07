#include "hoverlabel.h"

bool HoverLabel::event(QEvent* event) {
    if (event->type() == QEvent::Enter) {
        setStyleSheet("background-color: #EAEAEA;");
        return true;
    } else if (event->type() == QEvent::Leave) {
        setStyleSheet("background-color: #EFEFEF;");
        return true;
    }
    return QLabel::event(event);
}
