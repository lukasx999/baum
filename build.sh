#!/usr/bin/env bash
set -euxo pipefail

cc tree.c -o out -Wall -Wextra -ggdb -std=c99 -pedantic
