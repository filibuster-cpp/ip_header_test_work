#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QProcess>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void view();
private:
    QString find(QString, QByteArray);
private:
    QHBoxLayout oct0, oct4, oct8, oct12, oct16;
    QVBoxLayout Vlay;
    QPlainTextEdit vers, ihl, dsc, ecn, lenPac, id, flags, offset, ttl, protocol, chsum, ipSourse, ipDist;
    QProcess shark;
};
#endif // WIDGET_H
