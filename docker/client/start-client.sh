#!/bin/bash
set -e

# Если нужен доступ к X-серверу: на хосте выполните `xhost +local:root` или `xhost +SI:localuser:$USER`
if [ -z "$DISPLAY" ]; then
  echo "WARN: DISPLAY not set. GUI may not appear."
fi

# Определяем исполняемый файл (имя проекта — каталог client)
PROJ_NAME=$(basename "$(pwd)")
if [ -x "./$PROJ_NAME" ]; then
  exec ./"$PROJ_NAME"
fi

# fallback: первый исполняемый файл
EXE=$(find . -maxdepth 1 -type f -perm /111 -printf "%f\n" | head -n1)
if [ -n "$EXE" ]; then
  exec ./"$EXE"
fi

echo "Executable not found. Built files:"
ls -la
exit 1
