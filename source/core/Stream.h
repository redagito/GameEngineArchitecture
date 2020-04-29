#pragma once

#include <cstdint>
#include <string>

class Object;

class Link
{
   public:
    Object* getLinkId() const;

   private:
};

class Stream
{
   public:
    Stream();
    virtual ~Stream();

    // These should take const objects?
    bool insert(Object* object);

    bool insertInOrdered(Object* object);
    Object* getOrderedObject(size_t index);
    size_t getOrderedCount() const;

    bool insertInMap(Object* object, void* /* ??? */);
    void* getFromMap(Object* object);

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

    // Stores address
    void write(const void* ptr);
    void write(const size_t size);
    void write(const std::string& str);

    // Reads address
    void read(void*& ptr);
    void read(size_t& size);
    void read(std::string& str);

   private:
};