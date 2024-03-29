#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settings.h"
#include "requesthandler.h"
#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
    class CMainWindow;
}

class CWebWidget;


class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget* pParent = nullptr);
    ~CMainWindow();

    void DisableHideMenuEntry();

    void SetupSystemTray();

public slots:
    void DialWithProgramArg();
    // SingleApplication
    void MessageReceived(int instanceId, QByteArray message);

    // Window
    void on_actionInit_triggered();
    void on_actionSettings_triggered();
    void on_pReloadPushButton_pressed();
    void on_pDialPushButton_pressed();
    void on_pHangUpPushButton_pressed();
    void on_pNumberLineEdit_returnPressed();
    void ShowStatusBarMessage(const QString& sMessage);

    // TrayIcon
    void ToggleVisibility();
    void TrayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    void Dial(QString sNumber);

private:
    Ui::CMainWindow* m_pUi;
    QSystemTrayIcon* m_pSysTray;
    CWebWidget* m_pWebWidget;
    SSettings m_settings;
    CRequestHandler m_requestHandler;
};

#endif // MAINWINDOW_H
