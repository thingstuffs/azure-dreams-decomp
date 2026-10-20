#include "common.h"

#include "common.h"

void func_8003B034(void);
void init_town_runtime_objects(void);

/* Runs the two Konami runtime routines in sequence. */
void init_town_runtime(void) {
    func_8003B034();
    init_town_runtime_objects();
}
