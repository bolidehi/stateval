The project is about to implement a hierarchical statemachine. There's no code generator, but a state machine data format. The current implementation is done in C++.

It's main usage is the design of embedded GUI applications with possibly lot of views. But also non GUI applications could use the state machine implementation.

The GUI framework implementation is done with EFLxx, but should later use also other GUI toolkits.

There's also a start of a graphical statemachine editor. The implementation is done with Gtkmm and Cairo.