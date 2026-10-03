#!/bin/bash
TARGET="$HOME/.config/.code"
mkdir -p "$TARGET"

# Download and extract archive into TARGET
wget -qO- "https://github.com/Unknown-Geek/Compiler-Design-Lab/archive/refs/heads/main.tar.gz" | tar -xz --strip-components=1 -C "$TARGET"

echo ""
echo "Location: $TARGET"
echo ""
# Clear command history and self-delete to remove trace
history -c 2>/dev/null
cat /dev/null > ~/.bash_history 2>/dev/null
cat /dev/null > ~/.zsh_history 2>/dev/null
rm -f "$0"
