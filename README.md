# logme CMake Submodule Example

![Example output](view.png)

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

Clone the example and initialize submodules:

```bash
git clone https://github.com/efmsoft/logme_cmake_submodule_example.git
cd logme_cmake_submodule_example
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
