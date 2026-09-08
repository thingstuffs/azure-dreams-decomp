#include "common.h"

extern void *D_800C25C0;
extern s32 D_800D4FA0[];

/* Initialize the object's handler and values from its configuration bytes. */
void func_800C258C(void *object) {
    *(void **)((u8 *)object - 0x10) = &D_800C25C0;
    *(s32 *)((u8 *)object + 0x60) = *((u8 *)object + 0x96);
    *(s32 *)((u8 *)object + 0x50) = D_800D4FA0[*((u8 *)object + 0x94)];
}
