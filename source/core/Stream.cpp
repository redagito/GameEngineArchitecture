#include "core/Stream.h"

#include "core/Object.h"

Object* Link::getLinkId() const { return nullptr; }

Stream::Stream() {}

Stream::~Stream() {}

bool Stream::insert(Object* object) { return false; }

bool Stream::insertInOrdered(Object* object) { return false; }

Object* Stream::getOrderedObject(size_t index) { return nullptr; }

size_t Stream::getOrderedCount() const { return 0; }

bool Stream::insertInMap(Object* object, void* /* ??? */) { return false; }

void* Stream::getFromMap(Object* object) { return nullptr; }

bool Stream::remove(Object* object) { return false; }

void Stream::removeAll() {}

size_t Stream::getObjectCount() const { return 0; }

Object* Stream::getObject(size_t index) const { return nullptr; }

bool Stream::isTopLevel(Object* object) { return false; }

bool Stream::load(const uint8_t* buffer, size_t bufferSize) { return false; }

bool Stream::save(uint8_t*& buffer, size_t& bufferSize) const { return false; }

size_t Stream::getMemoryUsed() const { return 0; }

size_t Stream::getDiskUsed() const { return 0; }

void Stream::write(const void* ptr) {}

void Stream::write(const size_t size) {}

void Stream::write(const std::string& str) {}

void Stream::read(void*& ptr) {}

void Stream::read(size_t& size) {}

void Stream::read(std::string& str) {}