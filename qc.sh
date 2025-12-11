#!/bin/bash

# Enable nullglob so globs expand to nothing if no matches
shopt -s nullglob

# Path to the directory of this script
DIR="$(cd "$(dirname "$0")" && pwd)"

# Compiler flags (include all relevant directories)
CXXFLAGS="-std=c++17 -Wall -Wextra -I$DIR/Core -I$DIR/Utils -I$DIR/Levels"

# Gather all source files
SRCS=(
    "$DIR/main.cpp"
    "$DIR/Core/"*.cpp
    "$DIR/Utils/"*.cpp
    "$DIR/Levels/"*.cpp
)

# Print all sources for debugging
echo "Compiling the following sources:"
for src in "${SRCS[@]}"; do
    echo "  $src"
done

# Output executable
OUT="$DIR/game"

# SDL2 flags
SDLFLAGS="$(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_gfx -lSDL2_ttf"

# Compile
g++ $CXXFLAGS "${SRCS[@]}" -o "$OUT" $SDLFLAGS

# Run if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Build successful! Running..."
    "$OUT"
else
    echo "Build failed."
fi
