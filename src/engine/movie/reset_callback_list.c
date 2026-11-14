#include "common.h"
#include "m2c_compat.h"

#include "engine/movie.h"



/* Clears the object's field at offset 0x14. */
void reset_callback_list(MovieListNode *object) {
    object->next = 0;
}
