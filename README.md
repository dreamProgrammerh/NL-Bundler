# NL Bundler - Namespace Library Toolchain

<div align="center">

**Transform C projects into single-file `.nl` libraries with compile-time namespacing**

[![C17](https://img.shields.io/badge/C-17-blue.svg)](https://en.wikipedia.org/wiki/C17_(C_standard_revision))
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE.md)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)]()

</div>

## 📦 What is NL?

NL (Namespace Library) is a **single-file C library format** that solves dependency hell. Instead of managing multiple `.c` and `.h` files, build systems, and linker flags, you just:

```c
#define NL_Alias mylib_
#define NL_Main 1
#include "library.nl"
```

That's it. No build scripts, no linking, no headaches.

## 🎯 The Problem We Solve

| Traditional C | With NL |
|--------------|---------|
| Multiple .c/.h files | Single .nl file |
| Linker flags | Nothing |
| Symbol collisions | Built-in namespacing |
| Complex build systems | Just copy & include |
| Slow iteration | Header-only performance |

## ✨ Features

- **Single File Distribution** - One `.nl` file = one library
- **Compile-Time Namespacing** - No symbol conflicts, ever
- **Header-Only by Default** - Better compiler optimization
- **Zero Build Dependencies** - No make, cmake, or meson needed
- **Version-Aware** - Built-in version checking
- **Self-Hosting** - NL Bundler written in C, can bundle itself and its core libraries

## 🚀 Quick Start

### Install NL Bundler

```bash
# soon
```

### Bundle Your First Library

```bash
# soon
```

### Use a NL Library

```c
// soon
```

## 📚 NL Library Format

### Structure

```c
// library.nl - Single file containing both API and implementation
#ifndef LIBRARY_NL
#define LIBRARY_NL

// Configuration (user overrides these)
#ifndef NL_Alias
#define NL_Alias lib_      // Default namespace
#endif

#ifndef NL_Main
#define NL_Main 0          // Default to header-only
#endif

// Name mangling macro
#define _A_(name) _CONCAT1_(NL_Alias, name)

// ====================================
// Public API (always included)
// ====================================
void _A_(init)(void);
int _A_(do_something)(int x);

// ====================================
// Implementation (only if NL_Main == 1)
// ====================================
#if NL_Main
void _A_(init)(void) { /* ... */ }
int _A_(do_something)(int x) { return x * 2; }
#endif

#undef NL_Alias
#undef NL_Main
#undef _A_

#endif // LIBRARY_NL
```

### Why This Works

1. **Single inclusion** - The user includes your `.nl` file once
2. **Conditional compilation** - Implementation only compiled when requested
3. **Macro-based prefixing** - All symbols get a unique prefix
4. **No linking** - Everything is in the header, compiler sees it all

## 🛠️ NL Bundler Commands (Not Standard Yet, WILL CHANGE)

```bash
# Build a .nl library from a C project
nlc build ./src -o library.nl --namespace mylib_ --public api.h

# Bundle recursively (include dependencies)
nlc bundle ./project -o project.nl --recursive

# Extract a .nl file back to source
nlc extract library.nl -o ./extracted

# Validate a .nl file
nlc verify library.nl --test test.c

# Show library metadata
nlc info library.nl

# Install a library locally
nlc install https://example.com/awesome.nl

# List installed libraries
nlc list
```

### Configuration File (.nlconfig)

```json
{
  "name": "mylib",
  "version": "1.0.0",
  "namespace": "ml_",
  "public_headers": ["api.h", "types.h"],
  "private_sources": ["internal.c", "helpers.c"],
  "exclude": ["test_*", "*_demo.c"],
  "dependencies": {
    "arena": ">=1.0",
    "string": "~2.3"
  },
  "compile_flags": ["-O2", "-Wall"],
  "system_includes": ["stdint.h", "stdbool.h"]
}
```

## 📁 Library Repository Structure

Each NL library follows a standard layout:

```
library-name/
├── v1.0/                    # Versioned directory
│   ├── src/
│   │   ├── library.c
│   │   └── library.h
│   ├── lib.nl               # Bundled version
│   ├── README.md
│   ├── USAGE.md
│   └── WHATIS.md
├── v1.1/                    # New version
│   └── ...
└── .nlrepo                  # Repository metadata
```

### .nlrepo Format

```ini
Name=arena
Version=1.0.0
Description=Arena allocator with rich functions
Author=Your Name <email@example.com>
License=MIT
Dependencies=none
DefaultNamespace=aa_
PublicHeaders=arena.h, ...
Implementation=arena.c, ...
Website=https://github.com/yourname
```

## 📝 License

MIT License - See [LICENSE](LICENSE.md) for details.

## 🌟 Star History

[![Star History Chart](https://api.star-history.com/svg?repos=dreamProgrammerh/nl-bundler&type=Date)](https://star-history.com/#dreamProgrammerh/nl-bundler&Date)

## 🙏 Acknowledgments

- Inspired by [STB](https://github.com/nothings/stb) single-file libraries
- Namespace technique from [SQLite](https://sqlite.org/amalgamation.html) amalgamation
- Built with pure C17 for maximum compatibility

---

<div align="center">
<b>Made with ❤️ for the C community</b><br>
<i>Stop fighting build systems. Start coding.</i>
</div>