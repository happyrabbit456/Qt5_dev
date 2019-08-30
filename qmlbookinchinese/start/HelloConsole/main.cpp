#include <QCoreApplication>

// module or class includes
#include <QtCore>

#include <QQueue>

// text stream is text-codec aware
static QTextStream cout(stdout, QIODevice::WriteOnly);

//Qt 的顺序容器类有 QList、QLinkedList、QVector、QStack 和 QQueue。

//Qt 还提供关联容器类 QMap、QMultiMap、QHash、QMultiHash 和 QSet。

//QMultiMap 和 QMultiHash 支持一个键关联多个值，QHash 和 QMultiHash 类使用散列函数进行查找，查找速度更快。

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // avoid compiler warnings
    Q_UNUSED(argc)
    Q_UNUSED(argv)

    if(true){
        QString s1("Paris");
        QString s2("London");
        // string concatenation
        QString s = s1 + " " + s2 + "!";
        cout << s << endl;

        // convenient container classes
        QStringList list;
        list <<  s1 << s2;
        // join strings
        QString s3 = list.join(" ") + "!";
        cout << s3 << endl;
    }

    if(true){
        QString s1("Hello");
        QString s2("Qt");
        QList<QString> list;
        // stream into containers
        list << s1 << s2;
        // Java and STL like iterators
        QListIterator<QString> iter(list);
        while(iter.hasNext()) {
            cout << iter.next();
            if(iter.hasNext()) {
                cout << " ";
            }
        }
        cout << "!" << endl;

        QString str1=list[1]; //str1=="two"
        QString str0=list.at(0); //str0=="one"
        cout<<str1<<endl;
        cout<<str0<<endl;

        QList<QString> aList;
        aList.append("Monday");
        aList.append("Tuesday");
        aList.append("Wednesday");
        QString str=aList[0];
        cout<<str<<endl;

        QStack<int> stack;
        stack.push(10);
        stack.push(20);
        stack.push(30);
        while (!stack.isEmpty())
            cout << stack.pop() << endl;

        QQueue<int> queue;
        queue.enqueue (10);
        queue.enqueue(20);
        queue.enqueue (30);
        while (!queue.isEmpty())
            cout << queue.dequeue() << endl;
    }

    if(true){
        QList<QStringList> data;
        // file operations
        QFile file("sample.csv");
        if(file.open(QIODevice::ReadOnly)) {
            QTextStream stream(&file);
            // loop forever macro
            forever {
                QString line = stream.readLine();
                // test for null string 'String()'
                if(line.isNull()) {
                    break;
                }
                // test for empty string 'QString("")'
                if(line.isEmpty()) {
                    continue;
                }
                QStringList row;
                // for each loop to iterate over containers
                foreach(const QString& cell, line.split(",")) {
                    row.append(cell.trimmed());
                }
                data.append(row);
            }
        }
        // No cleanup necessary.
    }

    return a.exec();
}
