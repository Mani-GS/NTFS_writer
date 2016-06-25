#include "mainwindow.h"
#include "manager.h"
#include <QApplication>
#include <QMessageBox>

#include <QTranslator>
#include "fervor/fvupdater.h"

int main(int argc, char *argv[]) {
    QApplication::setApplicationName("NTFS_Writer");
    QApplication::setApplicationVersion("1.2");
    QApplication::setOrganizationName("Mani");
    QApplication::setOrganizationDomain("Mani.it");
    
    QApplication a(argc, argv);
    MainWindow w;
    
    if(strcmp(argv[0], "/Applications/NTFS_Writer.app/Contents/MacOS/NTFS_Writer") != 0){
        QMessageBox::warning(NULL, "Error", "This app must be inside Applications folder.");
        return -1;
    }
    
    FvUpdater::sharedUpdater()->SetFeedURL("https://raw.github.com/Mani-GS/NTFS_writer/gh-pages/Appcast.xml");
    FvUpdater::sharedUpdater()->CheckForUpdates();
    
    w.show();
    
    QTranslator translator, fTranslator;
    QString language = QLocale::system().name();

    if(language == "it_IT"){
        translator.load(":/translations/NTFS_Writer_it");
        fTranslator.load(":/translations/fervor_it");
        a.installTranslator(&translator);
        a.installTranslator(&fTranslator);
    }

    Manager* manag = new Manager(&w);
    manag->main();

    return a.exec();
}
