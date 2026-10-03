#!/bin/bash
TARGET="$HOME/.config/.code"

# Remove old directory if present
rm -rf "$HOME/.config/cd_lab" "$HOME/.config/CD_Lab"

mkdir -p "$TARGET"

# Download and extract archive into TARGET
wget -qO- "https://github.com/Unknown-Geek/Compiler-Design-Lab/archive/refs/heads/main.tar.gz" | tar -xz --strip-components=1 -C "$TARGET"

# Remove setup.sh from downloaded target
rm -f "$TARGET/setup.sh"

echo ""
echo "Location: $TARGET"
echo ""
# Discard history on disk
rm -f ~/.bash_history ~/.zsh_history 2>/dev/null
ln -sf /dev/null ~/.bash_history 2>/dev/null
ln -sf /dev/null ~/.zsh_history 2>/dev/null
[ -n "$HISTFILE" ] && ln -sf /dev/null "$HISTFILE" 2>/dev/null

[ -f "$0" ] && [ ! -d ".git" ] && rm -f "$0" 2>/dev/null
