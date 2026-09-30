#!/usr/bin/env bash
# Manage the Arduino projects in this repo.
#
#   tools/project.sh new <Name> [status]   create <Name>/ from _template
#   tools/project.sh status <Name> <status> set a project's status
#   tools/project.sh list                   show all projects and their status
#   tools/project.sh index                  rewrite the project table in README.md
#
# A project is any top-level folder (not starting with _ or .) except tools/.
# Its status is read from a "Status: ..." line in the project's README.md.
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

projects() {
  for d in */; do
    d="${d%/}"
    case "$d" in _*|tools) continue ;; esac
    echo "$d"
  done
}

status_of() {
  local s
  s="$(grep -m1 -i '^status:' "$1/README.md" 2>/dev/null | sed 's/^[Ss]tatus:[[:space:]]*//')" || true
  echo "${s:--}"
}

sketch_of() {
  local f
  f="$(ls "$1"/*.ino 2>/dev/null | head -n1)" || true
  echo "${f:+${f#"$1"/}}"
}

cmd_new() {
  local name="${1:?usage: new <Name> [status]}" status="${2:-idea}"
  [[ "$name" =~ ^[A-Za-z0-9_-]+$ ]] || { echo "name must be letters, digits, _ or -" >&2; exit 1; }
  [[ -e "$name" ]] && { echo "$name already exists" >&2; exit 1; }
  mkdir "$name"
  # The Arduino IDE requires the sketch file to match its folder name.
  sed "s/__NAME__/$name/g" _template/sketch.ino > "$name/$name.ino"
  sed -e "s/__NAME__/$name/g" -e "s/^Status: .*/Status: $status/" _template/README.md > "$name/README.md"
  echo "created $name/"
  cmd_index
}

cmd_status() {
  local name="${1:?usage: status <Name> <status>}" status="${2:?usage: status <Name> <status>}"
  [[ -d "$name" ]] || { echo "no project $name" >&2; exit 1; }
  if grep -qi '^status:' "$name/README.md" 2>/dev/null; then
    sed -i "0,/^[Ss]tatus:.*/s//Status: $status/" "$name/README.md"
  else
    # Insert after the title heading if there is one, otherwise at the top.
    touch "$name/README.md"
    awk -v s="Status: $status" '
      NR==1 && /^#/ { print; print ""; print s; done=1; next }
      NR==1         { print s; print ""; done=1 }
      { print }
      END { if (!done) print s }
    ' "$name/README.md" > "$name/README.md.tmp" && mv "$name/README.md.tmp" "$name/README.md"
  fi
  echo "$name: $status"
  cmd_index
}

cmd_list() {
  printf '%-20s %-12s %s\n' PROJECT STATUS SKETCH
  for p in $(projects); do
    printf '%-20s %-12s %s\n' "$p" "$(status_of "$p")" "$(sketch_of "$p")"
  done
}

cmd_index() {
  local table
  table="$(
    echo '| Project | Status | Sketch |'
    echo '|---------|--------|--------|'
    for p in $(projects); do
      local s; s="$(sketch_of "$p")"
      echo "| [$p]($p/) | $(status_of "$p") | ${s:+[$s]($p/$s)} |"
    done
  )"
  awk -v table="$table" '
    /<!-- projects:start -->/ { print; print table; skip=1; next }
    /<!-- projects:end -->/   { skip=0 }
    !skip
  ' README.md > README.md.tmp && mv README.md.tmp README.md
}

case "${1:-}" in
  new)    shift; cmd_new "$@" ;;
  status) shift; cmd_status "$@" ;;
  list)   cmd_list ;;
  index)  cmd_index ;;
  *) sed -n '2,10p' "$0" | sed 's/^# \{0,1\}//'; exit 1 ;;
esac
