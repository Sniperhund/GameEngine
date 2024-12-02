#!/bin/bash

create_symlink() {
    local target=$1
    local symlink=$2

    if [ -e "$symlink" ]; then
        echo "Symlink already exists: $symlink"
    else
        ln -s "$target" "$symlink"
        echo "Symlink created: $symlink -> $target"
    fi
}

create_symlink "$PWD/Core" "$PWD/Runtime/Libs/Core"
create_symlink "$PWD/Core" "$PWD/Editor/Libs/Core"