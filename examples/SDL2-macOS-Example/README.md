###  Installation guide for macOS v11.2.3
##  Install Homebrew
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
##  Install SDL2 with brew
$ brew install sdl2
##  Compile main.cpp
$ g++ -o a.out main.cpp -lSDL2
##Run the executable
$ ./a.out
