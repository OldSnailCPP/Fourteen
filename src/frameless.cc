#include "frameless.h"

FramelessWindow::FramelessWindow(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground);
    this->drawFunctionalBtn();
    this->drawSidebar();
}

FramelessWindow::~FramelessWindow() {
    delete welcomeBtn;
    delete fourteenWorldBtn;
    delete memberListBtn;
    delete aboutBtn;
    delete navBar;
    delete m_closeButton;
    delete m_minimizeButton;
    delete m_fullscreenButton;
}

void FramelessWindow::drawFunctionalBtn() {
    // 添加关闭按钮
    m_closeButton = new QPushButton(this);
    m_closeButton->setFixedSize(20, 20);
    resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    m_closeButton->move(width() - 30, 10);
    connect(m_closeButton, &QPushButton::clicked, this, &FramelessWindow::closeWindow);

    // 设置关闭按钮的样式
    m_closeButton->setStyleSheet("QPushButton {"
                                    "background-color: #2aca42;"  // 设置背景颜色
                                    "border-radius: 10px;"          // 设置边框圆角半径为10像素
                                    "color: #FFFFFF;"               // 设置文本颜色为白色
                                    "}");

    // 添加全屏按钮
    m_fullscreenButton = new QPushButton(this);
    m_fullscreenButton->setFixedSize(20, 20);
    resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    m_fullscreenButton->move(width() - 60, 10);
    connect(m_fullscreenButton, &QPushButton::clicked, this, &FramelessWindow::toggleFullscreen);

    // 设置全屏按钮的样式
    m_fullscreenButton->setStyleSheet("QPushButton {"
                                      "background-color: #ffbf2e;"  // 设置背景颜色为蓝色
                                      "border-radius: 10px;"
                                      "color: #FFFFFF;"
                                      "}");

    // 添加最小化按钮
    m_minimizeButton = new QPushButton(this);
    m_minimizeButton->setFixedSize(20, 20);
    resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    m_minimizeButton->move(width() - 90, 10);
    connect(m_minimizeButton, &QPushButton::clicked, this, &FramelessWindow::minimizeWindow);
    
    // 设置最小化按钮的样式
    m_minimizeButton->setStyleSheet("QPushButton {"
                                    "background-color: #ff6258;"  // 设置背景颜色
                                    "border-radius: 10px;"          // 设置边框圆角半径为10像素
                                    "color: #FFFFFF;"               // 设置文本颜色为白色
                                    "}");
    resize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void FramelessWindow::drawSidebar() {
    // 创建导航栏
    int navBarWidth = SCREEN_WIDTH / 6;
    int navBarHeight =  SCREEN_HEIGHT - 20;
    navBar = new QWidget(this);
    navBar->setGeometry(10, 10 + FRAME_HEIGHT, navBarWidth, navBarHeight - FRAME_HEIGHT);
    navBar->setStyleSheet("background-color: rgba(255, 255, 255, 255); border-radius: 10px;"); // 设置背景颜色和圆角

    // 创建按钮
    welcomeBtn       = new HoverLabel("A Welcome Page", navBar);
    fourteenWorldBtn = new HoverLabel("Fourteen World", navBar);
    memberListBtn    = new HoverLabel("All Member List", navBar);
    aboutBtn         = new HoverLabel("About", navBar);

    //设定位置
    int btn_h = navBarHeight / 8;
    welcomeBtn->setGeometry(0, 0, navBarWidth, btn_h);
    fourteenWorldBtn->setGeometry(0, btn_h + 2, navBarWidth, btn_h);
    memberListBtn->setGeometry(0, btn_h * 2 + 4, navBarWidth, btn_h);
    aboutBtn->setGeometry(0, btn_h * 3 + 6, navBarWidth, btn_h);

    QFont font("Jetbrains Mono", 12); // 设置 Jetbrains Mono 字体和字号
    welcomeBtn->setFont(font);
    fourteenWorldBtn->setFont(font);
    memberListBtn->setFont(font);
    aboutBtn->setFont(font);

    welcomeBtn->setAlignment(Qt::AlignCenter);
    fourteenWorldBtn->setAlignment(Qt::AlignCenter);
    memberListBtn->setAlignment(Qt::AlignCenter);
    aboutBtn->setAlignment(Qt::AlignCenter);

    // 设置按钮背景色
    welcomeBtn->setStyleSheet("background-color: #EFEFEF;");
    fourteenWorldBtn->setStyleSheet("background-color: #EFEFEF;");
    memberListBtn->setStyleSheet("background-color: #EFEFEF;");
    aboutBtn->setStyleSheet("background-color: #EFEFEF;");
}

void FramelessWindow::freshButtonPos() {
    m_minimizeButton->move(width() - 90, 10);
    m_fullscreenButton->move(width() - 60, 10);
    m_closeButton->move(width() - 30, 10);
}

void FramelessWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10);

    painter.setClipPath(path);
    painter.fillRect(rect(), QColor(255, 255, 255, 250));

    // 绘制文本
    // QFontDatabase::addApplicationFont(":/fonts/FZMWFont.ttf");  // 注册字体
    // QFont font("方正喵呜体");
    // font.setPointSize(24);
    // setStyleSheet(QString("font-family:%1;").arg(font.family()));
    // QFont font("Jetbrains Mono", 18); // 设置 Jetbrains Mono 字体和字号
    // painter.setFont(font);
    // QString text = "Hi~";
    // QSize textSize = painter.fontMetrics().size(Qt::TextSingleLine, text);
    // painter.setPen(Qt::blue);  // 设置文本颜色
    // painter.drawText((0, textSize.height()), Qt::AlignTop | Qt::AlignHCenter, text);

    QWidget::paintEvent(event);
}

void FramelessWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragStartPosition = event->pos();
    }
    QWidget::mousePressEvent(event);
}

void FramelessWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint diff = event->pos() - m_dragStartPosition;
        QPoint newpos = this->pos() + diff;
        this->move(newpos);
    }
    QWidget::mouseMoveEvent(event);
}

void FramelessWindow::closeWindow()
{
    this->close();
}

void FramelessWindow::minimizeWindow()
{
    setWindowState(Qt::WindowMinimized);
    this->freshButtonPos();
}

void FramelessWindow::toggleFullscreen()
{
    if (windowState() & Qt::WindowFullScreen)
        setWindowState(windowState() & ~Qt::WindowFullScreen);
    else
        setWindowState(windowState() | Qt::WindowFullScreen);
    this->freshButtonPos();
}
