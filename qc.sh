#!/bin/bash

# Disable history expansion (important because of '!' in folder path)
set +H

# Enable nullglob so globs expand to nothing if no matches
shopt -s nullglob

# Path to the directory of this script
DIR="$(cd "$(dirname "$0")" && pwd)"

# Compiler and flags
CXX=g++
CXXFLAGS="-std=c++17 -Wall -Wextra -I$DIR/SDLLibrary/Core -I$DIR/SDLLibrary/Utils -I$DIR/Levels"

# Gather all source files
SRCS=()
# Add main.cpp
SRCS+=("$DIR/main.cpp")

# SDLLibrary Core files
for file in "$DIR/SDLLibrary/Core/"*.cpp; do
    [ -f "$file" ] && SRCS+=("$file")
done

# SDLLibrary Utils files
for file in "$DIR/SDLLibrary/Utils/"*.cpp; do
    [ -f "$file" ] && SRCS+=("$file")
done

# Levels files
for file in "$DIR/Levels/"*.cpp; do
    [ -f "$file" ] && SRCS+=("$file")
done

# Top-level Utils files (Player, Enemy)
for file in "$DIR/Utils/"*.cpp; do
    [ -f "$file" ] && SRCS+=("$file")
done


# Debug: print all sources to compile
echo "Sources to compile:"
for src in "${SRCS[@]}"; do
    echo "  $src"
done

# Output executable
OUT="$DIR/game"

# SDL2 linker flags
SDLFLAGS="$(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_gfx -lSDL2_ttf"

# Compile and link
echo "Building..."
$CXX "${SRCS[@]}" $CXXFLAGS -o "$OUT" $SDLFLAGS

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Build successful! Running..."
    "$OUT"
else
    echo "Build failed."
fi
