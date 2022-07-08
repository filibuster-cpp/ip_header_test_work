#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    oct0.addWidget(&vers);
    oct0.addWidget(&ihl);
    oct0.addWidget(&dsc);
    oct0.addWidget(&ecn);
    oct0.addWidget(&lenPac);
    Vlay.addLayout(&oct0);
    oct4.addWidget(&id);
    oct4.addWidget(&flags);
    oct4.addWidget(&offset);
    Vlay.addLayout(&oct4);
    oct8.addWidget(&ttl);
    oct8.addWidget(&protocol);
    oct8.addWidget(&chsum);
    Vlay.addLayout(&oct8);
    oct12.addWidget(&ipSourse);
    Vlay.addLayout(&oct12);
    oct16.addWidget(&ipDist);
    Vlay.addLayout(&oct16);
    setLayout(&Vlay);
    connect(&shark, SIGNAL(readyReadStandardOutput()), this, SLOT(view()));
    shark.start("tshark", QStringList() << "-Oip");

}

Widget::~Widget()
{
}

void Widget::view()
{
    QByteArray stdout = shark.readAllStandardOutput();
    if (stdout.indexOf("Frame") == -1) return;
    vers.setPlainText(find(" = Version: ", stdout));
    ihl.setPlainText(find(" bytes (", stdout));
    dsc.setPlainText(find(" Field: ", stdout));
    ecn.setPlainText(find(" Transport (", stdout));
    lenPac.setPlainText(find(" Length: ", stdout));
    id.setPlainText(find("Identification: ", stdout));
    flags.setPlainText(find("Flags: ", stdout));
    offset.setPlainText(find("Offset: ", stdout));
    ttl.setPlainText(find("Live: ", stdout));
    protocol.setPlainText(find("Protocol: ", stdout));
    chsum.setPlainText(find("Checksum: ", stdout));
    ipSourse.setPlainText(find("Source Address: ", stdout));
    ipDist.setPlainText(find("Destination Address: ", stdout));
}

QString Widget::find(QString target, QByteArray arr)
{
    int index = arr.indexOf(target) + target.size();
    QString output;
    while((arr.at(index) != ' ') && (arr.at(index) != '\n') && (arr.at(index) != ',') && (arr.at(index) != ')')) {
        output.append(arr.at(index));
        ++index;
    }
    return output;
}

