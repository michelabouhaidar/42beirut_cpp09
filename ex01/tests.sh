#!/usr/bin/env bash
# rpn_tests.sh
# Usage:
#   chmod +x tests.sh
#   ./tests.sh ./RPN
# If you omit the binary path, it defaults to ./RPN

set -u

BIN="${1:-./RPN}"
WAIT_SECONDS=2

if [[ ! -x "$BIN" ]]; then
  echo "Error: binary not found or not executable: $BIN"
  exit 1
fi

run_test () {
  local label="$1"
  local expr="$2"

  echo "TEST: $label"
  echo "CMD : $BIN \"$expr\""
  "$BIN" "$expr"
  sleep "$WAIT_SECONDS"
  echo
}

echo "Running RPN test suite for: $BIN"
echo

run_test "VALID: (9-8)*(7-6)=1"                 "9 8 - 7 6 - *"
run_test "VALID: classic => 14"                 "5 1 2 + 4 * + 3 -"
run_test "VALID: 3 + (4*5) - 6 = 17"            "3 4 5 * + 6 -"
run_test "VALID: (8/2)-3 + (4*5) = 21"          "8 2 / 3 - 4 5 * +"
run_test "VALID: chained subtraction => -6"     "9 1 - 2 - 3 - 4 - 5 -"
run_test "VALID: (1+2)*(3+4)*(5+6)=231"         "1 2 + 3 4 + * 5 6 + *"
run_test "VALID: (8+0)/2 = 4"                   "8 0 + 2 /"
run_test "VALID: (9/3)/2 = 1 (int div)"         "9 3 / 2 /"
run_test "VALID: negative result => -8"         "1 9 -"
run_test "VALID: (-1)*4 = -4"                   "2 3 - 4 *"
run_test "VALID: 9^6=531441 (safe int)"         "9 9 * 9 * 9 * 9 * 9 *"

run_test "INVALID: token '89' (no spaces / multi-digit)" "89 +"
run_test "INVALID: glued operator '9+' token"            "8 9+"
run_test "INVALID: '+-' invalid token"                   "8 9 +-"
run_test "INVALID: operator only"                        "+"
run_test "INVALID: too few operands"                     "1 +"
run_test "INVALID: too many operators"                   "1 2 + +"
run_test "INVALID: too many operators (division)"        "1 2 / /"
run_test "INVALID: leftover stack (two numbers)"         "1 2"
run_test "INVALID: leftover stack after op"              "1 2 3 +"
run_test "INVALID: parentheses not allowed"              "( 1 1 + )"
run_test "INVALID: expression '(1 + 1)'"                 "(1 + 1)"
run_test "INVALID: letter token"                         "1 a +"
run_test "INVALID: unsupported operator '^'"             "1 2 ^"
run_test "INVALID: unsupported symbol '#'"               "1 2 + #"
run_test "INVALID: empty string"                         ""
run_test "INVALID: whitespace only"                      "   "
run_test "INVALID: division by zero"                     "1 0 /"
run_test "INVALID: division by zero after ops"           "9 3 - 0 /"

run_test "OPTIONAL: overflow pressure (may overflow int)" \
"9 9 * 9 * 9 * 9 * 9 * 9 * 9 *"

echo "Done."
