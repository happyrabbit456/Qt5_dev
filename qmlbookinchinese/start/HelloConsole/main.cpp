#include <QCoreApplication>

// module or class includes
#include <QtCore>

#include <QQueue>

#include <QtGlobal>

// text stream is text-codec aware
static QTextStream cout(stdout, QIODevice::WriteOnly);

//Qt 的顺序容器类有 QList、QLinkedList、QVector、QStack 和 QQueue。

//Qt 还提供关联容器类 QMap、QMultiMap、QHash、QMultiHash 和 QSet。

//QMultiMap 和 QMultiHash 支持一个键关联多个值，QHash 和 QMultiHash 类使用散列函数进行查找，查找速度更快。

//迭代器为访问容器类里的数据项提供了统一的方法，Qt 有两种迭代器类：Java 类型的迭代器和 STL 类型的迭代器。

//两者比较，Java 类型的迭代器更易于使用，且提供一些高级功能，而 STL 类型的迭代器效率更高。

/*
表 1 Java类型的迭代器类
容器类                         只读迭代器                       读写迭代器
QList<T>, QQueue<T>         QListItcrator<T>                QMutableListItcrator<T>
QLinkedList<T>              QLinkedListIterator<T>          QMutableLinkedListIterator<T>
QVector<T>, QStack<T>       QVectorllcrator<T>              QMutableVectorIterator<T>
QSet<T>	QSetItcrator<T>     QMutableSetItcrator<T>
QMap<Key, T>, QMultiMap<Key, T>     QMapIterator<Key, T>	QMutableMapIterator<Key, T>
QHash<Key, T>, QMultiHash<Key, T>	QHashIterator<Key, T>	QMutablcHashlterator<Key, T>
*/

/*
表 4 STL 类型的迭代器类
容器类                         只读迭代器                               读写迭代器
QList<T>, QQueue<T>         QList<T>::const iterator                QList<T>::iterator
QLinkedList<T>              QLinkedList<1>: :const_iterator         QLinkedList<T>::iterator
QVector<T>, QStack<T>       QVector<T>::const_ilerator              QVector<T>::iterator
QSet<T>                     QSet<T>::const_iterator                 QSet<T>::iterator
QMap<Key, P> QMultiMap<Kcy, T>      QMap<Key, T>::const_iterator	QMap<Key, T>:: iterator
QHash<Key, T> QMultiHash<Key, T>	QHash<Key, T>: :const_iterator	QHash<Key, T>::iterator
*/

//Qt 提供一个关键字 foreach (实际是 <QtGlobal> 里定义的一个宏）用于方便地访问容器里所有数据项。

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

        QString str8;
        foreach(str8,list){
            qDebug()<<str8<<endl;
        }

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

        QListIterator<QString> i(aList);
        while(i.hasNext()){
            qDebug()<<i.next();
        }
        while (i.hasPrevious()) {
            qDebug()<<i.previous();

        }

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

        QSet<QString> set;
        set<<"dog"<<"cat"<<"tiger";
        if(set.contains("cat")){
            cout<<"contain cat!"<<endl;
        }

        QMap<QString, int> map;
        map["one"] = 1;
        map["two"] = 2;
        map["three "] = 3;
        map.insert("four",4);
        map.remove("two");
        int num1=map["one"];
        int num2=map.value("three");
        int timeout=map.value("TIMEOUT",30);
        cout<<"num1:"<<num1<<endl<<"num2:"<<num2<<endl;
        cout<<"timeout:"<<timeout<<endl;

        foreach (const QString &str, map.keys())
            qDebug() << str << ':' << map.value(str);

        QMultiMap<QString, int> map1, map2, map3;
        map1.insert("plenty", 100);
        map1.insert("plenty", 2000); // map1.size() == 2
        map2.insert("plenty", 5000); // map2.size() == 1
        map3 = map1 + map2; // map3.size() == 3
        QList<int> values = map3.values("plenty");
        for (int i = 0; i < values.size(); ++i)
            cout << values.at(i) << endl;

        foreach (const QString &str, map.uniqueKeys()) {
            foreach (int i, map.values(str))
                qDebug() << str << ':' << i;
        }
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

    if(true){
        QList<int> list;
        list <<1<<2<<3<<4<<5;
        QMutableListIterator<int> i (list);
        while (i.hasNext()) {
            if (i.next() % 2 != 0)
                i.remove();
        }
    }

    if(true){
        QMap<QString, QString> map;
        map.insert("Paris", "France");
        map.insert("New York", "USA");
        map.insert("Mexico City", "USA");
        map.insert("Moscow", "Russia");

        QMutableMapIterator<QString, QString> i(map);
        while (i.hasNext ()) {
            if (i.next().key().endsWith("City"))
                i.remove();
        }

        while (i.findNext("USA"))
            i.remove();
    }

    if(true){
        QList<QString> list;
        list << "A" << "B" << "C" << "D";
        QList<QString>::const_iterator i;
        for (i = list.constBegin(); i != list.constEnd(); ++i)
            qDebug() << *i;

        QList<QString>::reverse_iterator r;
        for (r = list.rbegin(); r != list.rend(); ++r){
            *r = r->toLower();
        }
    }


    return a.exec();
}
