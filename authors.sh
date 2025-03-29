#!/usr/bin/env bash
_D="$HOME/.cache/bash/deps.sh"; mkdir -p "$(dirname "$_D")" && [[ ! -f $_D ]] && wget -qO "$_D" https://static.sek1.ro/libs-bash/deps/index.sh; source "$_D"
deps_source https://static.sek1.ro/libs-bash/dist/

dist_github_authors vSEK1RO libbasen > AUTHORS