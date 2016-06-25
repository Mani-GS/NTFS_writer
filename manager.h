#ifndef MANAGER_H
#define MANAGER_H

#include "mainwindow.h"
#include "droparea.h"
#include "aboutdialog.h"
#include <QtWidgets>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QGroupBox>
#include <QScrollArea>
#include <QComboBox>
#include <QProgressBar>
#include <string>
#include <pwd.h>
#include <dirent.h>
#include <vector>


using namespace std;

class Manager : public QObject{
    Q_OBJECT

public:
    Manager(MainWindow* w);
    void updateList();
    void main();

public slots:
    void openVolumes();
    void linkVolumes();
    void addFile(QList<QUrl> urlList);
    void findDevices();
    void copyFiles();
    void clear();
    void checkInstallation();
    void uninstall();
    void openAbout();

private:
    QString getName(QString path, int type);
    void createMsgBox(QMessageBox* msgBox, bool file, QString name);
    bool isApp(QString file);

    MainWindow* w;
    QPushButton *btnOpenVol, *btnSearchDevices, *btnCopy, *btnClear;
    DropArea *dropArea;
    QGroupBox *grpDropArea;
    QComboBox* cmbDestination;
    QProgressBar* prgBar;
    QLabel* lblStatus;
    QAction* checkDaemon, *uninstallDaemon, *openVol, *linkVol, *about;
    vector<QString> files;
    AboutDialog *aboutApp;
};

#endif // MANAGER_H
