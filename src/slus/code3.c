#include "common.h"

/* --- gcc 2.95.2 -O2 -fno-delayed-branch translation unit --- */

extern void *D_8006CDC8[];
extern int file_load_com(void *arg);

/* Passes the indexed table pointer to file_load_com. */
int func_8003E1C4(short table_index)
{
    return file_load_com(D_8006CDC8[table_index]);
}
