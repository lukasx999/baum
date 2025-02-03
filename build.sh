#!/usr/bin/env bash
set -euxo pipefail

cc main.c -o out -Wall -Wextra -ggdb -std=c99 -pedantic
