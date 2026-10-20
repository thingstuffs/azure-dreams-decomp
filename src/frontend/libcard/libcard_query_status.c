#include "common.h"

extern s16 func_8004DBDC(void);
s16 libcard_query_status(void) { return func_8004DBDC(); }
