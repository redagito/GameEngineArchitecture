#pragma once

// Forward declare
class Object;

class Controller
{
    public:
        virtual ~Controller();

       void setObject(Object* object);
       Object* getObject();
       
       virtual void update(double deltaTime) = 0;

    private:
        // Managed object
        Object* m_object = nullptr;
};