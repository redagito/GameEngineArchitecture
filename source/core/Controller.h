#pragma once

// Forward declare
class Object;
class Stream;

class Controller
{
    public:
        virtual ~Controller();

       void setObject(Object* object);
       Object* getObject();
       
       virtual void update(double deltaTime) = 0;
       virtual void registerStream(Stream& stream) = 0;

    private:
        // Managed object
        Object* m_object = nullptr;
};