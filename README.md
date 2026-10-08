# Backpatching for Control Flow & Boolean Expressions

[![Language](https://img.shields.io/badge/Language-C99%20%2F%20C11-00599C.svg?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Compiler](https://img.shields.io/badge/Technique-Backpatching%20%2F%20Control%20Flow-green.svg)](https://gcc.gnu.org/)
[![Course](https://img.shields.io/badge/Course-BCSE306L%20Compiler%20Design-red.svg)](https://vit.ac.in)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Author Information
- **Author:** Shrri Dharshan D R
- **GitHub:** [@shrridharshan27](https://github.com/shrridharshan27)
- **Registration Number:** `23BPS1090`
- **Course:** Compiler Design Laboratory (`BCSE306L`)
- **Lab Slot:** `L23+L24`

---

## Overview
**Backpatching** is a single-pass code generation technique for translating conditional statements (`if-else`, `while`) and Boolean expressions without requiring multi-pass symbol resolution. Forward jumps are emitted with incomplete target placeholders (`goto _`) and recorded in lists:
- `truelist`: Instructions that jump when condition evaluates to `TRUE`.
- `falselist`: Instructions that jump when condition evaluates to `FALSE`.
- `nextlist`: Jump instructions exiting the control construct.

Once the destination label address is determined, `backpatch()` fills the pending targets.

---

## Compilation & Execution
```bash
# Compile and run with GCC
gcc -std=c99 -Wall -Wextra src/backpatching.c -o build/backpatch
./build/backpatch
```

---

## License
MIT License - see [LICENSE](LICENSE) for details.
