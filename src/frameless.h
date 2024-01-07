#ifndef ROUNDWINDOW_H
#define ROUNDWINDOW_H

#define SCREEN_WIDTH  900
#define SCREEN_HEIGHT 600
#define FRAME_HEIGHT   40

#include <QtWidgets>
#include "hoverlabel.h"


class FramelessWindow : public QWidget
{
    Q_OBJECT

public:
    FramelessWindow(QWidget *parent = nullptr);
    ~FramelessWindow();

protected:
    void drawFunctionalBtn();
    void drawSidebar();
    void freshButtonPos();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void closeWindow();
    void minimizeWindow();
    void toggleFullscreen();

private:
    QPoint   m_dragStartPosition;
    HoverLabel  *welcomeBtn;
    HoverLabel  *fourteenWorldBtn;
    HoverLabel  *memberListBtn;
    HoverLabel  *aboutBtn;
    QWidget *navBar;
    QPushButton *m_closeButton;
    QPushButton *m_minimizeButton;
    QPushButton *m_fullscreenButton;

};

#endif // ROUNDWINDOW_H
