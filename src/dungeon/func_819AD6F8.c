#include "shared/entity.h"
#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/slus_callbacks.h"

/* Position block (three 4-byte slots, only the second halfword of each is used). */


/* Render data the header's unk_0C points at. */


/* The follower's record (the object header precedes it). */


typedef struct Rect {
    s32 first;
    s32 second;
} Rect;

void draw_textured_ellipse();
extern u8 D_80027454[12];
extern u8 D_80027490[12];
extern u8 D_800274A8[12];

/* Creates an object at its owner's position and initializes its sprite and angle. */
void func_80024EF8(ObjectNodeHeader *owner, s16 angle) {
    Rect rect;
    ObjectNodeHeader *spawned;
    EffectSprite *sprite;
    FollowerRecord *record;

    spawned = func_8003FD64(0x212, &owner->next);
    if (spawned != 0) {
        spawned->unk_10 = copy_follower_owner_position_and_color;
        func_8004491C(spawned, (s32)func_80045340);
        ((EntityRec *)spawned->unk_08)->x.w.i = (u16)((EntityRec *)owner->unk_08)->x.w.i;
        ((EntityRec *)spawned->unk_08)->y.w.i = (u16)((EntityRec *)owner->unk_08)->y.w.i;
        ((EntityRec *)spawned->unk_08)->z.w.i = (u16)((EntityRec *)owner->unk_08)->z.w.i;
        sprite = spawned->unk_0C;
        sprite->unk_08 = D_80027454;
        sprite->size_max = 0x2800;
        sprite->size = 0x2800;
        sprite->unk_06 = 8;
        sprite->angle = angle + 0x400;
        record = (FollowerRecord *)(spawned + 1);
        sprite->shade.color = 0x808080;
        record->owner = owner;
        record->angle = angle;
        rect.first = 0x01400340;
        rect.second = 0x200020;
        draw_textured_ellipse(D_80027490, &rect, 0, 0);
        draw_textured_ellipse(D_800274A8, &rect, 1, 0);
    }
}

