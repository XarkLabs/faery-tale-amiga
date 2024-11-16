# The Faery Tale Adventure - macOS/SDL2

Xark of [XarkLabs](https://XarkLabs.com)

This is my attempt to get The Faery Tale Adventure to run on a modern platform.

Initial target is macOS/SDL2, but after that it should hopefully be fairly portable to other platforms.

My rough plan:

* Add AmigaOS includes, tweak as needed [DONE]
* Get C code compiling fairly cleanly with clang  [DONE]
* Fix C types to make some sense on 64-bit modern C [DONE]
* Add stubs and/or implementation for AmigaOS functions [DONE]
* Add stubs and/or implementation for asm routines [DONE]
* Add LOG messages to enable easier tracing [DONE]
* Get things linking [DONE]
  * Now game "runs" but fails rapidly until more things get implemented...
* Keep working on implementing and/or fixing stubs and issues until the game "thinks" it is running (with no sound/graphics). [ON-GOING]
  * Need to deal with endian issues (Amiga was big endian, modern machines little)
  * load all assets in Amiga (from disk image file)
  * Possibly setup 32-bit "arena" for assets (of 32-bit pointer issues)
  * Implement Amiga blitter draw routines
  * Implement Amiga font drawing routines
* Add some basic SDL2 controller or mouse hookup
* At that point my initial plan is to then add some SDL2 code that will "interpret" the Amiga screen data in memory and convert and draw it to an SDL2 window.
* Same idea for audio using SDL2 audio output

For the AmigaOS functionality, only the bits actually required by the game are planned to be implemented (a relatively small slice of functionality).

The end goal is a "native" FTA that runs basically identically to the Amiga, but in a window on a modern PC (using SDL2 for portability).

> :mag: If you are interested in helping with this project, or just want to chat about other FTA development projects (or FTA in general) please ping me on Discord, username "true_xark".

I would like to thank Talin for releasing this code (and Joe for keeping a copy around)! :raised_hands:

I was very proud to have played a very small part in the original Amiga version back in the day, and I am similarly proud to get a chance to "hack on" the code now.

-Xark

NOTE: Please see [README_FTA](./README_FTA.md) for the original FTA release README.

[XarkLabs](https://XarkLabs.com)
[XarkLabs YouTube](https://www.youtube.com/@XarkLabs)
