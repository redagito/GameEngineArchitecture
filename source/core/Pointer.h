#pragma once

#include <cassert>

/**
* Smart pointer
*/
template <typename T>
class Pointer
{
   public:
    Pointer(T* object = nullptr);
    Pointer(const Pointer& p);
    ~Pointer();

    /**
    * Implicit conversion
    */
    operator T*();
    T& operator*();
    T* operator->();

    /**
    * Assignment
    */
    Pointer& operator=(T* object);
    Pointer& operator=(const Pointer& p);

    /**
    * Comparison
    */
    bool operator==(const T* object) const;
    bool operator!=(const T* object) const;

    bool operator==(const Pointer& p) const;
    bool operator!=(const Pointer& p) const;

   private:
    void clear();
    void assign(T* object);

    // Shared object
    T* m_object = nullptr;
};

template <typename T>
Pointer<T>::Pointer(T* object) : m_object(object)
{
    if (m_object != nullptr) m_object->incrementReferences();
}

template <typename T>
Pointer<T>::Pointer(const Pointer& p) : m_object(p.m_object)
{
    if (m_object != nullptr) m_object->incrementReferences();
}

template <typename T>
Pointer<T>::~Pointer()
{
    clear();
}

template <typename T>
Pointer<T>::operator T*()
{
    return m_object;
}

template <typename T>
T& Pointer<T>::operator*()
{
    assert(m_object != nullptr);
    return *m_object;
}

template <typename T>
T* Pointer<T>::operator->()
{
    return m_object;
}

template <typename T>
Pointer<T>& Pointer<T>::operator=(T* object)
{
    assign(object);
    return *this;
}

template <typename T>
Pointer<T>& Pointer<T>::operator=(const Pointer<T>& p) {
    assign(p.m_object);
    return *this;
}

template <typename T>
bool Pointer<T>::operator==(const T* object) const
{
    return m_object == object;
}

template <typename T>
bool Pointer<T>::operator!=(const T* object) const
{
    return m_object != object;
}


template <typename T>
bool Pointer<T>::operator==(const Pointer& p) const
{
    return m_object == p.m_object;
}

template <typename T>
bool Pointer<T>::operator!=(const Pointer& p) const
{
    return m_object != p.m_object;
}

template <typename T>
void Pointer<T>::clear()
{
    if (m_object == nullptr) return;

    m_object->decrementReferences();
    if (m_object->getReferences() == 0) delete m_object;
    m_object = nullptr;
}

template <typename T>
void Pointer<T>::assign(T* object)
{
    if (m_object == object) return;
    clear();

    if (object == nullptr) return;
    m_object = object;
    m_object->incrementReferences();
}