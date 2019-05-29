#ifndef WEBWIDGET_H
#define WEBWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
    class CWebWidget;
}

struct SSettings;


class CWebWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CWebWidget(const SSettings& settings, QWidget* pParent = nullptr);
    ~CWebWidget() override;

signals:
    void ReloadFinished(bool);

public slots:
    void LoadingFinished(bool);
    void Reload();

protected:
    void showEvent(QShowEvent*) override;

private:
    Ui::CWebWidget* m_pUi;
    QString m_sJquery;
    const SSettings& m_settings;
    bool m_bFirstLoadFinished;
    QPointF m_lastScrollPosition;
};

#endif // WEBWIDGET_H
