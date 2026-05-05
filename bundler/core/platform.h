#pragma once

// =============================================
// Operating System
// =============================================

// First, define all OS detection macros with 1 or 0
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#   define OS_WINDOWS 1
#   if defined(_WIN64) || defined(__WIN64__)
#       define OS_WINDOWS_64 1
#       define OS_WINDOWS_32 0
#   else
#       define OS_WINDOWS_64 0
#       define OS_WINDOWS_32 1
#   endif
#else
#   define OS_WINDOWS 0
#endif

// macOS detection (Darwin kernel)
#if defined(__APPLE__) || defined(__MACH__)
#   include <TargetConditionals.h>
#   if TARGET_OS_MAC == 1
#       define OS_MACOS 1
#   else
#       define OS_MACOS 0
#   endif
#   if TARGET_OS_IPHONE == 1
#       define OS_IOS 1
#   else
#       define OS_IOS 0
#   endif
#   if TARGET_OS_TV == 1
#       define OS_TVOS 1
#   else
#       define OS_TVOS 0
#   endif
#   if TARGET_OS_WATCH == 1
#       define OS_WATCHOS 1
#   else
#       define OS_WATCHOS 0
#   endif
#   define OS_DARWIN 1
#else
#   define OS_MACOS 0
#   define OS_IOS 0
#   define OS_TVOS 0
#   define OS_WATCHOS 0
#   define OS_DARWIN 0
#endif

// Linux detection
#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#   define OS_LINUX 1
#   if defined(__ANDROID__) || defined(ANDROID)
#       define OS_ANDROID 1
#   else
#       define OS_ANDROID 0
#   endif
#else
#   define OS_LINUX 0
#   define OS_ANDROID 0
#endif

// BSD family
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#   define OS_FREEBSD 1
#   define OS_BSD 1
#else
#   define OS_FREEBSD 0
#endif

#if defined(__NetBSD__)
#   define OS_NETBSD 1
#   define OS_BSD 1
#else
#   define OS_NETBSD 0
#endif

#if defined(__OpenBSD__)
#   define OS_OPENBSD 1
#   define OS_BSD 1
#else
#   define OS_OPENBSD 0
#endif

#if defined(__DragonFly__)
#   define OS_DRAGONFLY 1
#   define OS_BSD 1
#else
#   define OS_DRAGONFLY 0
#endif

// Set OS_BSD to 0 if no BSD variant was detected
#ifndef OS_BSD
#   define OS_BSD 0
#endif

// Other Unix-like systems
#if defined(__unix__) || defined(__unix) || defined(unix) || defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__) || defined(__MINGW64__)
#   define OS_UNIX 1
#else
#   define OS_UNIX 0
#endif

// Cygwin/Mingw specific
#if defined(__CYGWIN__) || defined(__CYGWIN32__)
#   define OS_CYGWIN 1
#else
#   define OS_CYGWIN 0
#endif

#if defined(__MINGW32__) || defined(__MINGW64__)
#   define OS_MINGW 1
#else
#   define OS_MINGW 0
#endif

// Haiku
#if defined(__HAIKU__)
#   define OS_HAIKU 1
#else
#   define OS_HAIKU 0
#endif

// Solaris/Illumos
#if defined(__sun) || defined(sun)
#   define OS_SOLARIS 1
#   if defined(__SVR4) || defined(__svr4__)
#       define OS_SOLARIS_SVR4 1
#   else
#       define OS_SOLARIS_SVR4 0
#   endif
#else
#   define OS_SOLARIS 0
#   define OS_SOLARIS_SVR4 0
#endif

// HP-UX
#if defined(__hpux) || defined(__hpux__)
#   define OS_HPUX 1
#else
#   define OS_HPUX 0
#endif

// AIX
#if defined(_AIX) || defined(__AIX__) || defined(__aix__)
#   define OS_AIX 1
#else
#   define OS_AIX 0
#endif

// IRIX
#if defined(sgi) || defined(__sgi)
#   define OS_IRIX 1
#else
#   define OS_IRIX 0
#endif

// OS/2
#if defined(__OS2__) || defined(__TOS_OS2__)
#   define OS_OS2 1
#else
#   define OS_OS2 0
#endif

// =============================================
// PUBLIC HELPER MACROS (OS_ prefix + camelCase)
// =============================================

/// @brief Returns 1 if running on Windows (any variant), 0 otherwise
#define OS_isWindows (OS_WINDOWS)

/// @brief Returns 1 if running on 64-bit Windows, 0 otherwise
#define OS_isWindows64 (OS_WINDOWS_64)

/// @brief Returns 1 if running on 32-bit Windows, 0 otherwise
#define OS_isWindows32 (OS_WINDOWS_32)

/// @brief Returns 1 if running on macOS, 0 otherwise
#define OS_isMacOS (OS_MACOS)

/// @brief Returns 1 if running on iOS, 0 otherwise
#define OS_isIOS (OS_IOS)

/// @brief Returns 1 if running on tvOS, 0 otherwise
#define OS_isTVOS (OS_TVOS)

/// @brief Returns 1 if running on watchOS, 0 otherwise
#define OS_isWatchOS (OS_WATCHOS)

/// @brief Returns 1 if running on any Apple platform (macOS, iOS, tvOS, watchOS), 0 otherwise
#define OS_isApple (OS_DARWIN)

/// @brief Returns 1 if running on Linux (non-Android), 0 otherwise
#define OS_isLinux (OS_LINUX && !OS_ANDROID)

/// @brief Returns 1 if running on Android, 0 otherwise
#define OS_isAndroid (OS_ANDROID)

/// @brief Returns 1 if running on any BSD variant, 0 otherwise
#define OS_isBSD (OS_BSD)

/// @brief Returns 1 if running on FreeBSD, 0 otherwise
#define OS_isFreeBSD (OS_FREEBSD)

/// @brief Returns 1 if running on NetBSD, 0 otherwise
#define OS_isNetBSD (OS_NETBSD)

/// @brief Returns 1 if running on OpenBSD, 0 otherwise
#define OS_isOpenBSD (OS_OPENBSD)

/// @brief Returns 1 if running on DragonFly BSD, 0 otherwise
#define OS_isDragonFly (OS_DRAGONFLY)

/// @brief Returns 1 if running under Cygwin environment, 0 otherwise
#define OS_isCygwin (OS_CYGWIN)

/// @brief Returns 1 if running under MinGW environment, 0 otherwise
#define OS_isMinGW (OS_MINGW)

/// @brief Returns 1 if running on Haiku OS, 0 otherwise
#define OS_isHaiku (OS_HAIKU)

/// @brief Returns 1 if running on Solaris/Illumos, 0 otherwise
#define OS_isSolaris (OS_SOLARIS)

/// @brief Returns 1 if running on HP-UX, 0 otherwise
#define OS_isHPUX (OS_HPUX)

/// @brief Returns 1 if running on AIX, 0 otherwise
#define OS_isAIX (OS_AIX)

/// @brief Returns 1 if running on IRIX, 0 otherwise
#define OS_isIRIX (OS_IRIX)

/// @brief Returns 1 if running on OS/2, 0 otherwise
#define OS_isOS2 (OS_OS2)

/// @brief Returns 1 if running on any Unix-like system (including Linux, BSD, macOS, Solaris, HP-UX, AIX, IRIX), 0 otherwise
#define OS_isUnix (OS_UNIX || OS_LINUX || OS_BSD || OS_MACOS || OS_SOLARIS || OS_HPUX || OS_AIX || OS_IRIX)

/// @brief Returns the path separator character ('\\' on Windows, '/' on Unix-like)
#define OS_pathSeparator OS_PATH_SEPARATOR

/// @brief Returns the path separator as a string ("\\" on Windows, "/" on Unix-like)
#define OS_pathSeparatorStr OS_PATH_SEPARATOR_STR

/// @brief Returns the newline sequence ("\r\n" on Windows, "\n" on Unix-like)
#define OS_newline OS_NEWLINE

/// @brief Returns 1 if the system is little-endian, 0 otherwise
#define OS_isLittleEndian (OS_LITTLE_ENDIAN)

/// @brief Returns 1 if the system is big-endian, 0 otherwise
#define OS_isBigEndian (OS_BIG_ENDIAN)

// =============================================
// Architecture
// =============================================
// First, define all architecture macros with explicit 1/0 values
// Start with defaults (all 0)
#define ARCH_X86_64 0
#define ARCH_X86_32 0
#define ARCH_ARM64 0
#define ARCH_ARM32 0
#define ARCH_RISCV64 0
#define ARCH_RISCV32 0
#define ARCH_LOONGARCH64 0
#define ARCH_MIPS64 0
#define ARCH_MIPS32 0
#define ARCH_PPC64 0
#define ARCH_PPC32 0
#define ARCH_S390X 0
#define ARCH_S390 0
#define ARCH_SPARC64 0
#define ARCH_SPARC32 0
#define ARCH_ALPHA 0
#define ARCH_HPPA 0
#define ARCH_M68K 0
#define ARCH_IA64 0

#define ARCH_64BIT 0
#define ARCH_32BIT 0

#define ARCH_FAMILY_X86 0
#define ARCH_FAMILY_ARM 0
#define ARCH_FAMILY_RISCV 0
#define ARCH_FAMILY_LOONGARCH 0
#define ARCH_FAMILY_MIPS 0
#define ARCH_FAMILY_PPC 0
#define ARCH_FAMILY_S390 0
#define ARCH_FAMILY_SPARC 0
#define ARCH_FAMILY_ALPHA 0
#define ARCH_FAMILY_HPPA 0
#define ARCH_FAMILY_M68K 0
#define ARCH_FAMILY_IA64 0

// Architecture capability macros (default to 0)
#define ARCH_HAS_MMX 0
#define ARCH_HAS_SSE 0
#define ARCH_HAS_SSE2 0
#define ARCH_HAS_SSE3 0
#define ARCH_HAS_SSSE3 0
#define ARCH_HAS_SSE4_1 0
#define ARCH_HAS_SSE4_2 0
#define ARCH_HAS_NEON 0
#define ARCH_HAS_AES 0
#define ARCH_HAS_CRC32 0
#define ARCH_HAS_VECTOR 0
#define ARCH_HAS_BITMANIP 0

// Now detect the actual architecture and override the defaults
#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__)
#   undef ARCH_X86_64
#   undef ARCH_64BIT
#   undef ARCH_FAMILY_X86
#   define ARCH_X86_64 1
#   define ARCH_64BIT 1
#   define ARCH_FAMILY_X86 1

#   undef ARCH_HAS_SSE
#   undef ARCH_HAS_SSE2
#   undef ARCH_HAS_SSE3
#   undef ARCH_HAS_SSSE3
#   undef ARCH_HAS_SSE4_1
#   undef ARCH_HAS_SSE4_2
#   define ARCH_HAS_SSE 1
#   define ARCH_HAS_SSE2 1
#   define ARCH_HAS_SSE3 1
#   define ARCH_HAS_SSSE3 1
#   define ARCH_HAS_SSE4_1 1
#   define ARCH_HAS_SSE4_2 1

#elif defined(__i386__) || defined(_M_IX86) || defined(__X86__)
#   undef ARCH_X86_32
#   undef ARCH_32BIT
#   undef ARCH_BITS
#   undef ARCH_FAMILY_X86
#   define ARCH_X86_32 1
#   define ARCH_32BIT 1
#   define ARCH_FAMILY_X86 1

#   undef ARCH_HAS_MMX
#   undef ARCH_HAS_SSE
#   undef ARCH_HAS_SSE2
#   define ARCH_HAS_MMX 1
#   define ARCH_HAS_SSE 1
#   define ARCH_HAS_SSE2 1

#elif defined(__aarch64__) || defined(_M_ARM64)
#   undef ARCH_ARM64
#   undef ARCH_64BIT
#   undef ARCH_FAMILY_ARM
#   define ARCH_ARM64 1
#   define ARCH_64BIT 1
#   define ARCH_FAMILY_ARM 1

#   undef ARCH_HAS_NEON
#   undef ARCH_HAS_AES
#   undef ARCH_HAS_CRC32
#   define ARCH_HAS_NEON 1
#   define ARCH_HAS_AES 1
#   define ARCH_HAS_CRC32 1

#elif defined(__arm__) || defined(_M_ARM) || defined(__thumb__)
#   undef ARCH_ARM32
#   undef ARCH_32BIT
#   undef ARCH_FAMILY_ARM
#   define ARCH_ARM32 1
#   define ARCH_32BIT 1
#   define ARCH_FAMILY_ARM 1

#   if defined(__ARM_NEON) || defined(__ARM_NEON__)
#       undef ARCH_HAS_NEON
#       define ARCH_HAS_NEON 1
#   endif
#   if defined(__ARM_FEATURE_CRC32)
#       undef ARCH_HAS_CRC32
#       define ARCH_HAS_CRC32 1
#   endif

#elif defined(__riscv)
#   if __riscv_xlen == 64
#       undef ARCH_RISCV64
#       undef ARCH_64BIT
#       undef ARCH_FAMILY_RISCV
#       define ARCH_RISCV64 1
#       define ARCH_64BIT 1
#       define ARCH_FAMILY_RISCV 1
#   elif __riscv_xlen == 32
#       undef ARCH_RISCV32
#       undef ARCH_32BIT
#       undef ARCH_FAMILY_RISCV
#       define ARCH_RISCV32 1
#       define ARCH_32BIT 1
#       define ARCH_FAMILY_RISCV 1
#   else
#       error "Unsupported RISC-V XLEN"
#   endif

#   if defined(__riscv_vector)
#       undef ARCH_HAS_VECTOR
#       define ARCH_HAS_VECTOR 1
#   endif
#   if defined(__riscv_zba) || defined(__riscv_zbb) || defined(__riscv_zbc) || defined(__riscv_zbs)
#       undef ARCH_HAS_BITMANIP
#       define ARCH_HAS_BITMANIP 1
#   endif

#elif defined(__loongarch64)
#   undef ARCH_LOONGARCH64
#   undef ARCH_64BIT
#   undef ARCH_FAMILY_LOONGARCH
#   define ARCH_LOONGARCH64 1
#   define ARCH_64BIT 1
#   define ARCH_FAMILY_LOONGARCH 1

#elif defined(__mips__)
#   if defined(__mips64) && (_MIPS_SIM == _ABI64)
#       undef ARCH_MIPS64
#       undef ARCH_64BIT
#       undef ARCH_FAMILY_MIPS
#       define ARCH_MIPS64 1
#       define ARCH_64BIT 1
#       define ARCH_FAMILY_MIPS 1
#   elif defined(__mips__)
#       undef ARCH_MIPS32
#       undef ARCH_32BIT
#       undef ARCH_FAMILY_MIPS
#       define ARCH_MIPS32 1
#       define ARCH_32BIT 1
#       define ARCH_FAMILY_MIPS 1
#   endif

#elif defined(__powerpc64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
#   undef ARCH_PPC64
#   undef ARCH_64BIT
#   undef ARCH_FAMILY_PPC
#   define ARCH_PPC64 1
#   define ARCH_64BIT 1
#   define ARCH_FAMILY_PPC 1

#elif defined(__powerpc__) || defined(__ppc__) || defined(_ARCH_PPC)
#   undef ARCH_PPC32
#   undef ARCH_32BIT
#   undef ARCH_FAMILY_PPC
#   define ARCH_PPC32 1
#   define ARCH_32BIT 1
#   define ARCH_FAMILY_PPC 1

#elif defined(__s390x__)
#   undef ARCH_S390X
#   undef ARCH_64BIT
#   undef ARCH_FAMILY_S390
#   define ARCH_S390X 1
#   define ARCH_64BIT 1
#   define ARCH_FAMILY_S390 1

#elif defined(__s390__)
#   undef ARCH_S390
#   undef ARCH_32BIT
#   undef ARCH_FAMILY_S390
#   define ARCH_S390 1
#   define ARCH_32BIT 1
#   define ARCH_FAMILY_S390 1

#elif defined(__sparc__)
#   if defined(__arch64__)
#       undef ARCH_SPARC64
#       undef ARCH_64BIT
#       undef ARCH_FAMILY_SPARC
#       define ARCH_SPARC64 1
#       define ARCH_64BIT 1
#       define ARCH_FAMILY_SPARC 1
#   else
#       undef ARCH_SPARC32
#       undef ARCH_32BIT
#       undef ARCH_FAMILY_SPARC
#       define ARCH_SPARC32 1
#       define ARCH_32BIT 1
#       define ARCH_FAMILY_SPARC 1
#   endif

#elif defined(__alpha__)
#   undef ARCH_ALPHA
#   undef ARCH_64BIT
#   undef ARCH_FAMILY_ALPHA
#   define ARCH_ALPHA 1
#   define ARCH_64BIT 1
#   define ARCH_FAMILY_ALPHA 1

#elif defined(__hppa__)
#   undef ARCH_HPPA
#   undef ARCH_32BIT
#   undef ARCH_FAMILY_HPPA
#   define ARCH_HPPA 1
#   define ARCH_32BIT 1
#   define ARCH_FAMILY_HPPA 1

#elif defined(__m68k__)
#   undef ARCH_M68K
#   undef ARCH_32BIT
#   undef ARCH_FAMILY_M68K
#   define ARCH_M68K 1
#   define ARCH_32BIT 1
#   define ARCH_FAMILY_M68K 1

#elif defined(__ia64__) || defined(_M_IA64)
#   undef ARCH_IA64
#   undef ARCH_64BIT
#   undef ARCH_FAMILY_IA64
#   define ARCH_IA64 1
#   define ARCH_64BIT 1
#   define ARCH_FAMILY_IA64 1

#else
#   error "Unsupported or unknown architecture"
#endif

#if ARCH_64BIT
#   define ARCH_BITS 64
#else
#   define ARCH_BITS 32
#endif

// =============================================
// PUBLIC HELPER MACROS (ARCH_ prefix + camelCase)
// =============================================

/// @brief Returns 1 if targeting 64-bit architecture, 0 otherwise
#define ARCH_is64Bit (ARCH_64BIT)

/// @brief Returns 1 if targeting 32-bit architecture, 0 otherwise
#define ARCH_is32Bit (ARCH_32BIT)

/// @brief Returns the architecture bitness (64 or 32)
#define ARCH_bits (ARCH_BITS)

/// @brief Returns 1 if architecture is x86/x86-64 family, 0 otherwise
#define ARCH_isX86 (ARCH_FAMILY_X86)

/// @brief Returns 1 if architecture is ARM family, 0 otherwise
#define ARCH_isARM (ARCH_FAMILY_ARM)

/// @brief Returns 1 if architecture is RISC-V family, 0 otherwise
#define ARCH_isRISCV (ARCH_FAMILY_RISCV)

/// @brief Returns 1 if architecture is LoongArch family, 0 otherwise
#define ARCH_isLoongArch (ARCH_FAMILY_LOONGARCH)

/// @brief Returns 1 if architecture is MIPS family, 0 otherwise
#define ARCH_isMIPS (ARCH_FAMILY_MIPS)

/// @brief Returns 1 if architecture is PowerPC family, 0 otherwise
#define ARCH_isPPC (ARCH_FAMILY_PPC)

/// @brief Returns 1 if architecture is IBM S/390 family, 0 otherwise
#define ARCH_isS390Family (ARCH_FAMILY_S390)

/// @brief Returns 1 if architecture is SPARC family, 0 otherwise
#define ARCH_isSPARC (ARCH_FAMILY_SPARC)

/// @brief Returns 1 if architecture is DEC Alpha, 0 otherwise
#define ARCH_isAlpha (ARCH_FAMILY_ALPHA)

/// @brief Returns 1 if architecture is HP PA-RISC, 0 otherwise
#define ARCH_isHPPA (ARCH_FAMILY_HPPA)

/// @brief Returns 1 if architecture is Motorola 68k, 0 otherwise
#define ARCH_isM68K (ARCH_FAMILY_M68K)

/// @brief Returns 1 if architecture is Intel Itanium, 0 otherwise
#define ARCH_isIA64 (ARCH_FAMILY_IA64)

/// @brief Returns 1 if architecture is x86-64, 0 otherwise
#define ARCH_isX86_64 (ARCH_X86_64)

/// @brief Returns 1 if architecture is x86-32, 0 otherwise
#define ARCH_isX86_32 (ARCH_X86_32)

/// @brief Returns 1 if architecture is ARM64/AArch64, 0 otherwise
#define ARCH_isARM64 (ARCH_ARM64)

/// @brief Returns 1 if architecture is ARM32, 0 otherwise
#define ARCH_isARM32 (ARCH_ARM32)

/// @brief Returns 1 if architecture is RISC-V 64-bit, 0 otherwise
#define ARCH_isRISCV64 (ARCH_RISCV64)

/// @brief Returns 1 if architecture is RISC-V 32-bit, 0 otherwise
#define ARCH_isRISCV32 (ARCH_RISCV32)

/// @brief Returns 1 if architecture is LoongArch 64-bit, 0 otherwise
#define ARCH_isLoongArch64 (ARCH_LOONGARCH64)

/// @brief Returns 1 if architecture is MIPS 64-bit, 0 otherwise
#define ARCH_isMIPS64 (ARCH_MIPS64)

/// @brief Returns 1 if architecture is MIPS 32-bit, 0 otherwise
#define ARCH_isMIPS32 (ARCH_MIPS32)

/// @brief Returns 1 if architecture is PowerPC 64-bit, 0 otherwise
#define ARCH_isPPC64 (ARCH_PPC64)

/// @brief Returns 1 if architecture is PowerPC 32-bit, 0 otherwise
#define ARCH_isPPC32 (ARCH_PPC32)

/// @brief Returns 1 if architecture is IBM S/390x 64-bit, 0 otherwise
#define ARCH_isS390X (ARCH_S390X)

/// @brief Returns 1 if architecture is IBM S/390 32-bit, 0 otherwise
#define ARCH_isS390 (ARCH_S390)

/// @brief Returns 1 if architecture is SPARC 64-bit, 0 otherwise
#define ARCH_isSPARC64 (ARCH_SPARC64)

/// @brief Returns 1 if architecture is SPARC 32-bit, 0 otherwise
#define ARCH_isSPARC32 (ARCH_SPARC32)

/// @brief Returns 1 if CPU supports MMX instructions, 0 otherwise
#define ARCH_hasMMX (ARCH_HAS_MMX)

/// @brief Returns 1 if CPU supports SSE instructions, 0 otherwise
#define ARCH_hasSSE (ARCH_HAS_SSE)

/// @brief Returns 1 if CPU supports SSE2 instructions, 0 otherwise
#define ARCH_hasSSE2 (ARCH_HAS_SSE2)

/// @brief Returns 1 if CPU supports SSE3 instructions, 0 otherwise
#define ARCH_hasSSE3 (ARCH_HAS_SSE3)

/// @brief Returns 1 if CPU supports SSSE3 instructions, 0 otherwise
#define ARCH_hasSSSE3 (ARCH_HAS_SSSE3)

/// @brief Returns 1 if CPU supports SSE4.1 instructions, 0 otherwise
#define ARCH_hasSSE4_1 (ARCH_HAS_SSE4_1)

/// @brief Returns 1 if CPU supports SSE4.2 instructions, 0 otherwise
#define ARCH_hasSSE4_2 (ARCH_HAS_SSE4_2)

/// @brief Returns 1 if CPU supports NEON SIMD instructions (ARM), 0 otherwise
#define ARCH_hasNEON (ARCH_HAS_NEON)

/// @brief Returns 1 if CPU supports AES acceleration, 0 otherwise
#define ARCH_hasAES (ARCH_HAS_AES)

/// @brief Returns 1 if CPU supports CRC32 instructions, 0 otherwise
#define ARCH_hasCRC32 (ARCH_HAS_CRC32)

/// @brief Returns 1 if CPU supports vector/SIMD instructions (RISC-V V extension), 0 otherwise
#define ARCH_hasVector (ARCH_HAS_VECTOR)

/// @brief Returns 1 if CPU supports bit manipulation instructions (RISC-V Zb* extensions), 0 otherwise
#define ARCH_hasBitManip (ARCH_HAS_BITMANIP)

// =============================================
// Sanity Checks
// =============================================

// Check for supported platforms
#if !OS_isWindows && !OS_isApple && !OS_isLinux && !OS_isBSD && !OS_isAndroid
#   if OS_isUnix
#       pragma message "Warning: Building for unknown Unix-like system - proceed with caution"
#   else
#       error "Unsupported or unknown operating system"
#   endif
#endif

// Check if at least one architecture was detected
#if !ARCH_isX86 && !ARCH_isARM && !ARCH_isRISCV && !ARCH_isLoongArch && \
    !ARCH_isMIPS && !ARCH_isPPC && !ARCH_isS390 && !ARCH_isSPARC && \
    !ARCH_isAlpha && !ARCH_isHPPA && !ARCH_isM68K && !ARCH_isIA64
#   error "No architecture detected - this should not happen"
#endif

// =============================================
// Compiler Detection
// =============================================

// First, define all compiler detection macros with explicit 1/0 values
#define COMPILER_GCC 0
#define COMPILER_CLANG 0
#define COMPILER_MSVC 0
#define COMPILER_ICC 0           // Intel Classic Compiler
#define COMPILER_ICX 0           // Intel LLVM-based Compiler (ICX/DPC++)
#define COMPILER_MINGW 0
#define COMPILER_CYGWIN 0
#define COMPILER_TINYC 0
#define COMPILER_PGI 0           // PGI/NVIDIA HPC SDK
#define COMPILER_SUNPRO 0        // Oracle Solaris Studio
#define COMPILER_IBMXL 0         // IBM XL C/C++
#define COMPILER_ARMCC 0         // ARM Compiler 5/6
#define COMPILER_EMSCRIPTEN 0
#define COMPILER_WATCOM 0
#define COMPILER_BORLAND 0
#define COMPILER_GHS 0           // Green Hills Software

// Compiler version components
#define COMPILER_VERSION_MAJOR 0
#define COMPILER_VERSION_MINOR 0
#define COMPILER_VERSION_PATCH 0

// Detect GCC
#if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__INTEL_LLVM_COMPILER)
#   undef COMPILER_GCC
#   define COMPILER_GCC 1
#   undef COMPILER_VERSION_MAJOR
#   undef COMPILER_VERSION_MINOR
#   undef COMPILER_VERSION_PATCH
#   define COMPILER_VERSION_MAJOR __GNUC__
#   define COMPILER_VERSION_MINOR __GNUC_MINOR__
#   define COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
#endif

// Detect Clang (including Apple Clang)
#if defined(__clang__) || defined(__CLANG__)
#   undef COMPILER_CLANG
#   define COMPILER_CLANG 1
#   undef COMPILER_VERSION_MAJOR
#   undef COMPILER_VERSION_MINOR
#   undef COMPILER_VERSION_PATCH
#   define COMPILER_VERSION_MAJOR __clang_major__
#   define COMPILER_VERSION_MINOR __clang_minor__
#   define COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

// Detect MSVC
#if defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)
#   undef COMPILER_MSVC
#   define COMPILER_MSVC 1
#   undef COMPILER_VERSION_MAJOR
#   undef COMPILER_VERSION_MINOR
#   undef COMPILER_VERSION_PATCH
#   // MSVC version encoding: _MSC_VER = MMNNBBBB (Major Minor Build)
#   define COMPILER_VERSION_MAJOR (_MSC_VER / 100)
#   define COMPILER_VERSION_MINOR (_MSC_VER % 100)
#   define COMPILER_VERSION_PATCH 0
#endif

// Detect Intel Classic Compiler (ICC)
#if defined(__INTEL_COMPILER) && !defined(__INTEL_LLVM_COMPILER)
#   undef COMPILER_ICC
#   define COMPILER_ICC 1
#   undef COMPILER_VERSION_MAJOR
#   undef COMPILER_VERSION_MINOR
#   undef COMPILER_VERSION_PATCH
#   define COMPILER_VERSION_MAJOR __INTEL_COMPILER / 100
#   define COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100)
#   define COMPILER_VERSION_PATCH 0
#endif

// Detect Intel LLVM-based Compiler (ICX/DPC++)
#if defined(__INTEL_LLVM_COMPILER)
#   undef COMPILER_ICX
#   define COMPILER_ICX 1
#   undef COMPILER_VERSION_MAJOR
#   undef COMPILER_VERSION_MINOR
#   undef COMPILER_VERSION_PATCH
#   define COMPILER_VERSION_MAJOR __INTEL_LLVM_COMPILER / 100
#   define COMPILER_VERSION_MINOR (__INTEL_LLVM_COMPILER % 100)
#   define COMPILER_VERSION_PATCH 0
#endif

// Detect MinGW (must be after GCC detection)
#if defined(__MINGW32__) || defined(__MINGW64__)
#   undef COMPILER_MINGW
#   define COMPILER_MINGW 1
#endif

// Detect Cygwin GCC
#if defined(__CYGWIN__) && defined(__GNUC__)
#   undef COMPILER_CYGWIN
#   define COMPILER_CYGWIN 1
#endif

// Detect TinyCC
#if defined(__TINYC__)
#   undef COMPILER_TINYC
#   define COMPILER_TINYC 1
#endif

// Detect PGI/NVIDIA HPC SDK
#if defined(__PGI) || defined(__PGIC__) || defined(__NVCOMPILER)
#   undef COMPILER_PGI
#   define COMPILER_PGI 1
#endif

// Detect Oracle Solaris Studio
#if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#   undef COMPILER_SUNPRO
#   define COMPILER_SUNPRO 1
#endif

// Detect IBM XL C/C++
#if defined(__IBMC__) || defined(__IBMCPP__)
#   undef COMPILER_IBMXL
#   define COMPILER_IBMXL 1
#endif

// Detect ARM Compiler
#if defined(__ARMCC_VERSION)
#   undef COMPILER_ARMCC
#   define COMPILER_ARMCC 1
#endif

// Detect Emscripten
#if defined(__EMSCRIPTEN__)
#   undef COMPILER_EMSCRIPTEN
#   define COMPILER_EMSCRIPTEN 1
#endif

// Detect Watcom
#if defined(__WATCOMC__)
#   undef COMPILER_WATCOM
#   define COMPILER_WATCOM 1
#endif

// Detect Borland
#if defined(__BORLANDC__)
#   undef COMPILER_BORLAND
#   define COMPILER_BORLAND 1
#endif

// Detect Green Hills Software
#if defined(__ghs__)
#   undef COMPILER_GHS
#   define COMPILER_GHS 1
#endif

// =============================================
// PUBLIC COMPILER MACROS (COMPILER_ prefix + camelCase)
// =============================================

/// @brief Returns 1 if compiling with GCC (not Clang or Intel), 0 otherwise
#define COMPILER_isGCC (COMPILER_GCC)

/// @brief Returns 1 if compiling with Clang (including Apple Clang), 0 otherwise
#define COMPILER_isClang (COMPILER_CLANG)

/// @brief Returns 1 if compiling with Microsoft Visual C++, 0 otherwise
#define COMPILER_isMSVC (COMPILER_MSVC)

/// @brief Returns 1 if compiling with Intel Classic Compiler (ICC), 0 otherwise
#define COMPILER_isICC (COMPILER_ICC)

/// @brief Returns 1 if compiling with Intel LLVM-based Compiler (ICX/DPC++), 0 otherwise
#define COMPILER_isICX (COMPILER_ICX)

/// @brief Returns 1 if compiling with MinGW GCC, 0 otherwise
#define COMPILER_isMinGW (COMPILER_MINGW)

/// @brief Returns 1 if compiling with Cygwin GCC, 0 otherwise
#define COMPILER_isCygwin (COMPILER_CYGWIN)

/// @brief Returns 1 if compiling with TinyCC, 0 otherwise
#define COMPILER_isTinyCC (COMPILER_TINYC)

/// @brief Returns 1 if compiling with PGI/NVIDIA HPC SDK, 0 otherwise
#define COMPILER_isPGI (COMPILER_PGI)

/// @brief Returns 1 if compiling with Oracle Solaris Studio, 0 otherwise
#define COMPILER_isSunPro (COMPILER_SUNPRO)

/// @brief Returns 1 if compiling with IBM XL C/C++, 0 otherwise
#define COMPILER_isIBMXL (COMPILER_IBMXL)

/// @brief Returns 1 if compiling with ARM Compiler (5/6), 0 otherwise
#define COMPILER_isARMCC (COMPILER_ARMCC)

/// @brief Returns 1 if compiling with Emscripten (WebAssembly), 0 otherwise
#define COMPILER_isEmscripten (COMPILER_EMSCRIPTEN)

/// @brief Returns 1 if compiling with Open Watcom, 0 otherwise
#define COMPILER_isWatcom (COMPILER_WATCOM)

/// @brief Returns 1 if compiling with Borland C++, 0 otherwise
#define COMPILER_isBorland (COMPILER_BORLAND)

/// @brief Returns 1 if compiling with Green Hills Software compiler, 0 otherwise
#define COMPILER_isGHS (COMPILER_GHS)

/// @brief Returns 1 if compiler is any Intel compiler (ICC or ICX), 0 otherwise
#define COMPILER_isIntel (COMPILER_ICC || COMPILER_ICX)

/// @brief Returns 1 if compiler is GCC-compatible (GCC, Clang, Intel, MinGW, Cygwin), 0 otherwise
#define COMPILER_isGNUCCompatible (COMPILER_GCC || COMPILER_CLANG || COMPILER_ICC || COMPILER_ICX || COMPILER_MINGW || COMPILER_CYGWIN)

/// @brief Returns compiler major version (e.g., 9 for GCC 9.3.0), 0 if unknown
#define COMPILER_versionMajor COMPILER_VERSION_MAJOR

/// @brief Returns compiler minor version (e.g., 3 for GCC 9.3.0), 0 if unknown
#define COMPILER_versionMinor COMPILER_VERSION_MINOR

/// @brief Returns compiler patch version (e.g., 0 for GCC 9.3.0), 0 if unknown
#define COMPILER_versionPatch COMPILER_VERSION_PATCH

/// @brief Returns compiler version as a single number (major*10000 + minor*100 + patch), 0 if unknown
#define COMPILER_versionInteger (COMPILER_VERSION_MAJOR * 10000 + COMPILER_VERSION_MINOR * 100 + COMPILER_VERSION_PATCH)

// =============================================
// Language Detection
// =============================================

#define LANG_C 0
#define LANG_CPP 0
#define LANG_OBJC 0
#define LANG_OBJCPP 0
#define LANG_CUDA 0
#define LANG_HIP 0
#define LANG_OPENCL 0

// Detect C (most reliable: __STDC__ is defined, __cplusplus is NOT defined)
// Also check for _STDC_C_VERSION which is more reliable than just __STDC__
#if defined(__STDC__) && !defined(__cplusplus) && !defined(__OBJC__)
#   undef LANG_C
#   define LANG_C 1
#endif

// Fallback: If we're not in C++ mode and not in ObjC mode, assume C
// This catches cases where __STDC__ might not be defined (some compilers)
#if !defined(__cplusplus) && !defined(__OBJC__) && !defined(LANG_C)
#   undef LANG_C
#   define LANG_C 1
#endif

// Detect C++ - check for __cplusplus OR _CPPLIB_VER OR _LIBCPP_VERSION
#if defined(__cplusplus) || defined(_CPPLIB_VER) || defined(_LIBCPP_VERSION) || defined(__cpp_lib_) || defined(__cpp_)
#   undef LANG_CPP
#   define LANG_CPP 1
#endif

// Detect Objective-C - Multiple macros to check
#if defined(__OBJC__) || defined(__OBJC2__) || (defined(__clang__) && defined(__OBJC__))
#   if !defined(__cplusplus)
#       undef LANG_OBJC
#       define LANG_OBJC 1
#   else
#       undef LANG_OBJCPP
#       define LANG_OBJCPP 1
#   endif
#endif

// Detect CUDA
#if defined(__CUDACC__) || defined(__CUDA__) || defined(__CUDA_ARCH__)
#   undef LANG_CUDA
#   define LANG_CUDA 1
#endif

// Detect HIP (AMD GPU)
#if defined(__HIPCC__) || defined(__HIP__) || defined(__HIP_ARCH__)
#   undef LANG_HIP
#   define LANG_HIP 1
#endif

// Detect OpenCL
#if defined(__OPENCL_VERSION__) || defined(__OPENCL_C_VERSION__)
#   undef LANG_OPENCL
#   define LANG_OPENCL 1
#endif

// =============================================
// PUBLIC LANGUAGE MACROS (LANG_ prefix + camelCase)
// =============================================

/// @brief Returns 1 if compiling as C (not C++, not Objective-C), 0 otherwise
#define LANG_isC (LANG_C)

/// @brief Returns 1 if compiling as C++, 0 otherwise
#define LANG_isCPP (LANG_CPP)

/// @brief Returns 1 if compiling as Objective-C, 0 otherwise
#define LANG_isObjC (LANG_OBJC)

/// @brief Returns 1 if compiling as Objective-C++, 0 otherwise
#define LANG_isObjCPP (LANG_OBJCPP)

/// @brief Returns 1 if compiling as CUDA (device or host), 0 otherwise
#define LANG_isCUDA (LANG_CUDA)

/// @brief Returns 1 if compiling as HIP (AMD GPU), 0 otherwise
#define LANG_isHIP (LANG_HIP)

/// @brief Returns 1 if compiling as OpenCL kernel, 0 otherwise
#define LANG_isOpenCL (LANG_OPENCL)

/// @brief Returns 1 if compiling as a C-family language (C, C++, ObjC, ObjC++), 0 otherwise
#define LANG_isCFamily (LANG_C || LANG_CPP || LANG_OBJC || LANG_OBJCPP)

// =============================================
// C Standard Version Detection (FIXED)
// =============================================

#define STD_C_VERSION 0
#define STD_C_VERSION_STR "unknown"

// Detect C standard version
#if defined(__STDC__) && !defined(__cplusplus)
    
    // Check for explicit __STDC_VERSION__ (C99 and later)
    #if defined(__STDC_VERSION__)
        #undef STD_C_VERSION
        #undef STD_C_VERSION_STR
        
        #if __STDC_VERSION__ >= 202311L
            #define STD_C_VERSION 202311L
            #define STD_C_VERSION_STR "C23"
        #elif __STDC_VERSION__ >= 201710L
            #define STD_C_VERSION 201710L
            #define STD_C_VERSION_STR "C17"
        #elif __STDC_VERSION__ >= 201112L
            #define STD_C_VERSION 201112L
            #define STD_C_VERSION_STR "C11"
        #elif __STDC_VERSION__ >= 199901L
            #define STD_C_VERSION 199901L
            #define STD_C_VERSION_STR "C99"
        #elif __STDC_VERSION__ >= 199409L
            #define STD_C_VERSION 199409L
            #define STD_C_VERSION_STR "C94"
        #else
            #define STD_C_VERSION 199001L
            #define STD_C_VERSION_STR "C90"
        #endif
        
    // No __STDC_VERSION__ means pre-C99 (C89/C90)
    #else
        #undef STD_C_VERSION
        #undef STD_C_VERSION_STR
        #define STD_C_VERSION 199001L
        #define STD_C_VERSION_STR "C90"
    #endif
    
// For compilers that don't define __STDC__ but are C compilers
#elif !defined(__cplusplus) && !defined(__OBJC__)
    #undef STD_C_VERSION
    #undef STD_C_VERSION_STR
    #define STD_C_VERSION 199001L
    #define STD_C_VERSION_STR "C90 (assumed)"
#endif

// =============================================
// PUBLIC C STANDARD MACROS (STD_ prefix + camelCase)
// =============================================

/// @brief Returns the C standard version as a long (e.g., 201112L for C11), 0 if not C
#define STD_cVersion (STD_C_VERSION)

/// @brief Returns the C standard version as a string (e.g., "C11"), "unknown" if not C
#define STD_cVersionStr (STD_C_VERSION_STR)

/// @brief Returns 1 if compiling with C99 or later, 0 otherwise
#define STD_hasC99 (STD_C_VERSION >= 199901L)

/// @brief Returns 1 if compiling with C11 or later, 0 otherwise
#define STD_hasC11 (STD_C_VERSION >= 201112L)

/// @brief Returns 1 if compiling with C17 or later, 0 otherwise
#define STD_hasC17 (STD_C_VERSION >= 201710L)

/// @brief Returns 1 if compiling with C23 or later, 0 otherwise
#define STD_hasC23 (STD_C_VERSION >= 202311L)

// =============================================
// C++ Standard Version Detection (FIXED)
// =============================================

// C++ standard version detection
#define STD_CPP_VERSION 0
#define STD_CPP_VERSION_STR "unknown"

// Only detect C++ if we're actually in C++ mode
#if defined(__cplusplus)
#   undef STD_CPP_VERSION
#   undef STD_CPP_VERSION_STR

#   if __cplusplus >= 202600L
#       define STD_CPP_VERSION 202600L
#       define STD_CPP_VERSION_STR "C++26"
#   elif __cplusplus >= 202302L
#       define STD_CPP_VERSION 202302L
#       define STD_CPP_VERSION_STR "C++23"
#   elif __cplusplus >= 202002L
#       define STD_CPP_VERSION 202002L
#       define STD_CPP_VERSION_STR "C++20"
#   elif __cplusplus >= 201703L
#       define STD_CPP_VERSION 201703L
#       define STD_CPP_VERSION_STR "C++17"
#   elif __cplusplus >= 201402L
#       define STD_CPP_VERSION 201402L
#       define STD_CPP_VERSION_STR "C++14"
#   elif __cplusplus >= 201103L
#       define STD_CPP_VERSION 201103L
#       define STD_CPP_VERSION_STR "C++11"
#   elif __cplusplus >= 199711L
#       define STD_CPP_VERSION 199711L
#       define STD_CPP_VERSION_STR "C++98/03"
#   endif
#endif

// =============================================
// PUBLIC C++ STANDARD MACROS (STD_ prefix + camelCase)
// =============================================

/// @brief Returns the C++ standard version as a long (e.g., 201703L for C++17), 0 if not C++
#define STD_cppVersion (STD_CPP_VERSION)

/// @brief Returns the C++ standard version as a string (e.g., "C++17"), "unknown" if not C++
#define STD_cppVersionStr (STD_CPP_VERSION_STR)

/// @brief Returns 1 if compiling with C++11 or later, 0 otherwise
#define STD_hasCPP11 (STD_CPP_VERSION >= 201103L)

/// @brief Returns 1 if compiling with C++14 or later, 0 otherwise
#define STD_hasCPP14 (STD_CPP_VERSION >= 201402L)

/// @brief Returns 1 if compiling with C++17 or later, 0 otherwise
#define STD_hasCPP17 (STD_CPP_VERSION >= 201703L)

/// @brief Returns 1 if compiling with C++20 or later, 0 otherwise
#define STD_hasCPP20 (STD_CPP_VERSION >= 202002L)

/// @brief Returns 1 if compiling with C++23 or later, 0 otherwise
#define STD_hasCPP23 (STD_CPP_VERSION >= 202302L)

/// @brief Returns 1 if compiling with C++26 or later, 0 otherwise
#define STD_hasCPP26 (STD_CPP_VERSION >= 202600L)

// =============================================
// Compiler Feature Macros
// =============================================

/// @brief Returns 1 if the compiler supports C++ attributes ([[...]]), 0 otherwise
#define COMPILER_hasCppAttributes (LANG_CPP && STD_hasCPP11)

/// @brief Returns 1 if the compiler supports C++11's nullptr, 0 otherwise
#define COMPILER_hasNullptr (LANG_CPP && STD_hasCPP11)

/// @brief Returns 1 if the compiler supports C++11's constexpr, 0 otherwise
#define COMPILER_hasConstexpr (LANG_CPP && STD_hasCPP11)

/// @brief Returns 1 if the compiler supports C++11's static_assert, 0 otherwise
#define COMPILER_hasStaticAssert (LANG_CPP && STD_hasCPP11) || (LANG_C && __STDC_VERSION__ >= 201112L)

/// @brief Returns 1 if the compiler supports C++11's override/final specifiers, 0 otherwise
#define COMPILER_hasOverride (LANG_CPP && STD_hasCPP11)

/// @brief Returns 1 if the compiler supports C++14's relaxed constexpr, 0 otherwise
#define COMPILER_hasRelaxedConstexpr (LANG_CPP && STD_hasCPP14)

/// @brief Returns 1 if the compiler supports C++17's if constexpr, 0 otherwise
#define COMPILER_hasIfConstexpr (LANG_CPP && STD_hasCPP17)

/// @brief Returns 1 if the compiler supports C++17's structured bindings, 0 otherwise
#define COMPILER_hasStructuredBindings (LANG_CPP && STD_hasCPP17)

/// @brief Returns 1 if the compiler supports C++20's concepts, 0 otherwise
#define COMPILER_hasConcepts (LANG_CPP && STD_hasCPP20)

/// @brief Returns 1 if the compiler supports C++20's three-way comparison (<=>), 0 otherwise
#define COMPILER_hasSpaceship (LANG_CPP && STD_hasCPP20)

/// @brief Returns 1 if the compiler supports __attribute__((...)) (GCC-style), 0 otherwise
#define COMPILER_hasGccAttribute (COMPILER_isGNUCCompatible || COMPILER_isClang)

/// @brief Returns 1 if the compiler supports __declspec(...) (MSVC-style), 0 otherwise
#define COMPILER_hasDeclspec (COMPILER_isMSVC || COMPILER_isIntel || (COMPILER_isGNUCCompatible && defined(__declspec)))

/// @brief Returns 1 if the compiler supports #pragma once, 0 otherwise
#define COMPILER_hasPragmaOnce 1  // Supported by practically all modern compilers

/// @brief Returns 1 if the compiler supports __builtin_expect, 0 otherwise
#define COMPILER_hasBuiltinExpect (COMPILER_isGNUCCompatible || COMPILER_isClang)

/// @brief Returns 1 if the compiler supports __builtin_unreachable, 0 otherwise
#define COMPILER_hasBuiltinUnreachable (COMPILER_isGNUCCompatible || COMPILER_isClang || COMPILER_isMSVC)

/// @brief Returns 1 if the compiler supports __FUNCTION__ macro, 0 otherwise
#define COMPILER_hasFunctionMacro 1  // All modern compilers support this

/// @brief Returns 1 if the compiler supports __PRETTY_FUNCTION__ (GCC/Clang), 0 otherwise
#define COMPILER_hasPrettyFunction (COMPILER_isGNUCCompatible)

/// @brief Returns 1 if the compiler supports __FUNCSIG__ (MSVC), 0 otherwise
#define COMPILER_hasFuncSig (COMPILER_isMSVC)

// =============================================
// Version Helper Macros
// =============================================

/// @brief Converts a year-based version (YYYY) to a standardized version integer
/// @details Example: STD_VERSION_GEN(2023) -> 20230000
///          This preserves the year in the high bits for easy comparison
#define STD_VERSION_GEN(year) ((year) * 10000)

/// @brief Converts a version with year and month (YYYYMM) to a standardized version integer
/// @details Example: STD_VERSION_FULL(2023, 6) -> 20230600
#define STD_VERSION_FULL(year, month) ((year) * 10000 + (month) * 100)

/// @brief Converts a version with year, month, and patch (YYYYMMPP) to a standardized version integer
/// @details Example: STD_VERSION_PATCH(2023, 6, 15) -> 20230615
#define STD_VERSION_PATCH(year, month, patch) ((year) * 10000 + (month) * 100 + (patch))

/// @brief Extracts the year component from a version integer
/// @details Example: STD_VERSION_YEAR(20230615) -> 2023
#define STD_VERSION_YEAR(version) ((version) / 10000)

/// @brief Extracts the month component from a version integer
/// @details Example: STD_VERSION_MONTH(20230615) -> 6
#define STD_VERSION_MONTH(version) (((version) / 100) % 100)

/// @brief Extracts the patch component from a version integer
/// @details Example: STD_VERSION_PATCH_NUM(20230615) -> 15
#define STD_VERSION_PATCH_NUM(version) ((version) % 100)

/// @brief Compares two versions by year only (ignores month and patch)
/// @details Returns 1 if v1_year > v2_year, 0 if equal, -1 if less
///          Usage: STD_VERSION_CMP_YEAR(2023, 2024) -> -1
#define STD_VERSION_CMP_YEAR(v1, v2) \
    (((v1) / 10000) > ((v2) / 10000) ? 1 : (((v1) / 10000) < ((v2) / 10000) ? -1 : 0))

/// @brief Compares two versions by year and month (ignores patch)
/// @details Returns 1 if v1 > v2, 0 if equal, -1 if less
///          Usage: STD_VERSION_CMP_YEAR_MONTH(202306, 202307) -> -1
#define STD_VERSION_CMP_YEAR_MONTH(v1, v2) \
    (((v1) / 100) > ((v2) / 100) ? 1 : (((v1) / 100) < ((v2) / 100) ? -1 : 0))

/// @brief Compares two versions fully (year, month, patch)
/// @details Returns 1 if v1 > v2, 0 if equal, -1 if less
#define STD_VERSION_CMP_FULL(v1, v2) \
    ((v1) > (v2) ? 1 : ((v1) < (v2) ? -1 : 0))

/// @brief Checks if two versions match in year (ignores month and patch)
/// @details Returns 1 if years match, 0 otherwise
#define STD_VERSION_MATCH_YEAR(v1, v2) \
    (((v1) / 10000) == ((v2) / 10000))

/// @brief Checks if two versions match in year and month (ignores patch)
/// @details Returns 1 if year and month match, 0 otherwise
#define STD_VERSION_MATCH_YEAR_MONTH(v1, v2) \
    (((v1) / 100) == ((v2) / 100))

// =============================================
// Version Comparison Helpers (Boolean Results)
// =============================================

/// @brief Returns 1 if v1_year > v2_year (year-only comparison)
#define STD_VERSION_GT_YEAR(v1, v2) \
    (((v1) / 10000) > ((v2) / 10000))

/// @brief Returns 1 if v1_year >= v2_year (year-only comparison)
#define STD_VERSION_GE_YEAR(v1, v2) \
    (((v1) / 10000) >= ((v2) / 10000))

/// @brief Returns 1 if v1_year < v2_year (year-only comparison)
#define STD_VERSION_LT_YEAR(v1, v2) \
    (((v1) / 10000) < ((v2) / 10000))

/// @brief Returns 1 if v1_year <= v2_year (year-only comparison)
#define STD_VERSION_LE_YEAR(v1, v2) \
    (((v1) / 10000) <= ((v2) / 10000))

/// @brief Returns 1 if v1 (year+month) > v2 (year+month)
#define STD_VERSION_GT_YEAR_MONTH(v1, v2) \
    (((v1) / 100) > ((v2) / 100))

/// @brief Returns 1 if v1 (year+month) >= v2 (year+month)
#define STD_VERSION_GE_YEAR_MONTH(v1, v2) \
    (((v1) / 100) >= ((v2) / 100))

/// @brief Returns 1 if v1 (year+month) < v2 (year+month)
#define STD_VERSION_LT_YEAR_MONTH(v1, v2) \
    (((v1) / 100) < ((v2) / 100))

/// @brief Returns 1 if v1 (year+month) <= v2 (year+month)
#define STD_VERSION_LE_YEAR_MONTH(v1, v2) \
    (((v1) / 100) <= ((v2) / 100))

// =============================================
// Preprocessor-Compatible Version Comparison
// =============================================

/*
 * These macros are designed to work in #if preprocessor directives.
 * They use masking to keep only the year component.
 * 
 * Example usage in #if:
 *   #if STD_VERSION_CMP_YEAR_PP(2023, 2024) < 0
 *       // Code for versions before 2024
 *   #endif
 */

/// @brief Masks out month and patch, keeping only year (for preprocessor comparisons)
/// @details Example: STD_VERSION_YEAR_ONLY(20230615) -> 2023
#define STD_VERSION_YEAR_ONLY(version) ((version) / 10000)

/// @brief Masks out patch, keeping year and month (for preprocessor comparisons)
/// @details Example: STD_VERSION_YEAR_MONTH_ONLY(20230615) -> 202306
#define STD_VERSION_YEAR_MONTH_ONLY(version) ((version) / 100)

/// @brief Compares year components for preprocessor use (returns 0, 1, or -1)
/// @details Usable in #if directives
#define STD_VERSION_CMP_YEAR_PP(v1, v2) \
    (STD_VERSION_YEAR_ONLY(v1) > STD_VERSION_YEAR_ONLY(v2) ? 1 : \
     (STD_VERSION_YEAR_ONLY(v1) < STD_VERSION_YEAR_ONLY(v2) ? -1 : 0))

/// @brief Returns 1 if year of v1 >= year of v2 (for preprocessor)
#define STD_VERSION_GE_YEAR_PP(v1, v2) \
    (STD_VERSION_YEAR_ONLY(v1) >= STD_VERSION_YEAR_ONLY(v2))

/// @brief Returns 1 if year of v1 <= year of v2 (for preprocessor)
#define STD_VERSION_LE_YEAR_PP(v1, v2) \
    (STD_VERSION_YEAR_ONLY(v1) <= STD_VERSION_YEAR_ONLY(v2))

/// @brief Returns 1 if year of v1 > year of v2 (for preprocessor)
#define STD_VERSION_GT_YEAR_PP(v1, v2) \
    (STD_VERSION_YEAR_ONLY(v1) > STD_VERSION_YEAR_ONLY(v2))

/// @brief Returns 1 if year of v1 < year of v2 (for preprocessor)
#define STD_VERSION_LT_YEAR_PP(v1, v2) \
    (STD_VERSION_YEAR_ONLY(v1) < STD_VERSION_YEAR_ONLY(v2))

// =============================================
// Practical Examples with C++ Standards
// =============================================

/*
 * These macros demonstrate how to apply version comparisons
 * to actual C++ standard versions
 */

/// @brief Returns the current C++ standard version as a year-only number (e.g., 2017 for C++17)
#define STD_cppVersionYear (STD_VERSION_YEAR(STD_cppVersion))

/// @brief Returns the current C++ standard version as year*100 (e.g., 201700 for C++17)
#define STD_cppVersionYearOnly (STD_VERSION_YEAR_ONLY(STD_cppVersion))

/// @brief Returns 1 if C++ version is at least the specified year
/// @details Example: STD_cppVersionAtLeast(2020) -> true for C++20, 23, 26
#define STD_cppVersionAtLeast(year) \
    (STD_VERSION_YEAR(STD_cppVersion) >= (year))

/// @brief Returns 1 if C++ version is exactly the specified year
/// @details Example: STD_cppVersionIs(2017) -> true only for C++17
#define STD_cppVersionIs(year) \
    (STD_VERSION_YEAR(STD_cppVersion) == (year))

/// @brief Returns 1 if C++ version is between min_year and max_year (inclusive)
#define STD_cppVersionBetween(min_year, max_year) \
    (STD_VERSION_YEAR(STD_cppVersion) >= (min_year) && \
     STD_VERSION_YEAR(STD_cppVersion) <= (max_year))

// =============================================
// Version Generation for C++ Standards
// =============================================

/*
 * Generate version integers from C++ standard years
 */

/// @brief Generate version integer from year (e.g., STD_VERSION_CPP(2017) -> 20170000)
#define STD_VERSION_CPP(year) STD_VERSION_GEN(year)

/// @brief Generate version integer from year and month (e.g., STD_VERSION_CPP_FULL(2017, 3) -> 20170300)
#define STD_VERSION_CPP_FULL(year, month) STD_VERSION_FULL(year, month)

/// @brief Predefined C++ standard versions
#define STD_CPP98_VERSION  STD_VERSION_CPP(1998)   // 19980000
#define STD_CPP03_VERSION  STD_VERSION_CPP(2003)   // 20030000
#define STD_CPP11_VERSION  STD_VERSION_CPP(2011)   // 20110000
#define STD_CPP14_VERSION  STD_VERSION_CPP(2014)   // 20140000
#define STD_CPP17_VERSION  STD_VERSION_CPP(2017)   // 20170000
#define STD_CPP20_VERSION  STD_VERSION_CPP(2020)   // 20200000
#define STD_CPP23_VERSION  STD_VERSION_CPP(2023)   // 20230000
#define STD_CPP26_VERSION  STD_VERSION_CPP(2026)   // 20260000

// =============================================
// Cross-Platform Compiler & Feature Macros
// =============================================

/*
 * These macros provide a unified interface for compiler-specific features
 * that vary across platforms and compilers.
 *
 * Naming convention:
 * - M_ prefix indicates a cross-platform macro
 * - camelCase suffix for consistency with other public macros
 * - Each macro expands to the appropriate compiler-specific keyword or construct
 */

// =============================================
// Thread Local Storage (TLS)
// =============================================

/*
 * Thread-local storage duration macros.
 * 
 * Platform support:
 * - C11:        _Thread_local + <threads.h>
 * - C++11:      thread_local
 * - GCC/Clang:  __thread (GNU extension, C99/C11)
 * - MSVC:       __declspec(thread)
 * - MinGW:      __thread (with POSIX threads) or __declspec(thread)
 *
 * Known issues from search results:
 * - Older MSVC (< 2015) only supports __declspec(thread) [citation:6]
 * - MinGW with win32 threads has issues with destructors [citation:1]
 * - Apple platforms had thread_local support removed at one point [citation:7]
 * - Some platforms require pthreads for TLS destructors [citation:1][citation:7]
 */

/// @brief Thread-local storage keyword for C/C++ variables
/// @details Expands to the appropriate TLS keyword for the compiler:
///          - C23/C11: _Thread_local
///          - C++11: thread_local
///          - GCC/Clang: __thread
///          - MSVC: __declspec(thread)
/// @example M_threadLocal int counter;
#if defined(__cplusplus) && __cplusplus >= 201103L
    // C++11 and later use standard thread_local
#   define M_threadLocal thread_local
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && !defined(__cplusplus)
    // C11/C17/C23 use _Thread_local
#   define M_threadLocal _Thread_local
#elif defined(__GNUC__) || defined(__clang__)
    // GCC/Clang GNU extension (works in C99/C11 mode)
#   define M_threadLocal __thread
#elif defined(_MSC_VER)
    // Microsoft Visual C++
#   define M_threadLocal __declspec(thread)
#else
    // Fallback - no TLS support
#   define M_threadLocal
#endif

/// @brief Alias for M_threadLocal with explicit C++ naming
#define M_tls M_threadLocal

// =============================================
// Compiler Attributes & Hints
// =============================================

/*
 * Compiler-specific attributes for optimization and diagnostics.
 * These help the compiler generate better code or provide additional checks.
 */

/// @brief Force inline a function (compiler hint)
/// @details Expands to compiler-specific always_inline attribute
/// @example M_alwaysInline int fastAdd(int a, int b) { return a + b; }
#if defined(_MSC_VER)
#   define M_alwaysInline __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#   define M_alwaysInline __attribute__((always_inline)) inline
#else
#   define M_alwaysInline inline
#endif

/// @brief Never inline a function (useful for debugging)
/// @example M_noInline void debugFunction() { ... }
#if defined(_MSC_VER)
#   define M_noInline __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
#   define M_noInline __attribute__((noinline))
#else
#   define M_noInline
#endif

/// @brief Mark a function as pure (no side effects, result depends only on args)
/// @details Enables common subexpression elimination
/// @example M_pure int square(int x) { return x * x; }
#if defined(__GNUC__) || defined(__clang__)
#   define M_pure __attribute__((pure))
#else
#   define M_pure
#endif

/// @brief Mark a function as const (like pure, but also doesn't read global memory)
/// @details Even more optimization-friendly than pure
/// @example M_const int cube(int x) { return x * x * x; }
#if defined(__GNUC__) || defined(__clang__)
#   define M_const __attribute__((const))
#else
#   define M_const
#endif

/// @brief Mark a function as hot (frequently executed)
/// @details Helps with branch prediction and inlining decisions
#if defined(__GNUC__) || defined(__clang__)
#   define M_hot __attribute__((hot))
#else
#   define M_hot
#endif

/// @brief Mark a function as cold (rarely executed, e.g., error handlers)
/// @details Optimizes for size over speed
#if defined(__GNUC__) || defined(__clang__)
#   define M_cold __attribute__((cold))
#else
#   define M_cold
#endif

/// @brief Mark a function as deprecated (compiler warning on use)
/// @example M_deprecated("Use newFunction() instead") void oldFunction();
#if defined(_MSC_VER)
#   define M_deprecated(msg) __declspec(deprecated(msg))
#elif defined(__GNUC__) || defined(__clang__)
#   define M_deprecated(msg) __attribute__((deprecated(msg)))
#else
#   define M_deprecated(msg)
#endif

/// @brief Mark a function as noreturn (never returns, e.g., exit(), abort())
/// @details Helps compiler optimize and eliminate unreachable code warnings
#if defined(_MSC_VER)
#   define M_noReturn __declspec(noreturn)
#elif defined(__GNUC__) || defined(__clang__)
#   define M_noReturn __attribute__((noreturn))
#else
#   define M_noReturn
#endif

/// @brief Mark a function as malloc-like (returns a pointer that doesn't alias)
/// @details Helps with alias analysis optimization
#if defined(__GNUC__) || defined(__clang__)
#   define M_malloc __attribute__((malloc))
#else
#   define M_malloc
#endif

/// @brief Mark a function as warn_unused_result (warning if return value ignored)
/// @example M_warnUnused int openFile(const char* path);
#if defined(__GNUC__) || defined(__clang__)
#   define M_warnUnused __attribute__((warn_unused_result))
#elif defined(_MSC_VER)
#   define M_warnUnused _Check_return_
#else
#   define M_warnUnused
#endif

// =============================================
// Branch Prediction Hints
// =============================================

/*
 * Help the compiler optimize branch prediction for hot/cold paths.
 * These are particularly useful in error handling or rare conditions.
 */

/// @brief Hint that a condition is likely true (for branch prediction)
/// @example if (M_likely(ptr != NULL)) { ... }
#if defined(__GNUC__) || defined(__clang__)
#   define M_likely(x)   __builtin_expect(!!(x), 1)
#   define M_unlikely(x) __builtin_expect(!!(x), 0)
#else
#   define M_likely(x)   (x)
#   define M_unlikely(x) (x)
#endif

// =============================================
// Compiler Built-ins & Intrinsics
// =============================================

/*
 * Compiler-provided built-in functions that don't exist in standard C/C++.
 * These map to the most efficient implementation available.
 */

/// @brief Indicate unreachable code (helps optimizer eliminate dead paths)
/// @example M_unreachable(); // after a function that always throws
#if defined(_MSC_VER)
#   define M_unreachable() __assume(0)
#elif defined(__GNUC__) || defined(__clang__)
#   define M_unreachable() __builtin_unreachable()
#else
#   define M_unreachable() do { } while (1)
#endif

/// @brief Get the current function name (with nice formatting)
/// @details
/// - GCC/Clang: __PRETTY_FUNCTION__ (includes return type and params)
/// - MSVC: __FUNCSIG__ (includes calling convention)
/// - C99: __func__ (standard, less detailed)
/// @example printf("Entered %s\n", M_functionName);
#if defined(_MSC_VER)
#   define M_functionName __FUNCSIG__
#elif defined(__GNUC__) || defined(__clang__)
#   define M_functionName __PRETTY_FUNCTION__
#else
#   define M_functionName __func__
#endif

/// @brief Get the current function name (simple, standard version)
#define M_funcName __func__

/// @brief Force a memory barrier (prevents reordering across this point)
#if defined(_MSC_VER)
#   include <intrin.h>
#   pragma intrinsic(_ReadWriteBarrier)
#   define M_compilerBarrier() _ReadWriteBarrier()
#elif defined(__GNUC__) || defined(__clang__)
#   define M_compilerBarrier() __asm__ volatile("" ::: "memory")
#else
#   define M_compilerBarrier() do { } while (0)
#endif

/// @brief Get the alignment of a type (as a compile-time constant)
/// @example size_t align = M_alignOf(int);
#if defined(_MSC_VER)
#   define M_alignOf(type) __alignof(type)
#elif defined(__GNUC__) || defined(__clang__)
#   define M_alignOf(type) __alignof__(type)
#else
#   define M_alignOf(type) _Alignof(type)
#endif

/// @brief Force a variable to be aligned to a specific boundary
/// @example M_aligned(64) float cache_line[8];
#if defined(_MSC_VER)
#   define M_aligned(bytes) __declspec(align(bytes))
#elif defined(__GNUC__) || defined(__clang__)
#   define M_aligned(bytes) __attribute__((aligned(bytes)))
#else
#   define M_aligned(bytes)
#endif

/// @brief Tell the compiler a variable is probably initialized (suppress warnings)
/// @example M_assume(ptr != NULL);
#if defined(_MSC_VER)
#   define M_assume(expr) __assume(expr)
#elif defined(__clang__) && __clang_major__ >= 3
#   define M_assume(expr) __builtin_assume(expr)
#elif defined(__GNUC__)
#   define M_assume(expr) do { if (!(expr)) __builtin_unreachable(); } while (0)
#else
#   define M_assume(expr) do { } while (0)
#endif

// =============================================
// Compiler Feature Detection
// =============================================

/*
 * Feature detection macros - 1 if supported, 0 otherwise.
 * Use these to conditionally compile code that requires specific features.
 */

/// @brief Returns 1 if the compiler supports C++11 thread_local keyword
#define M_hasThreadLocal (\
    (defined(__cplusplus) && __cplusplus >= 201103L) || \
    (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) || \
    defined(__GNUC__) || defined(__clang__) || defined(_MSC_VER))

/// @brief Returns 1 if the compiler supports __builtin_expect (branch prediction)
#define M_hasBuiltinExpect (defined(__GNUC__) || defined(__clang__))

/// @brief Returns 1 if the compiler supports __builtin_unreachable
#define M_hasBuiltinUnreachable (\
    defined(__GNUC__) || defined(__clang__) || defined(_MSC_VER))

/// @brief Returns 1 if the compiler supports always_inline attribute
#define M_hasAlwaysInline (\
    defined(_MSC_VER) || defined(__GNUC__) || defined(__clang__))

/// @brief Returns 1 if the compiler supports __PRETTY_FUNCTION__ or similar
#define M_hasPrettyFunction 1  // All major compilers have some equivalent

// =============================================
// Standard Library Feature Macros
// =============================================

/// @brief Align a value to the next multiple of alignment (power of 2)
/// @example size_t aligned = M_alignUp(15, 16); // returns 16
#define M_alignUp(value, alignment) \
    (((value) + ((alignment) - 1)) & ~((alignment) - 1))

/// @brief Align a value to the previous multiple of alignment (power of 2)
/// @example size_t aligned = M_alignDown(15, 16); // returns 0
#define M_alignDown(value, alignment) \
    ((value) & ~((alignment) - 1))

/// @brief Check if a value is aligned to the given alignment (power of 2)
#define M_isAligned(value, alignment) \
    (((value) & ((alignment) - 1)) == 0)

/// @brief Count the number of elements in a static array
#define M_arraySize(arr) (sizeof(arr) / sizeof((arr)[0]))

/// @brief Get the offset of a member within a struct type
/// @example size_t offset = M_offsetOf(struct mystruct, myfield);
#if defined(_MSC_VER)
#   define M_offsetOf(type, member) offsetof(type, member)
#else
#   define M_offsetOf(type, member) __builtin_offsetof(type, member)
#endif

/// @brief Get the container pointer from a member pointer
/// @example container_t* container = M_containerOf(member_ptr, container_t, member);
#define M_containerOf(ptr, type, member) \
    ((type*)((char*)(ptr) - M_offsetOf(type, member)))

/// @brief Suppress unused variable warnings
/// @example M_unused(x); // x is intentionally unused
#define M_unused(x) ((void)(x))

/// @brief Mark a variable as potentially unused (suppresses warnings)
#define M_maybeUnused __attribute__((unused))

// =============================================
// Endianness Helpers
// =============================================

/// @brief Swap bytes in a 16-bit value
#define M_swap16(x) ((unsigned short)(((x) >> 8) | ((x) << 8)))

/// @brief Swap bytes in a 32-bit value
#define M_swap32(x) \
    ((unsigned int)(((x) & 0xFF000000) >> 24) | \
     ((x) & 0x00FF0000) >> 8) | \
     ((x) & 0x0000FF00) << 8) | \
     ((x) & 0x000000FF) << 24))

/// @brief Convert from host to network byte order (big-endian)
#if OS_isBigEndian
#   define M_hton16(x) (x)
#   define M_hton32(x) (x)
#   define M_ntoh16(x) (x)
#   define M_ntoh32(x) (x)
#else
#   define M_hton16(x) M_swap16(x)
#   define M_hton32(x) M_swap32(x)
#   define M_ntoh16(x) M_swap16(x)
#   define M_ntoh32(x) M_swap32(x)
#endif
