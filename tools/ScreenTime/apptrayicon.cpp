#include "apptrayicon.h"
#include <QProcess>
#include <QDebug>
AppTrayIcon::AppTrayIcon(QMainWindow *parent)
    : QSystemTrayIcon(parent)
{
    _parent = parent;
    setIcon(QIcon(":/img/Assets/32.ico"));
    setToolTip("屏幕使用时间");
    connect(this, &QSystemTrayIcon::activated, this, &AppTrayIcon::on_trayIcon_activated);

    _menu = new QMenu();
    QAction *actionOpenAppDir = new QAction("打开安装目录");
    connect(actionOpenAppDir, &QAction::triggered, this, &AppTrayIcon::on_actionOpenAppDir_triggered);
    _menu->addAction(actionOpenAppDir);
    QAction *actionShowWindow = new QAction("显示窗口");
    connect(actionShowWindow, &QAction::triggered, this, &AppTrayIcon::ShowParent);
    _menu->addAction(actionShowWindow);
    QAction *actionExitApp = new QAction("退出程序");
    connect(actionExitApp, &QAction::triggered, this, &QApplication::quit);
    _menu->addAction(actionExitApp);
    setContextMenu(_menu);
    show();
}

AppTrayIcon::~AppTrayIcon()
{}

void AppTrayIcon::on_actionOpenAppDir_triggered()
{
    QString exeDir = QCoreApplication::applicationDirPath();
    exeDir.replace("/", "\\");
    QProcess::startDetached("explorer", QStringList() << exeDir);
}

void AppTrayIcon::on_trayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
    qDebug() << "8";
    switch(reason)
    {
    case QSystemTrayIcon::MiddleClick:
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        if (_parent->isVisible())
        {
            HideParent();
        }
        else
        {
            ShowParent();
        }
        qDebug() << "14";
        break;
    case QSystemTrayIcon::Context:
        QPoint pos = QCursor::pos();
        int offsetY = -_menu->sizeHint().height();
        _menu->popup(QPoint(pos.x(), pos.y() + offsetY));
        qDebug() << "15";
        break;
    }
    qDebug() << "9";
}

void AppTrayIcon::ShowParent()
{
    qDebug() << "10";
    _parent->show();
    _parent->activateWindow();
    qDebug() << "11";
}
void AppTrayIcon::HideParent()
{
    qDebug() << "12";
    _parent->hide();
    qDebug() << "13";
}
