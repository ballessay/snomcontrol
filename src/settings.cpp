#include "settings.h"
#include <QSettings>
#include <QTextCodec>
#include <cassert>


namespace
{
    const char* pOranization = "ballessay";
    const char* pApplicationName = "snomcontrol";

    const char* pPhoneUrl = "phoneUrl";
    const char* pSipAccount = "sipAccount";
    const char* pUsername = "username";
    const char* pPassword = "password";
    const char* pConvertPlus = "convertPlus";

    const QByteArray key = "photh7ahWeefohzanahji1IoBood2mei9meiK6aL";
    const char fill = 127;


    QByteArray Obscure(const QString& sText)
    {
        QByteArray text(key.size() - sText.size(), fill);
        text.insert(0, sText);

        assert(text.size() == key.size());
        if (text.size() != key.size()) text.resize(key.size());

        QByteArray obscured;
        for (QString::size_type i = 0; i < text.length(); ++i)
        {
            obscured.append(text.at(i) ^ key.at(i));
        }

        return obscured;
    }


    QString Unobscure(const QByteArray& obscured)
    {
        if (obscured.isEmpty()) return QString();

        assert(obscured.size() == key.size());

        QByteArray text;
        for (QString::size_type i = 0; i < obscured.size(); ++i)
        {
            text.append(obscured.at(i) ^ key.at(i));
        }
        text.replace(fill, '\0');
        return text.simplified();
    }
}


void SSettings::Save()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       pOranization, pApplicationName);
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    settings.setIniCodec(pCodec);

    settings.setValue(pPhoneUrl, sPhoneUrl);
    settings.setValue(pSipAccount, sSipAccount);
    settings.setValue(pUsername, Obscure(sUsername));
    settings.setValue(pPassword, Obscure(sPassword));
    settings.setValue(pConvertPlus, bConvertPlus);
}


void SSettings::Load()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       pOranization, pApplicationName);
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    settings.setIniCodec(pCodec);

    sPhoneUrl = settings.value(pPhoneUrl).toString();
    sSipAccount = settings.value(pSipAccount).toString();
    sUsername = Unobscure(settings.value(pUsername).toByteArray());
    sPassword = Unobscure(settings.value(pPassword).toByteArray());
    bConvertPlus = settings.value(pConvertPlus).toBool();
}

