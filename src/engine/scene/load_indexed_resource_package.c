#include "common.h"
#include "slus/data.h"

/* --- gcc 2.95.2 -O2 -fno-delayed-branch translation unit --- */

extern int file_load_com(void *arg);

/* Passes the indexed table pointer to file_load_com. */
int load_indexed_resource_package(short table_index)
{
    return file_load_com(indexed_resource_packages[table_index]);
}
