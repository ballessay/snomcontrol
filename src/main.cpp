#include "mainwindow.h"
#include <QApplication>
#include "singleapplication.h"
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QTimer>
#include <QFile>
#include <QTextStream>



int main(int argc, char *argv[])
{
    SingleApplication::Options options = SingleApplication::User |
                                         SingleApplication::ExcludeAppPath;
    SingleApplication app(argc, argv, true, options);

    app.setOrganizationName("ballessay");
    app.setOrganizationDomain("ballessay.de");
    app.setApplicationName("snomcontrol");

    QFile stylesheet( ":/QTDark.stylesheet");
    if (stylesheet.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream ts(&stylesheet);
        app.setStyleSheet(ts.readAll());
    }

    CMainWindow w;

    if (app.isSecondary()) {
        app.sendMessage(app.arguments().join(';').toUtf8());
        return 0;
    } else {
        if (!QSystemTrayIcon::isSystemTrayAvailable()) {
            w.DisableHideMenuEntry();
        }
        else
        {
            w.SetupSystemTray();

            QApplication::setQuitOnLastWindowClosed(false);
        }

        QObject::connect(&app, &SingleApplication::receivedMessage,
                         &w, &CMainWindow::MessageReceived);

        if (argc >= 2)
        {
            QByteArray data(argv[1]);
            QTimer::singleShot(1000, &w, &CMainWindow::DialWithProgramArg);
        }

        w.show();
    }

    return app.exec();
}
