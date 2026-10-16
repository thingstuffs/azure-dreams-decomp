#include "modules/town_ovl_6490c0.h"

/* Passes the value and line to the handler with its fixed data tables. */
s32 townProcessValueWithFixedTables(s32 value, s32 unused, s32 line)
{
    return townGetFlagTestTableAddress(D_80017760, D_800178C0, value, line);
}
