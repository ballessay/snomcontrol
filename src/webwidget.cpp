#include "webwidget.h"
#include "ui_webwidget.h"
#include "settings.h"
#include <QFile>
#include <QTimer>


CWebWidget::CWebWidget(const SSettings& settings, QWidget* pParent) :
    QWidget(pParent),
    m_pUi(new Ui::CWebWidget),
    m_settings(settings),
    m_bFirstLoadFinished(false)
{
    m_pUi->setupUi(this);

    QFile file;
    file.setFileName(":/jquery.min.js");
    file.open(QIODevice::ReadOnly);
    m_sJquery = file.readAll();
    m_sJquery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    file.close();

    connect(m_pUi->webEngineView, &QWebEngineView::loadFinished,
            this, &CWebWidget::LoadingFinished);

    QTimer::singleShot(500, this, SLOT(SetUrl()));

    m_pUi->webEngineView->setContextMenuPolicy(Qt::PreventContextMenu);
}


CWebWidget::~CWebWidget()
{
    delete m_pUi;
}


void CWebWidget::SetUrl()
{
    m_pUi->webEngineView->setUrl(QUrl("http://" + m_settings.sUsername + ":" +
                                      m_settings.sPassword + "@" +
                                      m_settings.sPhoneUrl));
}


void CWebWidget::LoadingFinished(bool)
{
    auto page = m_pUi->webEngineView->page();

    page->runJavaScript(m_sJquery);

    // remove unwanted stuff from the settings page
    QString code = QStringLiteral("qt.jQuery('table.flyoutMenu').remove();");
    page->runJavaScript(code);

    code = QStringLiteral("qt.jQuery('table #Table1').remove();");
    page->runJavaScript(code);

    //code = QStringLiteral("qt.jQuery('input.button').remove();");
    code = QStringLiteral("qt.jQuery('input.button[name=\"SETTINGS\"]').remove();");
    page->runJavaScript(code);

    code = QStringLiteral("qt.jQuery('table[dir=\"ltr\"]  > tbody > tr:first-child').remove();");
    page->runJavaScript(code);

    code = QStringLiteral("qt.jQuery('table .bubbleTable').remove();");
    page->runJavaScript(code);

    emit ReloadFinished(true);

    m_bFirstLoadFinished = true;

    page->runJavaScript(QString("window.scrollTo(%1, %2);")
                            .arg(m_lastScrollPosition.x())
                            .arg(m_lastScrollPosition.y()));
}


void CWebWidget::Reload()
{
    if (m_bFirstLoadFinished)
    {
        emit ReloadFinished(false);

        m_lastScrollPosition = m_pUi->webEngineView->page()->scrollPosition();

        m_pUi->webEngineView->reload();
    }
}


void CWebWidget::showEvent(QShowEvent*)
{
    Reload();
}
