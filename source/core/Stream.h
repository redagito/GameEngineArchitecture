#pragma once

#include <cstdint>

class Object;

class Link
{
};

class Stream
{
   public:
       Stream();
       virtual ~Stream();
       
       bool insert(Object* object);
       bool remove(Object* object);
       void removeAll();
       
       size_t getObjectCount() const;
       Object* getObject(size_t index) const;

       bool isTopLevel(Object* object);

       /**
       * Load from binary buffer
       */
       bool load(const uint8_t* buffer, size_t bufferSize);

       /**
       * Save to binary buffer
       */
       bool save(uint8_t*& buffer, size_t& bufferSize) const;

       /**
       * Memory and disk usage in bytes
       */
       size_t getMemoryUsed() const;
       size_t getDiskUsed() const;

    private:
};