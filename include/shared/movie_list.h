#ifndef SHARED_MOVIE_LIST_H
#define SHARED_MOVIE_LIST_H

#include "common.h"

/* The list node view formerly local to append_town_movie_list_node.c.
 * append_list_tail follows and clears the link at +0x14; the callback runner
 * consumes the first five words. Keep those words opaque in this link view. */
typedef struct S_8003AF58_1 {
    u8 pad_00[0x14];
    struct S_8003AF58_1 *next; /* 0x14 */
} MovieListNode;

#endif
