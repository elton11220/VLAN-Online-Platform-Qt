#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    qputenv("QT_ENABLE_HIGHDPI_SCALING", "1");//高DPI适配
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);//高DPI适配
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);//Retina屏 适配
    QApplication a(argc, argv);
    QApplication::processEvents(); //防止线程阻塞
    MainWindow w;
    QDir* dir = new QDir();
    if(!dir->exists(QDir::currentPath() + "\\data")){
        QMessageBox::warning(&w,"错误","程序数据遭到破坏\n请重新安装");
        return 0;
    }
    if(!dir->exists(QDir::currentPath() + "\\data\\log")){
        QDir dir;
        dir.mkdir(QDir::currentPath() + "\\data\\log");
    }
#if defined (Q_OS_WIN32)
    if(!dir->exists(QDir::currentPath() + "\\data\\config.ini") || !dir->exists(QDir::currentPath() + "\\data\\lan-play-win32.exe") || !dir->exists(QDir::currentPath() + "\\data\\lan-play-win64.exe") || !dir->exists(QDir::currentPath() + "\\data\\winpcap413.exe")){
        QMessageBox::warning(&w,"错误","程序数据遭到破坏\n请重新安装");
        return 0;
    }
#elif defined(Q_OS_MACOS)

#elif defined(Q_OS_LINUX)

#endif
    w.show();
    return a.exec();
}
