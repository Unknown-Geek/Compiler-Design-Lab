#!/bin/bash
TARGET="$HOME/.config/cd_lab"
mkdir -p "$TARGET"
curl -sL https://github.com/Unknown-Geek/Compiler-Design-Lab/archive/refs/heads/main.tar.gz | tar -xz --strip-components=1 -C "$TARGET"

# Add shortcut alias to bashrc and zshrc
for rc in "$HOME/.bashrc" "$HOME/.zshrc"; do
    if [ -f "$rc" ] && ! grep -q "alias cdlab=" "$rc" 2>/dev/null; then
        echo "alias cdlab='cd $TARGET'" >> "$rc"
    fi
done

echo ""
echo "=========================================="
echo " Compiler Design Lab (CSL411) Setup Done! "
echo " Location: $TARGET"
echo " To use now: cd ~/.config/cd_lab"
echo " Or simply:  cdlab (in any new terminal)"
echo "=========================================="
echo ""
