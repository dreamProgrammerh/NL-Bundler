#pragma once

// ========================
// System Headers
// ========================
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// ========================
// Core Types
// ========================
#include "core/platform.h"
#include "core/stypes.h"
#include "core/typedefs.h"

// ========================
// Constants
// ========================
#include "constants/version.h"

// ========================
// Utilities (Header-only)
// ========================
#include "core/strings.h"
#include "utils/log.h"
#include "utils/debug.h"

// ========================
// API Headers
// ========================
#include "utils/path.h"
#include "utils/file.h"
#include "lexer/token.h"
#include "parser/node.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

// ========================
// Implementation Guard
// ========================
#ifdef NLC_IMPLEMENTATION
#include "nlc.c"
#endif