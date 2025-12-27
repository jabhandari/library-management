# Library Management (Console App)

Small, menu-driven C++ console application for managing library publications.

## Big picture
- Console UI (`Menu.cpp/.h`) separates presentation from domain logic (`Publication`, `Book`).
- Persistence uses a small plain-text record format implemented by classes that implement the `Streamable` interface (`Streamable.h`).
- `LibAppMain_prof.cpp` is a test runner: it copies an `orig` data file into the active data file, forces the date via test globals, constructs `seneca::LibApp`, and calls `app.run()`.

## Key files
- `LibAppMain_prof.cpp` — test harness and data-file copy pattern.
- `LibApp.cpp` / `LibApp.h` — application lifecycle and menu wiring.
- `Menu.cpp` / `Menu.h` — simple console menu helper.
- `Publication.cpp` / `Publication.h`, `Book.cpp` / `Book.h` — domain objects, implement `Streamable`.
- `Streamable.h` / `Streamable.cpp` — I/O contract: `write`, `read`, `conIO`, and stream operators.
- `Date.h` / `Date.cpp` — date utilities; contains test globals: `seneca_test`, `seneca_year`, `seneca_mon`, `seneca_day`.
- `Lib.h` — formatting constants (e.g., `SENECA_TITLE_WIDTH`) and capacities.
- `LibRecsSmall.txt`, `LibRecs.txt` — example data files.

## Project-specific patterns and conventions
- All serializable domain objects implement `Streamable`'s pure virtuals: `write`, `read`, `conIO`, and `operator bool()`.
- `conIO(std::ios&)` determines whether `write/read` produce console-friendly output or compact file records — preserve that behavior when editing I/O.
- `Date` exposes `errCode()` / `dateStatus()` and uses global `seneca_*` variables for deterministic tests; do not rename or remove those globals.
- Formatting widths and limits are defined in `Lib.h` and used for aligned console output.

## Build & run
From the repository root (Windows examples shown):

MinGW / g++ (example):
```bash
g++ -std=c++17 Book.cpp Date.cpp Publication.cpp Streamable.cpp PublicationSelector.cpp Menu.cpp LibApp.cpp LibAppMain_prof.cpp Utils.cpp -o LibApp.exe
./LibApp.exe
```

MSVC (Developer Command Prompt):
```powershell
cl /EHsc /std:c++17 *.cpp
.\LibApp.exe
```

Notes:
- There is no build script in the repo; adjust compile command to your toolchain and OS.

## Test harness and deterministic runs
- `LibAppMain_prof.cpp` sets `seneca_test = true` and forces `seneca_day`, `seneca_mon`, `seneca_year` so runs are repeatable.
- That file also constructs an `original` filename by prefixing `orig` to the chosen data filename and copies its contents into the active data file before running — inspect that copy pattern when debugging data/IO issues.

## Extending the code
- To add a new publication type:
  1. Create a class that implements `Streamable` (implement `write`, `read`, `conIO`, and `operator bool()`).
  2. Update `PublicationSelector.cpp/.h` so the UI can instantiate the new type.
  3. Add test records to `origLibRecs*.txt` if needed.

## Debugging tips
- Compare `LibRecs*.txt` to `Publication::read`/`write` implementations when addressing parse/format bugs.
- Use the test harness (`LibAppMain_prof.cpp`) to run deterministic flows; it will print the final content of the data file to stdout.

## Where to look for examples
- `Publication.h` / `Book.h` — concrete `Streamable` implementation patterns.
- `Streamable.h` — canonical method signatures and operator overloads.
- `Date.h` — shows the global-test mechanism and error codes.


