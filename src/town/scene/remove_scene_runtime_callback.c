#include "common.h"

extern u8 D_80123124[];
extern void remove_runtime_callback(void *);
/* Calls remove_runtime_callback with D_80123124. */
void remove_scene_runtime_callback(void) { remove_runtime_callback(D_80123124); }
