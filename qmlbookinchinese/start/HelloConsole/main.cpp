#include <QCoreApplication>

// module or class includes
#include <QtCore>

#include <QQueue>

#include <QtGlobal>

#include <QTextCodec>

#include <iostream>
#include <string>

//using namespace std;

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

/*
QString 类从字符串转换为整数的函数有：
int toInt(bool * ok = Q_NULLPTR, int base = 10) const
long toLong (bool * ok = Q_NULLPTR, int base = 10) const
short toShort (bool * ok = Q_NULLPTR, int base = 10) const
uint toUInt (bool *ok = Q_NULLPTR, int base = 10) const
ulong toULong (bool *ok = Q_NULLPTR, int base = 10) const

这些函数如果不设置参数，缺省表示从十进制表示的字符串转换为整数；若指定整数基参数，还可以直接将二进制、十六进制字符串转换为整数。

QString 将字符串转换为浮点数的函数有：
double toDouble(bool *ok = Q_NULLPTR) const
float toFloat (bool * ok = Q_NULLPTR) const

str=QString::number(total,'f',2);
str=QString::asprintf ("%.2f", total);
str=str.setNum(total,'f',2);
str=str.sprintf ("%.2f，total);

可以使用 QString 的静态函数 number() 和 asprintf()，也可以使用其公共函数 setNum() 和 sprintf()。 QString 的 sprintf() 函数与 C 语言里的 sprintf() 函数的格式是一样的，而 setNum() 和 number() 函数使用另外一种格式定义，而且 setNum 和 number 有多个重载函数定义，可以处理各种类型的整数和浮点数，在处理整数时还可以指定进制，例如将一个整数直接转换为十六进制或二进制字符串。
进制转换

将一个整数转换为不同进制的字符串，可以使用 QString 的函数 setNum() 或静态函数 number()，它们的函数原型是：
Qstring &setNum (int n, int base = 10)
QString number (int n, int base = 10)

其中 n 是待转换的整数，base 是使用的进制，缺省为十进制，也可以指定为十六进制和二进制。下面是读取二进制字符串，然后转换为十进制和十六进制显示的按钮的槽函数代码。
*/



QString str2qstr(const std::string  str)
{
    return QString::fromLocal8Bit(str.data());
}

std::string qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return std::string(cdata);
}

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

    //    if(true){
    //        //QString 内部采用的是Unicode
    //        QString qstr="中国";
    //        std::string str9=qstr.toStdString();
    //        cout<<str9.c_str()<<endl;//乱码
    //        QString str8=QString(str9.c_str());
    //        cout<<str8<<endl;//乱码


    //        QString str1=QString::fromUtf8("文");
    //        QString str2=QString::fromUtf8("中");
    //        QString str3=str1;
    //        str1.append (str2) ; //str1="文中"
    //        str3.prepend (str2) ; //str3="中文"
    //        cout<<str1<<endl;//乱码
    //        cout<<str3<<endl;//乱码
    //    }

    if(true){
        //        QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

        //        QString qstr="中国";
        //        cout<<qstr<<endl;
        QString str = QString::fromLocal8Bit("中文");
        //        QString str = QString::fromUtf8("中文");
        cout<<str<<endl;//正常


        //        std::string str9=qstr.toStdString();
        //        cout<<str9.c_str()<<endl;//乱码
        //        QString str8=QString(str9.c_str());
        //        cout<<str8<<endl;//乱码


        //        QString str1=QString::fromUtf8("文");
        //        QString str2=QString::fromUtf8("中");
        //        QString str3=str1;
        //        str1.append (str2) ; //str1="文中"
        //        str3.prepend (str2) ; //str3="中文"
        //        cout<<str1<<endl;//乱码
        //        cout<<str3<<endl;//乱码

        QString str1=QString::fromLocal8Bit("文");
        QString str2=QString::fromLocal8Bit("中");
        QString str3=str1;
        str1.append (str2) ; //str1="文中"
        str3.prepend (str2) ; //str3="中文"
        cout<<str1<<endl;//乱码
        cout<<str3<<endl;//乱码
    }

    if(true){
//        isNull() 和 isEmpty()
//        两个函数都判读字符串是否为空，但是稍有差别。如果一个空字符串，只有“\0”，isNull() 返回 false，而 isEmpty() 返回 true；只有未赋值的字符串，isNull() 才返回 true。

        QString str1, str2="";
        bool N=str1.isNull () ; // N=true 未赋值字符串变量
        N=str2.isNull () ; // N=false 只有"\0"的字符串，也不是 Null
        N=str1.isEmpty(); // N=true
        N=str2.isEmpty(); // N=true
    }

    if(true)
    {
//        trimmed() 和 simplified()
//        trimmed() 去掉字符串首尾的空格，simplified() 不仅去掉首尾的空格，中间连续的空格也用一个空格替换。
        QString str1=" Are you     OK? ", str2;
        str2=str1.trimmed () ; //str1="Are you OK? "
        qDebug()<<str2<<endl;
        str2=str1.simplified(); //str1="Are you OK?"
        qDebug()<<str2<<endl;
    }
    if(true){
//        section()
//        section() 函数的原型为：
//        QString section (const QString &sep, int start, int end = -1, SectionFlags flags = SectionDefault) const

//        其功能是从字符串中提取以 sep 作为分隔符，从 start 端到 end 端的字符串。
//        纯文本复制
        QString str2, str1=str2qstr("学生姓名,男,1984-3-4,汉族,山东");
        str2=str1.section (",",0,0); // str2="学生姓名"， 第 1 段的编号为 0
        qDebug()<<str2<<endl;
        str2=str1.section (",",1,1); // str2="男"
        qDebug()<<str2<<endl;
        str2=str1.section (",",0,1); // str2="学生姓名，男"
        qDebug()<<str2<<endl;
        str2=str1.section (",",4,4); // str2="山东"
        qDebug()<<str2<<endl;
    }

    return a.exec();
}

