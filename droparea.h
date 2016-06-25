#ifndef DROPAREA_H
#define DROPAREA_H

#include <QtGui>
#include <QLabel>

class QMimeData;

class DropArea : public QLabel{
    Q_OBJECT

public:
    DropArea(QWidget *parent = 0);

public slots:
    void clear();

signals:
    void changed(const QMimeData *mimeData = 0);
    void dropped(QList<QUrl> urlList);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    QLabel *label;
};

#endif
