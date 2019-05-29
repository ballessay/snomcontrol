#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

struct SSettings;
namespace Ui { class CSettingsDialog; }


class CSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSettingsDialog(const SSettings& settings,
                             QWidget* pParent = nullptr);
    ~CSettingsDialog();

    SSettings CurrentSettings() const;

private slots:
    void ToggleHiddenUi();

private:
    Ui::CSettingsDialog* m_pUi;
};

#endif // SETTINGSDIALOG_H
