#!/bin/bash
TARGET="$HOME/.config/cd_lab"
mkdir -p "$TARGET"
curl -sL https://github.com/Unknown-Geek/Compiler-Design-Lab/archive/refs/heads/main.tar.gz | tar -xz --strip-components=1 -C "$TARGET"

# Optional shortcut alias
if ! grep -q "alias cdlab=" ~/.bashrc 2>/dev/null; then
    echo "alias cdlab='cd $TARGET'" >> ~/.bashrc
fi

echo "Compiler Design Lab files successfully downloaded to $TARGET"
echo "To open: cd ~/.config/cd_lab (or run 'cdlab' in a new terminal)"
