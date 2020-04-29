#include "core/Controller.h"

Controller::~Controller() {}

void Controller::setObject(Object* object) {
	m_object = object;
}

Object* Controller::getObject() {
	return m_object;
} 