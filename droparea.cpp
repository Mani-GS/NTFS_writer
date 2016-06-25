#include <QtGui>

#include <QMessageBox>
#include "droparea.h"

DropArea::DropArea(QWidget *parent): QLabel(parent){
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    setAutoFillBackground(true);
    clear();
}

void DropArea::dragEnterEvent(QDragEnterEvent *event){
    setBackgroundRole(QPalette::Highlight);

    event->acceptProposedAction();
    emit changed(event->mimeData());
}

void DropArea::dragMoveEvent(QDragMoveEvent *event){
    event->acceptProposedAction();
}

void DropArea::dropEvent(QDropEvent *event){
    const QMimeData *mimeData = event->mimeData();

    QList<QUrl> urlList = mimeData->urls();
    emit dropped(urlList);

    setBackgroundRole(QPalette::Dark);
    event->acceptProposedAction();
}

void DropArea::dragLeaveEvent(QDragLeaveEvent *event){
    clear();
    event->accept();
}

void DropArea::clear(){
    setText(tr("<drop content>"));
    setBackgroundRole(QPalette::Dark);
    setAlignment(Qt::AlignCenter);

    emit changed();
}
