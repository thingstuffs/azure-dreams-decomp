#include "common.h"
#include "frontend/libcard.h"

/* Stores a value at the destination address. */
void set_file_list_selection(ObjectNodeHeader **dest, ObjectNodeHeader *parent) {
    *dest = parent;
}
