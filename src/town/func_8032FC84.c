#include "common.h"
#include "shared/record_ptrs.h"

typedef struct TownRuntime {
    u8 pad_00[0x28];
    void *field_28;
    void *field_2C;
    u8 pad_30[4];
    void *field_34;
} TownRuntime;

extern s16 D_8001B8A8[3];
extern s32 D_8001C370;
extern u8 D_8001C480[0x10];
extern u8 D_8001DA10;
extern u8 D_8001DC10;
extern u8 D_8001DCD0;

extern void func_80019860(s32, s32, s32);
extern void func_80016748(void);
extern void func_8001A044(s32, void *, void *);

/* Initializes town resources and stores their pointers in the runtime. */
void func_8001A484(void) {
    s16 *position;
    TownRuntime *runtime;

    position = D_8001B8A8;
    func_80019860(D_8001B8A8[0], position[1], position[2]);
    func_80016748();
    func_8001A044(D_8001C370, D_8001C480, &D_8001DA10);
    runtime = *(TownRuntime **)((u8 *)(&D_80016000));
    runtime->field_28 = D_8001C480;
    runtime->field_34 = &D_8001DC10;
    runtime->field_2C = &D_8001DCD0;
}
