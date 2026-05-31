#!/usr/bin/env bash

set -euo pipefail

EXPECTED="recorrido_neocorp_expected.log"
ACTUAL="recorrido_neocorp_actual.log"

if [[ ! -f "$EXPECTED" ]]; then
  echo "No existe $EXPECTED."
  exit 1
fi

make
./neocorp neocorp.dat -d -l "$ACTUAL" < recorrido_neocorp.cmd >/dev/null
diff -u "$EXPECTED" "$ACTUAL"
echo "Recorrido Neocorp OK."
