#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/movie.h"



/* Clears the object's field at offset 0x14. */
void clear_town_movie_object_field(MovieListNode *object) {
    object->next = 0;
}
