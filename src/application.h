#ifndef APPLICATION_H
#define APPLICATION_H

#include "core/utils.h"
#include "components/errormessage.h"
#include "upgradedialog.h"
#include "aboutdialog.h"
#include "configdialog.h"
#include "historywindow.h"
#include "uploaddialog.h"
#include "core/tagservice.h"
#include "core/serverservice.h"
#include "core/settingservice.h"
#include "core/formatservice.h"
#include "core/clipservice.h"
#include "core/uploadservice.h"

#include <QtGlobal>
#include <QApplication>
#include <QIcon>
#include <QSystemTrayIcon>
#include <QSqlDatabase>

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char **argv);
    ~Application() override;

    int showUpgradeWindow();
    void createTrayIcon();
    void showAboutDialog();
    void showConfigDialog();
    void showHistoryWindow();
    void showUploadDialog();
    bool prepare(const QString& dbPath);
    void sendNotification(const QString &message, const QString &title="fu", QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information, int timeout = 10000);

    const QString &getDbPath();

    TagService *tagService() {return _tagService; }
    ServerService *serverService() { return _serverService; }
    SettingService *settingService() {return _settingService; }
    FormatService *formatService() { return _formatService; }
    ClipService *clipService() { return _clipService; }
    UploadService *uploadService() { return _uploadService; }


private:
    template <typename T>
    void showWindowOrDialog(T **widget);
    QSystemTrayIcon *_trayIcon;
    QIcon _windowIcon;
    QIcon _uploadingIcon;
    bool _isUploadingIcon = false;
    QString _dbPath;
    QSqlDatabase _sqlDb;
    TagService *_tagService = nullptr;
    ServerService *_serverService = nullptr;
    SettingService *_settingService = nullptr;
    FormatService *_formatService = nullptr;
    ClipService *_clipService = nullptr;
    UploadService *_uploadService = nullptr;

    UpgradeDialog *upgradeDialog = nullptr;
    AboutDialog *aboutDialog = nullptr;
    ConfigDialog *configDialog = nullptr;
    HistoryWindow *historyWindow = nullptr;
    UploadDialog *uploadDialog = nullptr;

public slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason);
};

#define APP (qobject_cast<Application*>qApp)


#endif // APPLICATION_H


