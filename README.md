# logme CMake Submodule Example

This repository demonstrates a **minimal and correct** way to integrate
[logme](https://github.com/efmsoft/logme) into a CMake-based C++ project.

The example shows how to:

- use **logme as a git submodule**
- link against **the static logme library**
- enable logging in **Release builds**
- keep the setup simple and reproducible

This repository is intended to be referenced from the **logme wiki**
as a canonical integration example.

---

## Project Layout

```
.
├── CMakeLists.txt
├── src/
│   └── main.cpp
└── external/
    └── logme/        # git submodule
```

The static logme library is added explicitly from:

```
external/logme/logme
```

---

## Setup

Add logme as a git submodule:

```bash
git submodule add https://github.com/efmsoft/logme.git external/logme
git submodule update --init --recursive
```

---

## Build

Linux / macOS:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/example
```

Windows (PowerShell):

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
build\Release\example.exe
```

---

## Key Points

- logme is linked as a **static library**
- logging is enabled in Release builds via:

```cmake
target_compile_definitions(example PRIVATE LOGME_INRELEASE)
```

- no JSON configuration or optional dependencies are required
- this setup is suitable as a starting point for real projects

---

## License

This repository is provided as an example and is released under a
permissive license. See `LICENSE