#include "graphics/Texture.h"

Texture::Texture(Image* image = nullptr) : m_image(image) {}

void Texture::setImage(Pointer<Image> image) { m_image = image; }
Pointer<Image> Texture::getImage() { return m_image; }