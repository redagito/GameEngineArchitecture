#include <iostream>

#include "core/Core.h"
#include "core/Object.h"

class MyClassA : public Object
{
   public:
    RTTI_DECLARE(MyClassA, Object);
};

class MyClassB : public MyClassA
{
   public:
    RTTI_DECLARE(MyClassB, MyClassA);
};

void appMain()
{
    Pointer<MyClassA> a{new MyClassA};
    a->setName("A");
    Pointer<MyClassB> b{new MyClassB};
    b->setName("B");

    Pointer<Object> c{new MyClassA};
    (*c).setName("C");

    Pointer<MyClassA> d{a};
    d->setName(d->getName() + "D");

    Pointer<MyClassA> e{d};
    e->setName(e->getName() + "E");

    Pointer<Object> f{e};
    f->setName(f->getName() + "F");

    Object::printInUse("usage.txt", "Before end");
}

int main(int argc, char** argv)
{
    Core::initialize();

    appMain();

    Core::terminate();

    return 0;
}