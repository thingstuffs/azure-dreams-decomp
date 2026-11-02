#include "common.h"
#include "frontend/libcard.h"
#include "frontend/card/server_imports.h"

/* Returns the result of func_8004DBDC with no arguments. */
s16 libcard_query_status(void) { return func_8004DBDC(); }
