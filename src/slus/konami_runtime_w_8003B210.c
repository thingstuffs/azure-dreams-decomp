#include "common.h"

#include "common.h"

void func_8003B034(void);
void func_8003B06C(void);

/* Runs the two Konami runtime routines in sequence. */
void func_8003B210(void) {
    func_8003B034();
    func_8003B06C();
}
