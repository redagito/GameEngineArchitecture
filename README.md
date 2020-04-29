# Game Engine Architecture

Game engine implementation based on on the book 3D Game Engine Architecture by David H. Eberly.

My goal is to implement the engine as described in the book with modern OpenGL.

# Modules

The structure of the project follows the basic outline of the engine as described in the book.

## Math

The math module provides generic geometric primitives and transformation calculation.

## Core

The core module provides

* Object system
* RTTI
* Smart pointer
* Controller
* Streaming
* Pre-main initialization
* Post-main termination

## Graphics

The graphics module provides

* Renderer
* Scene graph
* Bounding volumes