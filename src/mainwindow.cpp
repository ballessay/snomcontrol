#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settingsdialog.h"
#include "webwidget.h"

#include <QDebug>

#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QByteArray>

namespace
{
    const QStringList supportedUirs{QStringList() << "callto:" << "sip:" << "tel:"
                                   // For thunderbird cardbook default
                                   << "undefined:"};
}


CMainWindow::CMainWindow(QWidget* pParent) :
    QMainWindow(pParent),
    m_pUi(new Ui::CMainWindow),
    m_requestHandler(m_settings, this)
{
    m_pUi->setupUi(this);

    connect(m_pUi->actionQuit, &QAction::triggered,
            qApp, &QCoreApplication::quit);

    SetupSystemTray();

    m_settings.Load();

    m_pWebWidget = new CWebWidget(m_settings, this);
    m_pWebWidget->setObjectName(QString::fromUtf8("pWebWidget"));

    m_pUi->pMainGridLayout->addWidget(m_pWebWidget, 1, 0, 1, 1);

    connect(m_pWebWidget, &CWebWidget::ReloadFinished,
            m_pUi->pReloadPushButton, &QPushButton::setEnabled);

    connect(&m_requestHandler, &CRequestHandler::Message,
            this, &CMainWindow::ShowStatusBarMessage);
    connect(&m_requestHandler, &CRequestHandler::Error,
            this, &CMainWindow::ShowStatusBarMessage);

    m_pUi->pReloadPushButton->setIcon(QIcon(":/reload.png"));
    m_pUi->pReloadPushButton->setEnabled(false);
    m_pUi->pDialPushButton->setIcon(QIcon(":/ok.png"));
    m_pUi->pHangUpPushButton->setIcon(QIcon(":/cancel.png"));
}


CMainWindow::~CMainWindow()
{
    delete m_pUi;
}


void CMainWindow::DialWithProgramArg()
{
    QStringList args(qApp->arguments());
    if (args.size() >= 2)
    {
        MessageReceived(0, args.join(";").toUtf8());
    }
}


void CMainWindow::MessageReceived(int, QByteArray message)
{
    QString sMessage(message);
    QStringList args(sMessage.split(";"));

    if (args.size() == 0) return;

    QString sNumber(args.size() == 1 ? args.at(0) : args.at(1));

    for (const QString& uri : supportedUirs)
    {
        if (sNumber.startsWith(uri))
        {
            sNumber.remove(uri);
            break;
        }
    }

    m_pUi->pNumberLineEdit->setText(sNumber);

    Dial(sNumber);
}


void CMainWindow::on_actionSettings_triggered()
{
    CSettingsDialog d(m_settings, this);
    if (CSettingsDialog::Accepted == d.exec())
    {
        m_settings = d.CurrentSettings();
        m_settings.Save();
    }
}


void CMainWindow::on_pReloadPushButton_pressed()
{
    m_pWebWidget->Reload();
}


void CMainWindow::on_pDialPushButton_pressed()
{
    Dial(m_pUi->pNumberLineEdit->text().trimmed());
}


void CMainWindow::on_pHangUpPushButton_pressed()
{
    m_requestHandler.HangUp();

    m_pUi->pNumberLineEdit->clear();
}


void CMainWindow::on_pNumberLineEdit_returnPressed()
{
    Dial(m_pUi->pNumberLineEdit->text());
}


void CMainWindow::ShowStatusBarMessage(const QString &sMessage)
{
    m_pUi->statusBar->showMessage(sMessage, 10000);
}


void CMainWindow::ToggleVisibility()
{
    setVisible(!isVisible());
}


void CMainWindow::TrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
      case QSystemTrayIcon::Trigger:
      case QSystemTrayIcon::DoubleClick:
      case QSystemTrayIcon::MiddleClick:
        ToggleVisibility();
        break;
    default:
        break;
    }
}


void CMainWindow::SetupSystemTray()
{
    QMenu* pMenu = new QMenu(this);

    pMenu->addAction(tr("&Toggle visibility"), this,
                     &CMainWindow::ToggleVisibility, tr("Ctrl+T"));
    pMenu->addSeparator();
    pMenu->addAction(tr("&Quit"), qApp, &QCoreApplication::quit, tr("Ctrl+Q"));

    m_pSysTray = new QSystemTrayIcon(this);

   connect(m_pSysTray, &QSystemTrayIcon::activated,
           this, &CMainWindow::TrayIconActivated);

    m_pSysTray->setContextMenu(pMenu);
    m_pSysTray->setIcon(QIcon(":/snom_logo.png"));
    m_pSysTray->show();
}


void CMainWindow::Dial(QString sNumber)
{
    if (m_settings.bConvertPlus && sNumber.startsWith("+"))
    {
        sNumber.replace("+", "00");
    }

    m_requestHandler.Dial(sNumber);

    m_pWebWidget->Reload();
}

