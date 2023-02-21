#ifndef IOBJECT_H
#define IOBJECT_H

// I-Object stand for Interface Object (giao dien.)

class IObject
{

    public:
        virtual void Draw() = 0;
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;
};

#endif // IOBJECT_H
