typedef struct { unsigned char pad_000[0x2a4]; int (*service)(int); } SceneService2A4;
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Invoke the callback at offset 0x88 with zero. */
void func_8047E3D0(void) {
    ((SceneService2A4 *)D_80016000->unk_20)->service(0);
}
