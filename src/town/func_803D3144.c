/* Relink of matched town/func_8032FC84; every changed retail word is a paired relocation. */
#define townInitObjectSetRuntimePointers func_8001A144
#define D_8001B8A8 D_8001A91C
#define D_8001C370 D_8001B320
#define D_8001C480 D_8001B430
#define D_8001DA10 D_8001B5B0
#define D_8001DC10 D_8001B5F0
#define D_8001DCD0 D_8001B638
#include "common.h"
#include "shared/record_ptrs.h"

typedef struct TownRuntime {
    u8 pad_00[0x28];
    void *field_28;
    void *field_2C;
    u8 pad_30[4];
    void *field_34;
} TownRuntime;

extern s16 D_8001A91C[3];
extern s32 D_8001B320;
extern u8 D_8001B430[0x10];
extern u8 D_8001B5B0;
extern u8 D_8001B5F0;
extern u8 D_8001B638;

extern void func_80019520(s16, s16, s16);
extern void func_80017D24(void);
extern void func_80019D04(void *, void *, void *);

/* Initializes town resources and stores their pointers in the runtime. */
void func_8001A144(void) {
    s16 *position;
    TownRuntime *runtime;

    position = D_8001A91C;
    func_80019520(D_8001A91C[0], position[1], position[2]);
    func_80017D24();
    func_80019D04(D_8001B320, D_8001B430, &D_8001B5B0);
    runtime = *(TownRuntime **)((u8 *)(&D_80016000));
    runtime->field_28 = D_8001B430;
    runtime->field_34 = &D_8001B5F0;
    runtime->field_2C = &D_8001B638;
}
