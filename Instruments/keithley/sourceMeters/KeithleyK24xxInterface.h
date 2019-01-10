#ifndef KEITHLEYK24XXINTERFACE_H
#define KEITHLEYK24XXINTERFACE_H

class KeithleyK24xxInterface
{
public:
    virtual ~KeithleyK24xxInterface() {}
    virtual QString echo(const QString &message) = 0;
};

#define KeithleyK24xxInterface_iid "org.qt-project.Qt.Examples.KeithleyK24xxInterface"

Q_DECLARE_INTERFACE(KeithleyK24xxInterface, KeithleyK24xxInterface_iid)

#endif // KEITHLEYK24XXINTERFACE_H
