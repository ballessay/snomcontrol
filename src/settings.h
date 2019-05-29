#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QStringList>


struct SSettings
{
    void Save();
    void Load();

    QString sPhoneUrl;  ///< DNS of IP of the phone

    QString sSipAccount;        ///< Accountname in the form: id@provider.com

    QString sUsername;  ///< Phone username
    QString sPassword;  ///< Phone password

    bool bConvertPlus; ///< Convert + sign of international area codes
};

#endif // SETTINGS_H
