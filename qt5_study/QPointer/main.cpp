#include <QCoreApplication>

#include <QPointer>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QDebug>
#include <QList>

#include "person.h"

#include <iostream>
#include <string>

#include <cstdio>
#include <cstring>

using namespace  std;

//Qt 中隐式共享和写时拷贝就是利用 QSharedDataPointer 和 QSharedData 这两个类来实现的。
//比如我们有个类叫做 Employee，里面有些数据希望能够利用隐式共享和写时拷贝技术。那么我们可以把需要隐式共享的数据封装到另一个类中，比如叫做 EmployeeData，这个类要继承自 QSharedData。
class EmployeeData : public QSharedData
{
public:
    EmployeeData() : id(-1) { }
    EmployeeData(const EmployeeData &other)
        : QSharedData(other), id(other.id), name(other.name) { }
    ~EmployeeData() { }

    int id;
    QString name;
};
//这个例子中，id 和 name 就是我们要隐式共享和写时拷贝的数据。那么 Employee 类需要这么来实现。

class Employee
{
public:
    Employee() { d = new EmployeeData; }
    Employee(const Employee &other)
        : d (other.d)
    {
    }
    Employee(int id, const QString &name)
    {
        d = new EmployeeData;
        setId(id);
        setName(name);
    }
    void setId(int id) { d->id = id; }
    void setName(const QString &name) { d->name = name; }

    int id() const { return d->id; }
    QString name() const { return d->name; }

private:
    QSharedDataPointer<EmployeeData> d;
};

//我们对 Employee 中数据的访问都要通过 d。那么当需要修改 id 或 name 时，QSharedDataPointer 类自动的调用 detach() 方法来完成数据的拷贝。d (other.d) 则完成了隐式共享的功能。

class MyClass
{
public:
    MyClass():str("null")
    {}
    MyClass(const MyClass &rhs):str(rhs.str)
    {}
    MyClass &operator=(const MyClass &rhs)
    {
        if (this != &rhs)
            str = rhs.str;
        return *this;
    }
    ~MyClass()
    {
        qDebug() << "delete";
    }
    QString str;
};

class QtSmartPointerTest
{
public:
    QtSmartPointerTest()
    {
        qDebug() << "creating";
    }

    ~QtSmartPointerTest()
    {
        qDebug() << "deleting";
    }

    int var = 8;
};


class Test
{
public:
    Test()
    {
        qDebug() << "creating Test";
        spt_ptr = new QtSmartPointerTest();
        qDebug() << spt_ptr->var;
        QSharedPointer<QtSmartPointerTest> spt_sptr(spt_ptr);
        qDebug() << spt_ptr;
    }
    ~Test()
    {
        qDebug() << spt_ptr->var <<spt_ptr;
        qDebug() << "deleting Test";
    }

    QtSmartPointerTest *spt_ptr;
};

void hasProblem()
{
    QList <Person*> listA;
    QList <Person*> listB;

    Person *w1 = new Person;
    Person *w2 = new Person;
    Person *w3 = new Person;

    listA.append(w1);
    listA.append(w2);
    listA.append(w3);

    listB.append(w1);
    listB.append(w2);
    listB.append(w3);

    foreach (Person *w, listA)
    {
        listA.removeOne(w);
        delete w;
        w = nullptr;
        if(w)
        {
            qDebug() << "listA is not null";
        }
        else
            qDebug() << "listA is null";
    }

    foreach (Person *w, listB)
    {
        if(w)
        {
            qDebug() << "listB is not null";
        }
        else
            qDebug() << "listB is null";
    }

}

void fixProblem()
{
    QList <QPointer<Person>> listA;
    QList <QPointer<Person>> listB;

    QPointer<Person> w1 = new Person;
    QPointer<Person> w2 = new Person;
    QPointer<Person> w3 = new Person;

    listA.append(w1);
    listA.append(w2);
    listA.append(w3);

    listB.append(w1);
    listB.append(w2);
    listB.append(w3);

    foreach (QPointer<Person> w, listA)
    {
        listA.removeOne(w);
        delete w;
        w = nullptr;
        if(w)
        {
            qDebug() << "listA is not null";
        }
        else
            qDebug() << "listA is null";
    }

    foreach (QPointer<Person> w, listB)
    {
        if(w)
        {
            qDebug() << "listB is not null";
        }
        else
            qDebug() << "listB is null";
    }
}

class Test1
{
public :
    Test1(int num):n(num){}
private:
    int n;
};
class Test2
{
public :
    explicit Test2(int num):n(num){}
private:
    int n;
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
        qDebug() << "test qscopedptr";
        {
            QScopedPointer<MyClass> m(new MyClass);
        }
        qDebug() << "test qsharedptr";
        QSharedPointer<MyClass> s(new MyClass);
        QSharedPointer<MyClass> s1 = s;
        QWeakPointer<MyClass> w = s;
        qDebug() << w.data()->str;
        s.clear();
        qDebug() << "after s is cleared";
        qDebug() << w.data()->str;
        qDebug() << "try s, after s is cleared";
        if (s.isNull())
            qDebug() << "s is null";
        else
            qDebug() << s->str;
        s1.clear();
        if (w.isNull())
            qDebug() << "w is null";
        else
            qDebug() << "w still has the resource";
    }

    {
        QList<QPointer<Person>> m_persons;
        QSharedPointer<Person> m_person;

        qDebug() << m_person;
        QPointer<Person> person1= new Person("person1");
        m_persons.append(person1);
        m_persons.append(new Person("person2"));


        QPointer<Person> tmp = new Person("tmp");
        // need delelet tmp
        delete tmp;
        QSharedPointer<Person> sharedPerson(new Person("sharedPerson"));
        m_person = sharedPerson;

        // 释放拥有的 children
        qDeleteAll(m_persons);
        m_persons.clear();
        // m_person 被释放，这就是智能指针
        if (m_person.isNull())
            qDebug() << "m_person is null";
        else
        {
            qDebug() << m_person<<endl;
        }
    }

    {
        QObject *obj = new QObject;
        QPointer<QObject> pObj(obj);
        delete obj;
        Q_ASSERT(pObj.isNull()); // pObj will be nullptr now
    }

    {
        int *pI = new int;
        QSharedPointer<int> pI1(pI);
        QSharedPointer<int> pI2 = pI1;
        pI1.clear();
        // pI2 is still pointing to pI, so it is not deleted
        pI2.clear();
        // No shared pointers anymore, pI is deleted
        if(pI1.isNull())
        {
            qDebug()<<endl<<"pI1.isNull()"<<endl;
        }
        if(pI2.isNull())
        {
            qDebug()<<"pI2.isNull()"<<endl;
        }
    }

    {
        hasProblem();
        fixProblem();
    }

    {
        //        char的范围是-128~127，a得到158后超出范围，应转为补码：158的有符号二进制是1001 1110，转为补码应先取反为0110 0001，再加1得到98，取相反数为-98。sum=200-98=102
        char a=101;
        int sum=200;
        a+=57;
        sum+=a;
        printf("%d\n",sum);     //102
    }

    {
        //        C++提供了关键字explicit，可以阻止不应该允许的经过转换构造函数进行的隐式转换的发生,声明为explicit的构造函数不能在隐式转换中使用。
        //        解析：explicit构造函数是用来防止隐式转换的
        //        编译时，会指出 t3那一行error:无法从“int”转换为“Test2”。而t1却编译通过。注释掉t3那行，调试时，t1已被赋值成功。
        Test1 t1 = 12;
        Test2 t2(13);
        //        Test2 t3 = 14;
    }

    {
        //        对字符串用sizeof时，需要考虑·\0；用strlen（长度）时不用考虑，所以前者比后者大1
        char a[]="12345";
        cout<<"sizeof(a):"<<sizeof (a)<<endl;//6
        cout<<"strlen(a):"<<strlen(a)<<endl; //5

    }

    {
        char ch = 0;
        short a = 1;
        ch = *(char *)&a;

        if (1 == ch)
            printf("Little Endian\n");
        else
            printf("Big Endian\n");

    }


    return a.exec();
}
