<div align="center">

# Cub3D

![Norminette](https://img.shields.io/badge/Norm-passing-brightgreen?style=flat-square) ![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white) ![Makefile](https://img.shields.io/badge/Makefile-427819?style=flat-square) ![MLX42](https://img.shields.io/badge/MLX42-Graphics-blue?style=flat-square) ![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat-square&logo=linux&logoColor=black) ![macOS](https://img.shields.io/badge/macOS-000000?style=flat-square&logo=apple&logoColor=white) ![42 School](https://img.shields.io/badge/42-School-000000?style=flat-square)

*A C-based 3D raycasting engine inspired by Wolfenstein 3D*

</div>

---

## 👥 Authors

This project was made with illusion and hard work by:

- [**crmorale**](https://github.com/Crmorale)
- [**fmesa-or**](https://github.com/fmesa-or)

Done in 2025

---

## About the Project

Cub3D is a raycasting graphics project that renders a 3D maze environment in first-person perspective. Using raycasting techniques similar to classic games like Wolfenstein 3D, this project demonstrates fundamental concepts of computer graphics, linear algebra, and game development in C. The project utilizes the MLX42 graphics library and the X11 display server.

## Features

- ✨ **Raycasting Engine** - Renders dynamic 3D environments in real-time
- 🎨 **Texture Mapping** - All four walls (North, South, East, West) support custom textures
- 🎮 **Real-time Input** - Smooth player movement and camera rotation
- 🌅 **Customizable Maps** - Support for .cub configuration files with custom maps and textures
- ⚡ **Performance Optimized** - Efficient raycasting algorithm with minimal overhead
- 🛡️ **Memory Management** - Comprehensive memory allocation tracking and leak prevention

## Requirements

- **Compiler**: `gcc` (C99 or later)
- **Flags**: `-Wall -Wextra -Werror -g`
- **OS**: Linux / macOS
- **Graphics**: MLX42 with GLFW3 support
- **Dependencies**: libglfw3-dev, libx11-dev, libglx-dev

## Installation and Setup

### Prerequisites

#### macOS
```bash
# Install required dependencies
brew install glfw3 cmake
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libglfw3-dev libx11-dev libglx-dev cmake
```

### Building the Project

```bash
# Clone the repository
git clone https://github.com/usuario/cub3D.git
cd cub3D

# Compile the project
make

# Clean build artifacts
make clean

# Remove all generated files
make fclean

# Rebuild everything
make re
```

## Usage

### Running the Project

```bash
./cub3D maps/goods/donut.cub
```

### Map File Format

Map files use the `.cub` extension and contain:

```
# Textures (required for all 4 directions)
NO ./textures/north.xpm42
SO ./textures/south.xpm42
EA ./textures/east.xpm42
WE ./textures/west.xpm42

# Floor and ceiling colors (RGB format)
F 220,100,0
C 225,30,0

# Map grid (1 = wall, 0 = space, N/S/E/W = player spawn position)
1111111111
1000000001
1010100101
1001000001
1010000001
1000000001
1111111111
```

### Map Files Included

- `maps/goods/donut.cub` - Classic donut-shaped maze
- `maps/goods/jail.cub` - Prison-themed map
- `maps/goods/library.cub` - Library environment

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `←` / `→` | Rotate camera |
| `ESC` | Quit |

## Project Structure

```
cub3D/
├── Makefile                    # Compilation rules
├── include/
│   ├── cub3d.h                # Main header
│   ├── game.h                 # Game structures and constants
│   └── vmem.h                 # Virtual memory management
├── src/
│   ├── cub3d.c                # Main entry point
│   ├── execute/
│   │   ├── draw/              # Rendering (raycasting/texture)
│   │   ├── movement/          # Player movement and input handling
│   │   ├── player/            # Player state management
│   │   └── ray/               # Raycasting algorithm
│   ├── parse/                 # Configuration file parsing
│   │   ├── filer/             # File validation
│   │   ├── gnl/               # Get next line (file reading)
│   │   ├── maper/             # Map parsing and validation
│   │   └── error.c            # Error handling
│   ├── libft/                 # Custom C utility functions
│   └── mem/                   # Memory management system
├── lib/
│   └── MLX42/                 # MLX42 graphics library
├── maps/                      # Map configuration files
│   ├── goods/                 # Valid test maps
│   ├── bads/                  # Invalid maps (for testing)
│   └── test/                  # Additional test maps
├── textures/                  # Texture files (.xpm42)
└── docs/
    └── README.md              # This file
```

## Implementation Details

### Core Components

#### Raycasting Algorithm
- Casts rays from the player's position through each pixel of the screen
- Calculates distance to walls using DDA (Digital Differential Analyzer)
- Determines which texture to render based on ray direction
- Applies perspective correction for proper 3D rendering

#### Texture Mapping
- Supports XPM42 format for efficient texture handling
- Correct UV mapping calculation for accurate wall rendering
- Wall height calculation based on distance

#### Player Movement
- Real-time keyboard input handling
- Collision detection with walls
- Smooth camera rotation
- Diagonal movement support

#### Memory Management
- Custom virtual memory system prevents leaks
- Automatic cleanup on program exit
- Tracking of all allocations

## Compilation Notes

- All code follows the 42 School Norm standards
- The project uses MLX42 for all graphics operations
- No external libraries except MLX42 and standard C library
- All functions are reentrant with proper error handling

## Testing

The project includes test maps of varying complexity:

- **Valid maps** (`maps/goods/`) - Maps that should run correctly
- **Invalid maps** (`maps/bads/`) - Edge cases for testing error handling

Run tests with different maps:
```bash
./cub3D maps/goods/donut.cub
./cub3D maps/goods/jail.cub
./cub3D maps/goods/library.cub
```

### Memory Leak Detection

Test for memory leaks using Valgrind:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/goods/donut.cub
```

## Performance Considerations

- Raycasting provides real-time rendering performance
- Optimized for 1920x1080 resolution (adjustable)
- Efficient memory allocation with minimal fragmentation
- No dynamic allocations during the game loop

## Known Limitations

- Map size is limited to the configured dimensions
- Textures must be in XPM42 format
- Sprites/objects not implemented (core requirement excluded)
- No audio system

## Troubleshooting

### Compilation Issues

**Issue**: MLX42 build fails
```bash
# Rebuild MLX42
cd lib/MLX42
mkdir -p build && cd build
cmake .. && make
cd ../../
```

**Issue**: Missing dependencies
```bash
# Reinstall required libraries
# macOS: brew install glfw3 cmake
# Linux: sudo apt-get install libglfw3-dev libx11-dev libglx-dev cmake
```

### Runtime Issues

**Issue**: "Error: Invalid map configuration"
- Verify map file format matches the `.cub` specification
- Ensure all textures are correctly specified with valid paths
- Check that floor (F) and ceiling (C) colors are valid RGB values

**Issue**: Window doesn't display
- Ensure X11 is available (Linux)
- On macOS, verify graphics system support
- Check GLFW3 installation

## Resources & References

- [MLX42 Documentation](https://harm-smits.github.io/42docs/libs/mlx/getting_started.html)
- [Raycasting Algorithm](https://en.wikipedia.org/wiki/Ray_casting)
- Wolfenstein 3D: Classic reference for raycasting games

---

<div align="center">

Made with ☕ at **42 School**

</div>