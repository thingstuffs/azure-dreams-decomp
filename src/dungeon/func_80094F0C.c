#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    u8 pad24[0x24];
    u8 x;
    u8 y;
    s8 flag;
} FuncArg1;

typedef struct {
    u8 pad1c[0x1c];
    u32 flags;
    u8 pad20[0x68];
    u16 height;
} FuncArg2;

typedef struct {
    u8 pad0c[0x0c];
    u16 flags;
    u8 tail[6];
} FuncMonster;

extern s32 func_8009A350(s32, s32, s32, u16 *);
extern s32 func_8009A540(s32, s32, s32, s16);
extern s32 func_8009B25C(FuncArg2 *, s32, s32, s16);
extern s16 func_8009FB34(u16, u16);
extern s32 func_800BCB04(s32, s32, s16);

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_800DCEAC[];
extern s16 D_800DCEBC[];
extern FuncMonster D_800E2970[];

/* Checks movement clearance and classifies the destination height relative to the actor. */
s32 func_8009A66C(u32 move_flags, FuncArg1 *position, FuncArg2 *actor, s16 height_offset) {
    register s16 offset_or_height ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 call_direction;
    s16 *x_table;
    u16 flags;
    u16 *flags_out;
    s32 direction;
    u32 x_shifted;
    u32 y_shifted;
    s32 x_base;
    s32 y_base;
    s32 x_pos;
    s32 y_pos;
    register u16 height ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 monster_index;
    s32 dest_height;
    register s32 signed_height ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 status;

    direction = (move_flags >> 9) & 7;
    height = actor->height;
    x_shifted = position->x << 6;
    y_shifted = position->y << 6;
    x_base = x_shifted + 0x20;
    y_base = y_shifted + 0x20;

    if ((func_8009A540(direction, x_shifted >> 6, y_shifted >> 6,
                       (s16)(height - height_offset)) << 16) != 0) {

        call_direction = direction;
        flags_out = &flags;
        x_table = D_800DCEAC;
        offset_or_height = call_direction << 1;
        x_pos = *(u16 *)((u8 *)x_table + offset_or_height) + x_base;
        y_pos = *(u16 *)((u8 *)D_800DCEBC + offset_or_height) + y_base;
        if ((func_8009A350(position->x, position->y, call_direction, flags_out) << 16) == 0) {
            return 0;
        }

        if (position->flag < 0) {
            monster_index = func_8009FB34(
                (u16)(position->x +
                      *(u16 *)((u8 *)D_8006CCD8 + offset_or_height)),
                (u16)(position->y +
                      *(u16 *)((u8 *)D_8006CCE8 + offset_or_height)));
            if (monster_index >= 0 &&
                (D_800E2970[monster_index].flags & 2) &&
                !(actor->flags & 0x2000)) {
                return 0;
            }
        }

        if (flags & 0x8402) {
            return 0;
        }

        if (flags & 0x3300) {
            s32 y_coord;
            s32 x_coord;

            if (!(flags & 0x40)) {
                status = -1;
                goto done;
            }
            x_pos &= 0xFFFF;
            x_coord = x_pos;
            y_coord = y_pos & 0xFFFF;
            offset_or_height = func_800BCB04(x_coord, y_coord, (s16)(height - height_offset));
            if (func_8009B25C(actor, (u32)x_pos >> 6, (u32)y_coord >> 6,
                              (s16)offset_or_height)) {
                status = -1;
                goto done;
            }
        } else {
            offset_or_height = func_800BCB04(x_pos & 0xFFFF, y_pos & 0xFFFF,
                                   (s16)(height - height_offset));
        }

        status = (u32)offset_or_height << 16;
        dest_height = status >> 16;
        if (dest_height >= 0x200) {
            return 0;
        }
        status = (u32)height << 16;
        signed_height = status >> 16;
        status = 1;
        if (dest_height == signed_height) {
            goto done;
        }
        status = 2;
        if (signed_height < dest_height) {
            goto done;
        }
        status = 3;
done:
        return status;
    }
    return 0;
}
