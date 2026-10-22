/* Category sorting with discovery-rank comparisons through a shared temporary table. */
#include "slus/sort_rank_81540.h"

u8 *current_sort_rank_table = 0;

#include "../build/partition_sources/code__sort_rank_81540.c"
#include "w_8004B08C.c"
