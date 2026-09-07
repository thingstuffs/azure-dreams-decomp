#include "common.h"

typedef struct {
    u32 words[3];
} __attribute__((packed)) Copy12;

typedef struct {
    u8 pad[0x1C];
    s32 flags;
} Status;

extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0();
extern void func_800A2B04(s32, s32, s32);
extern u8 D_80082E80[];
extern Copy12 D_8016A858[];
extern u8 *D_80174704;

/* Reposition the current object using an indexed offset from the reference coordinates. */
void func_8016E138(s32 offset_index) {
    Copy12 offsets;
    s32 old_tile_mask;
    s32 new_tile_mask;
    register s32 saved_index ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs state+offset) depends on it */
    u8 *offset_bytes;
    register u8 *offset_page ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    register Copy12 *offset_src ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
    s16 *xy_offset;
    s32 object_handle;
    u8 *object;
    u8 *origin;
    u8 *state;
    register Status *status ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    register s32 offset_pos ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 status_flags;
    s32 x;
    s32 y;

    saved_index = offset_index;
    ASM_KEEP_NV(saved_index);   /* MATCH pin: retail schedule: same instructions, different order without it */
    state = D_80174704;
    ASM_KEEP_NV(state);   /* MATCH pin: retail schedule: same instructions, different order without it */
#ifdef NON_MATCHING
    offset_page = (u8 *)D_8016A858 + 0x57A8;
#else
    offset_page = (u8 *)0x80170000;
#endif
    ASM_KEEP(offset_page);   /* MATCH pin: retail immediate-load split depends on it */
    offset_src = (Copy12 *)(offset_page - 0x57A8);
    ASM_KEEP_NV(offset_src);   /* MATCH pin: retail address form (%hi/%lo vs state+offset) depends on it */
    offsets = *offset_src;
    ASM_KEEP_DEP_NV(offset_src, offset_page);   /* MATCH pin: retail register colouring depends on it */
    old_tile_mask = 0x3000;
    status = (Status *)state + 1;
    ASM_KEEP_NV(status);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    object = *(u8 **)(state + 0xC);
    object_handle = *(s32 *)(state + 8);
    *(u16 *)(object + 0x14) &= 0xFF7F;
    x = object[0x24];
    y = object[0x25];
    if (status->flags & 0x2000) {
        old_tile_mask = 0x300;
    }
    offset_bytes = (u8 *)&offsets;
    func_8009A3D0(x, y, old_tile_mask, offset_src);
    origin = D_80082E80;
    ASM_KEEP_NV(origin);   /* MATCH pin: retail schedule: same instructions, different order without it */
    offset_pos = saved_index << 1;
    xy_offset = (s16 *)(offset_bytes + offset_pos);
    object[0x24] = origin[0x24] + ((u8 *)xy_offset)[0];
    object[0x25] = origin[0x25] + ((u8 *)xy_offset)[1];
    func_800A2B04(object_handle, object[0x24], object[0x25]);
    status_flags = *(volatile s32 *)&status->flags;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    x = object[0x24];
    y = object[0x25];
    new_tile_mask = 0x3000;
    if (status_flags & 0x2000) {
        new_tile_mask = 0x300;
    }
    func_8009A21C(x, y, new_tile_mask);
}
