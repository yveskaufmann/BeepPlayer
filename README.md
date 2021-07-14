# BeepPlayer - Tetris with a sound synthesizer

I started this tiny project as simple sound synthesizer
that generates the tetris music.

A friend of mine was disappointed that the actual game was missing,
so I added the missing game.

## Build

### Windows

You can use [MinGW](https://sourceforge.net/projects/mingw/) install and to build this game,
you need to install `g++` and `mingw32-make`. In order to build, link and run the game
you need to install the libraries:

- [SDL2](https://www.libsdl.org/download-2.0.php)
- [SDL_ttf 2.0](https://www.libsdl.org/projects/SDL_ttf/)

Simply download these libary and copy them into your mingw directory.
Now you should be able to build and run the game via:

sh```
mingw32-make
mingw32-make run
```

### Ubuntu

Install the necessary tools and dependencies (`g++`, `make`, `SDL2`) via:

sh```
$ sudo apt update
$ sudo apt install build-essential
$ sudo apt install ibsdl2-dev libsdl2-2.0-0
$ sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;
$ sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;
```

You can now build and run the game with:

sh```
$ make
$ make run
```

