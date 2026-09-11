#include "common.h"

typedef struct S_80174320_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { void * s; u8 * u; } unk_2C;   /* accessed as both */
} S_80174320_0;   /* entity in func_80174320 */

typedef struct S_80174320_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x53];
    s8 unk_9B;
    u8 pad_9C[0x16];
    s16 unk_B2;
} S_80174320_1;   /* obj in func_80174320 */

typedef struct S_80174320_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80174320_2;   /* ctx in func_80174320 */



extern void func_80047784(void *, u8, s32);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A152C(s32, s32);
extern void func_800A9A0C(void *);
extern void func_8016FCE4(void *, void *, void *, void *);
extern void func_80171594(u8, u8, s16);
extern void func_801724D4(void);
extern void func_801740F8(void *, void *, void *, void *);

extern s16 D_80083228;
extern u8 D_80174A2C[];
extern u8 D_80174A9C[];
extern u8 D_80174AA4[];
extern u8 D_80174AAC[];
extern u8 *D_80174AB4;
extern s16 D_80174AB8;

/* Advance the command stream and update the object's direction, animation, and effects. */
s32 func_80174320(void *object_arg, void *context_arg, void *entity_arg) {
    s32 audio_param;
    s16 elapsed_ticks;
    register s32 command ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 opcode;
    u16 entity_flag;
    register u8 command_byte ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 duration;
    u8 *stream;
    void *call_obj;
    register void *obj ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    void *entity;
    register s32 result;
    u32 anim_page;
    void *old_anim;
    u8 *anim;
    u8 audio_x;
    u8 audio_y;
    register s32 angle ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u16 obj_flags;
    s32 clear_opcode;

    call_obj = object_arg;
    entity = entity_arg;
    obj = object_arg;
    if (((S_80174320_0 *)entity)->unk_14 & 0x40) {
        return 0;
    }

    stream = D_80174AB4;
    if (stream == 0) {
        result = 0;
        return result;
    }

    command_byte = stream[1];
    ASM_KEEP_NV(command_byte);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    command = command_byte & 0xFF;
    if (command == 0) {
        ((S_80174320_1 *)obj)->unk_B2 = 0;
        goto block_common;
    }

    duration = stream[0];
    elapsed_ticks = *(u16 *)&D_80174AB8 + 1;
    D_80174AB8 = elapsed_ticks;
    if ((s32)duration < elapsed_ticks) {
        D_80174AB4 = stream + 2;
        D_80174AB8 = 0;
        ((S_80174320_1 *)obj)->unk_9B = 0;
    }

    angle = command_byte & 7;
    obj_flags = ((S_80174320_1 *)obj)->unk_46;
    ASM_KEEP_NV(obj_flags);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    angle <<= 9;
    ((S_80174320_1 *)obj)->unk_2A = angle;
    clear_opcode = 0xD0;
    ASM_USE(clear_opcode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    obj_flags |= 0x8000;
    ((S_80174320_1 *)obj)->unk_46 = obj_flags;
    opcode = command & 0xF8;
    ASM_KEEP(command);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(call_obj);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */

    if (opcode == clear_opcode) {
        goto block_D0;
    }
    if (opcode < 0xD1) {
        if (opcode == 0x10) {
            goto block_10;
        }
        if (opcode < 0x11) {
            if (opcode == 8) {
                goto block_8;
            }
            goto block_common;
        }
        if (opcode == 0xC0) {
            goto block_C0;
        }
        if (opcode == 0xC8) {
            goto block_C8;
        }
        goto block_common;
    }
    if (opcode == 0xE8) {
        goto block_E8;
    }
    if (opcode < 0xE9) {
        if (opcode == 0xD8) {
            goto block_D8;
        }
        if (opcode == 0xE0) {
            goto block_E0;
        }
        goto block_common;
    }
    if (opcode == 0xF0) {
        goto block_F0;
    }
    if (opcode == 0xF8) {
        goto block_F8;
    }
    goto block_common;

block_8:
    call_obj = obj;
    ASM_KEEP_NV(call_obj);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    func_8016FCE4(call_obj, context_arg, entity, call_obj);
    result = 0;
    return result;

block_C0:
    ((S_80174320_1 *)obj)->unk_9B = 0;
block_C8:
    func_801740F8(call_obj, context_arg, entity, obj);
    goto block_common;

block_10:
    old_anim = ((S_80174320_0 *)entity)->unk_2C.s;
    anim_page = 0x80170000;
    ASM_KEEP(anim_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    anim = (u8 *)(anim_page + 0x4A2C);
    goto block_anim;

block_F8:
    anim_page = 0x80170000;
    ASM_KEEP_NV(anim_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    old_anim = ((S_80174320_0 *)entity)->unk_2C.s;
    anim = (u8 *)(anim_page + 0x4AA4);
    goto block_anim;

block_F0:
    old_anim = ((S_80174320_0 *)entity)->unk_2C.s;
    anim = D_80174AAC;
block_anim:
    if (old_anim != anim) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = anim;
        func_80047784(entity,
            *(u8 *)((((D_80083228 + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7) + (u32)anim),
            0);
        goto block_common;
    }
    goto block_common;

block_E8:
    old_anim = ((S_80174320_0 *)entity)->unk_2C.s;
    anim = D_80174A9C;
    if (old_anim != anim) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = anim;
        func_80047784(entity,
            anim[((D_80083228 + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7],
            0);
        func_80171594(((S_80174320_0 *)entity)->unk_24, ((S_80174320_0 *)entity)->unk_25,
            ((S_80174320_2 *)context_arg)->unk_0A);
        func_800A152C(0x15, 1);
        goto block_common;
    }
    goto block_common;

block_D8:
    old_anim = ((S_80174320_0 *)entity)->unk_2C.s;
    anim = D_80174A9C;
    if (old_anim != anim) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = anim;
        func_80047784(entity,
            anim[((D_80083228 + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80174320_0 *)entity)->unk_14 |= 0x800;
        goto block_common;
    }
    goto block_common;

block_D0:
    entity_flag = ((S_80174320_0 *)entity)->unk_14 & 0x800;
    ((S_80174320_0 *)entity)->unk_14 = entity_flag;
    if (entity_flag != 0) {
        ((S_80174320_0 *)entity)->unk_14 = 0;
        goto block_common;
    }
    goto block_common;

block_E0:
    anim = D_80174A2C + 0x50;
    if (((S_80174320_0 *)entity)->unk_2C.u != anim) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = anim;
        func_80047784(entity,
            anim[((D_80083228 + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7],
            0);
        func_801724D4();
        audio_x = ((S_80174320_0 *)entity)->unk_24;
        audio_y = ((S_80174320_0 *)entity)->unk_25;
        audio_param = 0x3000;
        if (((S_80174320_1 *)obj)->unk_1C & 0x2000) {
            audio_param = 0x300;
        }
        func_8009A3D0(audio_x, audio_y, audio_param);
    }
    goto block_common;

block_common:
    func_800A9A0C(obj);
    return 0;
}
