#include "common.h"

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
extern u8 D_80016000[0x10];

extern void func_80019860(s32, s32, s32);
extern void func_80016748(void);
extern void func_8001A044(s32, void *, void *);

void func_8001A484(void) {
    s16 *position;
    u8 *page;
    s32 resource;
    void *callback;
    void *data;
    TownRuntime *runtime;

    do {
        position = D_8001B8A8;
    } while (0);
    func_80019860(D_8001B8A8[0], position[1], position[2]);
    page = (u8 *)0x80020000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    func_80016748();
    do {
        resource = D_8001C370;
    } while (0);
    ASM_KEEP(resource);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    callback = page - 0x3B80;
    data = &D_8001DA10;
    func_8001A044(resource, callback, data);
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    do {
        runtime = *(TownRuntime **)D_80016000;
    } while (0);
    do {
        runtime->field_28 = page - 0x3B80;
    } while (0);
    runtime->field_34 = &D_8001DC10;
    runtime->field_2C = &D_8001DCD0;
}
