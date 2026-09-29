#!/bin/bash
TARGET="$HOME/.config/cd_lab"
mkdir -p "$TARGET"

# Download and extract archive into TARGET
curl -sL "https://github.com/Unknown-Geek/Compiler-Design-Lab/archive/refs/heads/main.tar.gz" | tar -xz --strip-components=1 -C "$TARGET"

echo ""
echo "Location: $TARGET"
echo ""
