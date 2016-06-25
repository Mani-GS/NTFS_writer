#include "manager.h"

using namespace std;

Manager::Manager(MainWindow* w){
    this->w = w;

    dropArea = new DropArea();
    grpDropArea = w->findChild<QGroupBox*>("grpDropArea");
    btnOpenVol = w->findChild<QPushButton*>("btnOpenVol");
    btnSearchDevices = w->findChild<QPushButton*>("btnSearchDevices");
    btnCopy = w->findChild<QPushButton*>("btnCopy");
    btnClear = w->findChild<QPushButton*>("btnClear");
    cmbDestination = w->findChild<QComboBox*>("cmbDestination");
    checkDaemon = w->findChild<QAction*>("actionCheckDaemon");
    uninstallDaemon = w->findChild<QAction*>("actionUninstallDaemon");
    openVol = w->findChild<QAction*>("actionOpenVolumes");
    linkVol = w->findChild<QAction*>("actionLinkVolumes");
    about = w->findChild<QAction*>("actionAbout");
    prgBar = new QProgressBar();
    lblStatus = new QLabel();

    aboutApp = new AboutDialog();

    lblStatus->setText("Ready");

    QStatusBar* status = w->findChild<QStatusBar*>("statusBar");

    status->addPermanentWidget(lblStatus);
    status->addPermanentWidget(prgBar);

    QScrollArea *lay = w->findChild<QScrollArea*>("scrollArea");
    lay->setWidget(dropArea);

    connect(btnCopy, SIGNAL(released()), this, SLOT(copyFiles()));
    connect(btnOpenVol, SIGNAL(released()), this, SLOT(openVolumes()));
    connect(btnSearchDevices, SIGNAL(released()), this, SLOT(findDevices()));
    connect(btnClear, SIGNAL(released()), this, SLOT(clear()));
    connect(dropArea, SIGNAL(dropped(QList<QUrl>)), this, SLOT(addFile(QList<QUrl>)));
    connect(openVol, SIGNAL(triggered()), this, SLOT(openVolumes()));
    connect(checkDaemon, SIGNAL(triggered()), this, SLOT(checkInstallation()));
    connect(linkVol, SIGNAL(triggered()), this, SLOT(linkVolumes()));
    connect(uninstallDaemon, SIGNAL(triggered()), this, SLOT(uninstall()));
    connect(about, SIGNAL(triggered()), this, SLOT(openAbout()));
}

void Manager::main(){
    findDevices();
    checkInstallation();
}

void Manager::checkInstallation(){
    if(system("cd /Library/LaunchAgents && ls | grep com.ntfs_writer.plist")){
        QMessageBox::warning(NULL, tr("Warning"), tr("The daemon isn't installed, this app needs it installed to run properly.\nInstalling the daemon now."));

        struct passwd *pw = getpwuid(getuid());
        QString installStr = "osascript /Applications/NTFS_Writer.app/Contents/scripts/install.scpt $1";
        installStr.replace("$1", pw->pw_dir);

        string install = installStr.toUtf8().constData();

        if(!system(install.c_str())){
            QMessageBox::information(NULL, tr("Success"), tr("Daemon installed correctly."));
        }
    }
}

void Manager::uninstall(){
    QMessageBox msg;
    msg.setWindowTitle(tr("Warning"));
    msg.setText(tr("If you uninstall the daemon, this app won't work properly."));
    msg.setInformativeText(tr("Are you sure?"));
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    msg.button(QMessageBox::Yes)->setText(tr("Yes"));
    msg.button(QMessageBox::No)->setText(tr("No"));
    msg.setIconPixmap(QPixmap (":/images/stop.png"));

    int ret = msg.exec();

    if(ret == QMessageBox::Yes){
        struct passwd *pw = getpwuid(getuid());
        QString uninstallStr = "osascript /Applications/NTFS_Writer.app/Contents/scripts/uninstall.scpt $1";
        uninstallStr.replace("$1", pw->pw_dir);

        string uninstall = uninstallStr.toUtf8().constData();

        system(uninstall.c_str());
        QMessageBox::information(NULL, tr("Uninstalled"), tr("Daemon uninstalled."));
    }
}

void Manager::copyFiles(){
    QString sel = cmbDestination->itemText(cmbDestination->currentIndex());
    if(sel == ""){
        QMessageBox::warning(NULL, tr("Warning"), tr("No device selected"));
        return;
    }

    if(files.size() == 0){
        QMessageBox::warning(NULL, tr("Warning"), tr("No files selected"));
        return;
    }

    lblStatus->setText(tr("Copying elements..."));
    prgBar->setMaximum(files.size());
    prgBar->setValue(0);

    QString baseDest = "/Volumes/" + sel;
    QString dest;
    QString cpStr;
    QString dirStr;
    QString currentFile;
    QString filename;
    string dir;
    string cp;
    baseDest.replace(" ", "\\ ");

    bool copy, copyF, copyD, copyF_all, copyD_all;

    copyF_all = false;
    copyD_all = false;

    copyF = true;
    copyD = true;

    for(unsigned int i=0; i<files.size(); i++){
        prgBar->setValue(i);
        prgBar->update();
        prgBar->repaint();
        w->update();
        w->repaint();

        copy = true;

        cpStr = "cp $1 $2";

        currentFile = files[i];
        currentFile.replace(" ", "\\ ");
        dest = baseDest;

        if(currentFile[currentFile.length() - 1] == '/'){
            currentFile = " -r " + currentFile;

            filename = getName(currentFile, 2);

            dest = baseDest + "/" + filename + "/";
            dirStr = "mkdir " + dest;

            dir = dirStr.toUtf8().constData();

            if(!copyD_all && system(dir.c_str())){
                QMessageBox msgBox;
                createMsgBox(&msgBox, false, filename);

                int ret = msgBox.exec();

                if(ret == QMessageBox::No){
                    copy = false;
                }else if(ret == QMessageBox::NoAll){
                    copy = false;
                    copyD = false;
                    copyD_all = true;
                }else if(ret == QMessageBox::YesAll){
                    copyD = true;
                    copyD_all = true;
                }
            }else{
                copy = copyD;
            }
        }else{
            filename = getName(currentFile, 1);
            dest = baseDest + "/" + filename;

            dirStr = "cd $1 && ls | grep $2";
            dirStr.replace("$1", baseDest);
            dirStr.replace("$2", filename.replace(" ", "\\ "));

            dir = dirStr.toUtf8().constData();

            if(!copyF_all && !system(dir.c_str())){
                QMessageBox msgBox;
                createMsgBox(&msgBox, true, filename);

                int ret = msgBox.exec();

                if(ret == QMessageBox::No){
                    copy = false;
                }else if(ret == QMessageBox::NoAll){
                    copy = false;
                    copyF = false;
                    copyF_all = true;
                }else if(ret == QMessageBox::YesAll){
                    copyF = true;
                    copyF_all = true;
                }
            }else{
                copy = copyF;
            }
        }

        if(copy){
            cpStr.replace("$1", currentFile);
            cpStr.replace("$2", dest);

            cp = cpStr.toUtf8().constData();
            system(cp.c_str());
        }
    }

    prgBar->setValue(files.size());
    lblStatus->setText("Done! Ready");
    clear();
}

bool Manager::isApp(QString file){
    bool ret = false;

    file = file.right(4);

    QMessageBox::information(NULL, "", file);

    ret = file[0] == 'a';
    ret = ret && file[1] == 'p';
    ret = ret && file[2] == 'p';
    ret = ret && file[3] == '/';

    return ret;
}

void Manager::createMsgBox(QMessageBox* msgBox, bool file, QString name){
    QString err, infoText;
    if(file){
        err = tr("File $1 already exists.");
        infoText = tr("Do you wanto to replace it?");
    }else{
        err = tr("Folder $1 already exists.");
        infoText = tr("Do you wanto to replace its content?");
    }
    err.replace("$1", name.replace("\\ ", " "));

    msgBox->setWindowTitle(tr("Warning"));
    msgBox->setText(err);
    msgBox->setInformativeText(infoText);
    msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::YesAll | QMessageBox::NoAll);
    msgBox->setDefaultButton(QMessageBox::No);
    msgBox->button(QMessageBox::Yes)->setText(tr("Yes"));
    msgBox->button(QMessageBox::No)->setText(tr("No"));
    msgBox->button(QMessageBox::YesAll)->setText(tr("Yes to all"));
    msgBox->button(QMessageBox::NoAll)->setText(tr("No to all"));
    msgBox->setIconPixmap(QPixmap (":/images/copy.png"));
}

QString Manager::getName(QString path, int type){
    QString folder = "";

    int i;
    for(i=path.length() - type; i>=0 && path[i] != '/'; i--);

    i++;
    for(i; i<path.length() - (type - 1); i++){
        folder += path[i];
    }

    return folder;
}

void Manager::addFile(QList<QUrl> urlList){
    for(int i=0; i<urlList.size(); i++){
        QString path=urlList.at(i).toString();
        path.replace("file://", "");
        files.push_back(path);
    }

    updateList();
    dropArea->setAlignment(Qt::AlignLeft);
}

void Manager::updateList(){
    QString text = "";
    for(unsigned int i=0; i<files.size(); i++){
        text = text + files[i] + "\n";
    }

    dropArea->setText(text);
}

void Manager::findDevices(){
    cmbDestination->clear();

    FILE* out = popen("diskutil list | grep NTFS | awk '{print $3}'", "r");

    if(!out){
        pclose(out);
        return;
    }

    char buffer[1024];
    char *line;
    while (line = fgets(buffer, sizeof(buffer), out)){
        QString dev = line;
        dev.replace("\n", "");
        cmbDestination->addItem(dev);
    }
    pclose(out);
}

void Manager::clear(){
    while(files.size() > 0){
        files.pop_back();
    }

    dropArea->clear();
}

void Manager::openVolumes(){
    system("open /Volumes");
}

void Manager::linkVolumes(){
    bool ok;
    QString name = QInputDialog::getText(NULL, tr("Name"), tr("Insert name of new link folder"), QLineEdit::Normal, "", &ok);

    if(ok && !name.isEmpty()){
        name.replace(" ", "");

        QString cmdStr = "ln -s /Volumes $1";

        struct passwd *pw = getpwuid(getuid());
        QString path = pw->pw_dir;
        path += "/desktop/" + name;
        cmdStr.replace("$1", path);

        string cmd = cmdStr.toUtf8().constData();

        system(cmd.c_str());
    }
}

void Manager::openAbout(){
    aboutApp->show();
}
