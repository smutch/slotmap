Slot map
========

This is a simple slot map implementation in C, based on the `code <https://github.com/seanmiddleditch/TinyExperiments/blob/master/SlotMapExample/Main.cpp>`_ and `blog post <https://seanmiddleditch.com/2013-01-05-data-structures-for-game-developers-the-slot-map/>`_ by Sean Middleditch.

A slot map is a data structured used in game development (amongst other fields) to hold objects which can be continually destroyed or created.  Each object is assigned a unique ID and stored in a stack or vector which grows as needed.  Objects can be retrieved using this ID.  When objects are destroyed, their IDs are mangled and their memory left to be used for newly created objects.  Slot maps provide a useful compromise between lookup speed, and memory locality.

This implementation was developed as a learning exercise and basis for experimentation for a new data structure to underpin a galaxy formation model.  The code likely has many places for improvement, but may be useful as a starting point for others and so I have put it out here.

The chances that you will want to use this code without modification is slim.  At the very least, you will likely want to modify the :any:`item` struct to reflect the data which you would like to store.

As part of this implementation, a simple :doc:`stack <stack>` data structure is also provided which may be useful on its own in some cases.
