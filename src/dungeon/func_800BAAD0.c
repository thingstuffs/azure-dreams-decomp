#include "common.h"

typedef struct Struct_80083460 {
    u8 pad[10];
    u16 count;
} Struct_80083460;

extern u8 *D_800E3D7C;
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern s32 D_80012090;
extern s16 D_8008146C;
extern Struct_80083460 D_80083460[];
extern u8 D_800C0180[];
extern u8 D_800DF45C[];
extern u8 D_800E1375[];
extern u8 D_800E13B7[];

extern s32 func_80033BC0(s32);
extern void func_8008D344(void *, void *, void *, s32);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern void func_800997FC(void *);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32);
extern s32 func_800AD6FC(void *, u16, s32);
extern s32 func_800BBA40(u8, u8, s16, void *, s32, s32, void *);

/* Apply an event to the target and update the event count on completion. */
s32 func_800C0230(u8 *entity, s32 event, s16 target_type, s32 target_record) {
    u8 *entity_info;

    if (target_type == 0xD) {
        return func_80098864(event, target_record);
    }
    if ((void *)entity == D_800E3D7C) {
        *(s32 *)(entity + 0x110) = event;
        func_8008D344(entity, D_80083780, D_80082E80, 0);
        return 0;
    }
    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A6480(entity, event);
        if (func_800AD6FC(entity, D_800DDE84[entity[0x13]] & 3, event) == 0) {
            func_800A5F38(entity, event);
            return 1;
        }
        D_80083460->count--;
        goto block_update;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if (D_80012090 == 0 && D_8008146C == 0x28 && func_80033BC0(0xA2) == 0) {
        func_800997FC(D_800E1375);
        D_80083460->count--;
        func_80098B38(event);
        return 1;
    }
    entity_info = *(u8 **)(entity - 0x14);
    if (func_800BBA40(entity_info[0x24], entity_info[0x25],
                      *(s16 *)(entity + 0x88), D_800DF45C,
                      0x2800, 0x208020, D_800C0180) == 0) {
        return 0;
    }
    func_800997FC(D_800E13B7);
    D_80083460->count++;

block_update:
    func_80098B38(event);
    return 1;
}
