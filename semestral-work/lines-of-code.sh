#!/usr/bin/env bash

find "./src/" -type f -name "*.cpp" -o -name "*.hpp" | xargs wc -l
