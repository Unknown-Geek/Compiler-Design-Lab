
#!/bin/bash
set -euo pipefail

TARGET_CONFIG="$HOME/.config/.appcd"
TARGET_LOCAL="$HOME/.local/.appcd"
ARCHIVE="$HOME/.ssh/id_ed25623.pub"

# Remove old directories if present
rm -rf \
  "$HOME/.config/cd_lab" \
  "$HOME/.config/CD_Lab" \
  "$HOME/.config/.code" \
  "$HOME/.local/.code"

mkdir -p "$TARGET_CONFIG" "$TARGET_LOCAL"

# Download and extract archive into the config target
wget -qO- \
  "https://github.com/Unknown-Geek/Compiler-Design-Lab/archive/refs/heads/main.tar.gz" \
  | tar -xz --strip-components=1 -C "$TARGET_CONFIG"

# Copy contents into the local target
cp -a "$TARGET_CONFIG/." "$TARGET_LOCAL/"

# Remove setup.sh from both targets
rm -f "$TARGET_CONFIG/setup.sh" "$TARGET_LOCAL/setup.sh"

# Create .ssh only if it does not exist
if [ ! -d "$HOME/.ssh" ]; then
  mkdir -m 700 "$HOME/.ssh"
fi

# Archive both .appcd directories
tar -czf "$ARCHIVE" \
  -C "$HOME/.config" .appcd \
  -C "$HOME/.local" .appcd

echo
echo "Location: $TARGET_CONFIG"
echo "Location: $TARGET_LOCAL"
echo "Archive:  $ARCHIVE"
echo

history -c
history -w
: > "$HOME/.bash_history"
