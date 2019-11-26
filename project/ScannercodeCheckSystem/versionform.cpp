#include "versionform.h"
#include "ui_versionform.h"

VersionForm::VersionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VersionForm)
{
    ui->setupUi(this);

    QStringList lines;
    QFile file( "version.txt" );
    if ( file.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &file );
        stream.setCodec("utf-8");
        QString line;
        while ( !stream.atEnd() ) {
            line = stream.readLine(); // 不包括“\n”的一行文本
            lines += line;
        }
        foreach (QString strLine, lines) {
            ui->plainTextEditVersion->appendPlainText(strLine);
        }

        file.close();
    }
}

VersionForm::~VersionForm()
{
    delete ui;
}
