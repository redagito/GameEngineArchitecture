# Game Engine Architecture

Game engine implementation based on on the book 3D Game Engine Architecture by David H. Eberly.

My goal is to implement the basic engine as described in the book with modern OpenGL.

# Modules

The structure of the engine follows the basic outline of the engine described in the book.

## Core

The core module does not have dependencies on any other module.

It provides

* Object system
* RTTI
* Smart pointer
* Controller
* Streaming