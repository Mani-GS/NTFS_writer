#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog){
    ui->setupUi(this);

    lblIcon = findChild<QLabel*>("lblIcon");
    setIcon();
}

AboutDialog::~AboutDialog(){
    delete ui;
}

void AboutDialog::setIcon(){
    QPixmap png (":/images/drop.png");

    lblIcon->setPixmap(png);
}
