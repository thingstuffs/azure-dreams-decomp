#include "common.h"

/* --- gcc 2.95.2 -O2 -fno-delayed-branch translation unit --- */

extern void *D_8006CDC8[];
extern int func_80041284(void *arg);

/* Passes the indexed table pointer to func_80041284. */
int func_8003E1C4(short table_index)
{
    return func_80041284(D_8006CDC8[table_index]);
}
