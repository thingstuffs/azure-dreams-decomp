#include "common.h"

#include "common.h"

typedef struct S_8004A330_Sub20 {
    u16 field0;
    u16 pad2;
    s16 x;
    s16 y;
    void *field8;
} S_8004A330_Sub20;

typedef struct S_8004A330_Entity {
    u8 pad0[0xC];
    void *field_c;
    void (*update_fn)(void *);
    u8 pad1[0x1E - 0x14];
    u16 flags;
    S_8004A330_Sub20 sub20;
    u8 pad2[0x50 - 0x2C];
    u8 sub50[4];
} S_8004A330_Entity;

extern S_8004A330_Entity *func_8003FC64(s32 a0);
extern s32 func_8004B404(s32 a0);
extern void func_8004A24C(S_8004A330_Sub20 *a0, s32 a1, s32 a2,
                          s16 a3, s16 a4, s16 a5);
extern void func_8004491C(void *a0, void *a1);
extern void func_8004CAA0(void);
extern void func_80049F2C(void *a0);
extern s32 D_800814A0;
#ifndef NON_MATCHING
extern s32 D_800814A0_load[3];
__asm__(".set D_800814A0_load, 0x800814A0");
#endif

/* Allocate and initialize an entity with a resource buffer and position targets. */
S_8004A330_Entity *func_8004A330(s32 style_flags, s32 start_x, s32 start_y, s32 target_x,
                                  s32 target_y, s32 width, s32 flags, s32 content_id) {
    S_8004A330_Entity *entity;
    register S_8004A330_Sub20 *state ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 buffer_addr;
    s32 saved_style_flags = style_flags;
    register s32 saved_start_y ASM_REG("$20") = start_y;   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    register s32 saved_target_x ASM_REG("$18") = target_x;   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    register s32 saved_target_y ASM_REG("$19") = target_y;   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    register s32 saved_width ASM_REG("$21") = width;   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    u16 entity_flags;
    s32 global_flags;
#ifndef NON_MATCHING
    s32 *global_page;
#endif

    entity = func_8003FC64(0);
    if (entity != 0) {
        buffer_addr = func_8004B404(0);
        state = &entity->sub20;
        state->field8 = (void *)buffer_addr;
        if (buffer_addr != 0) {
            state->field0 = (u16)flags;
            state->x = (s16)(saved_target_x - 0xA0);
            state->y = (s16)(saved_target_y - 0x80);
            func_8004A24C(state, saved_style_flags, content_id, (s16)start_x,
                          (s16)saved_start_y,
                          (s16)saved_width);
            ASM_KEEP(start_x);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(saved_start_y);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(saved_target_x);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(saved_target_y);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(saved_width);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
            entity->field_c = &entity->sub50;
            func_8004491C(entity, func_8004CAA0);
            entity->update_fn = func_80049F2C;
        } else {
            entity_flags = entity->flags;
            entity->flags = entity_flags | 0x8000;
#ifndef NON_MATCHING
            global_flags = D_800814A0_load[0];
#else
            global_flags = D_800814A0;
#endif
            entity = 0;
            global_flags |= 0x8000;
#ifndef NON_MATCHING
            global_page = (s32 *)0x80080000;
            global_page[0x528] = global_flags;
#else
            D_800814A0 = global_flags;
#endif
        }
    }
    return entity;
}
