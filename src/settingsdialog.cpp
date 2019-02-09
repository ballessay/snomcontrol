#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settings.h"
#include <QShortcut>
#include <QKeySequence>



CSettingsDialog::CSettingsDialog(const SSettings& settings, QWidget* pParent) :
    QDialog(pParent),
    m_pUi(new Ui::CSettingsDialog)
{
    m_pUi->setupUi(this);

    m_pUi->pAccountGroupBox->hide();

    m_pUi->pPhoneUrlLineEdit->setText(settings.sPhoneUrl);
    m_pUi->pSipAccountLineEdit->setText(settings.sSipAccount);

    m_pUi->pUsernameLineEdit->setText(settings.sUsername);
    m_pUi->pPasswordLineEdit->setText(settings.sPassword);

    m_pUi->pConvertPlusCheckBox->setChecked(settings.bConvertPlus);

    QShortcut* pSc = new QShortcut(QKeySequence(tr("Ctrl+Alt+H", "Show Hidden")), this);

    connect(pSc, &QShortcut::activated, this, &CSettingsDialog::ToggleHiddenUi);
}


CSettingsDialog::~CSettingsDialog()
{
    delete m_pUi;
}


SSettings CSettingsDialog::CurrentSettings() const
{
    SSettings settings;

    settings.sPhoneUrl = m_pUi->pPhoneUrlLineEdit->text();
    settings.sSipAccount = m_pUi->pSipAccountLineEdit->text();
    settings.sUsername = m_pUi->pUsernameLineEdit->text();
    settings.sPassword = m_pUi->pPasswordLineEdit->text();
    settings.bConvertPlus = m_pUi->pConvertPlusCheckBox->isChecked();

    return settings;
}


void CSettingsDialog::ToggleHiddenUi()
{
    m_pUi->pAccountGroupBox->setVisible(!m_pUi->pAccountGroupBox->isVisible());
}
