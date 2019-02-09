#include "mainwindow.h"
#include "singleapplication.h"
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QTimer>



int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv, true);

    app.setOrganizationName("ballessay");
    app.setOrganizationDomain("ballessay.de");
    app.setApplicationName("snomcontrol");

    CMainWindow w;

    if (app.isSecondary()) {
        app.sendMessage(app.arguments().join(';').toUtf8());
        return 0;
    } else {
        if (!QSystemTrayIcon::isSystemTrayAvailable()) {
            QMessageBox::critical(nullptr, QObject::tr("Systray"),
                                  QObject::tr("I couldn't detect any system "
                                              "tray on this system."));
            return 1;
        }
        QApplication::setQuitOnLastWindowClosed(false);

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