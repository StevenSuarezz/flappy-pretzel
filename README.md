# Flappy Pretzel

I made a flappy bird clone based around my Golden Retreiver named Pretzel because I was bored. Oh and also to learn SDL2 I guess. Guide Pretzel through pipes by controlling her vertical movement. Collect enough dog treats to up your score and she might even drop you a gift! 💩

## Prerequisites

- CMake (version 3.10 or higher)
- SDL2
- SDL2_image

### Installing Dependencies

#### Ubuntu/Debian
```bash
sudo apt-get install cmake libsdl2-dev libsdl2-image-dev
```

#### macOS
```bash
brew install cmake sdl2 sdl2_image
```

## Building the Game

1. Clone the repository:
```bash
git clone https://github.com/yourusername/flappy-pretzel.git
cd flappy-pretzel
```

2. Create and build the project:
```bash
mkdir build
cd build
cmake ..
make
```

3. Run the game:
```bash
./game
```

## Game Controls

- **Space**: Make Pretzel jump
- **Escape**: Quit the game

## Project Structure

```
flappy-pretzel/
├── CMakeLists.txt
├── src/
│   └── main.c
└── images/
    ├── pretzel.png
    ├── pipe.png
    └── background.png
```

## Game Features

- Smooth player movement with gravity physics
- Randomly generated pipe obstacles
- Dynamic player texture rotation based on velocity
- Consistent frame rate (60 FPS)
- Cross-platform support (Linux, macOS)

## Acknowledgments

- Inspired by the original Flappy Bird game
- Built using SDL2 library
- Built on my own (not following any tutorials or blindly copying/pasting AI generated code)
- Still a WIP, I expect much more refactoring to come
