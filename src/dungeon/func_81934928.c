#include "modules/dungeon_ovl_1954800.h"
void func_80024128(void *self, void *output)
{
    Copy24 *copy_src;
    void *effect;
    void *output_data;
    void *search_origin;
    void *target;
    void *particle;
    s32 rand_quotient;
    s16 state;
    s32 spawn_index;
    s32 origin_component;
    s32 random_value;
    s32 value;
    s16 countdown;
    s32 page_value;

    state = ((S_81934928_0 *)self)->unk_0A.s;
    effect = ((S_81934928_0 *)self)->unk_00;
    output_data = output;
    switch (state) {
    case 0:
    {
        if ((((S_81934928_6 *)(((S_81934928_0 *)self)->unk_04))->unk_00 & 0x80) == 0) {
            return;
        }
        {
            EntityRec *copy_page;
            *(Copy24 *)output_data = *(Copy24 *)&D_80083780;
            copy_page = &D_80083780;
            ((S_81934928_0 *)self)->unk_10.s = ((u16)copy_page->x.w.i);
            ((S_81934928_0 *)self)->unk_12.s = ((u16)copy_page->y.w.i);
            page_value = ((u16)copy_page->z.w.i);
        }
        ((S_81934928_0 *)self)->unk_0C.s = 0x3C;
        ((S_81934928_0 *)self)->unk_0A.u++;
        ((S_81934928_0 *)self)->unk_14 = page_value;
        func_800A56E0(0x300);
    }
        /* fallthrough */
    case 1:
    spawn_index = 0x3C - ((S_81934928_0 *)self)->unk_0C.u;
    if (spawn_index >= 8) {
        spawn_index = 8;
    }
    if (spawn_index >= 0) {
        do {
            particle = func_8003FD64(0x202, ((s32 *)(&D_80083498)));
            if (particle != NULL) {
                ((S_81934928_2 *)particle)->unk_10 = D_8002445C;
                func_8004491C(particle, D_80024740);
                search_origin = (u8 *)particle + 0x20;

                rand_quotient = rand();
                random_value = rand_quotient;
                origin_component = ((S_81934928_0 *)self)->unk_10.u;
                rand_quotient = random_value / 512;
                value = origin_component + ((random_value % 512)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                ((S_81934928_3 *)search_origin)->unk_0C = value;
                ((S_81934928_3 *)search_origin)->unk_1E = value;

                rand_quotient = rand();
                random_value = rand_quotient;
                origin_component = ((S_81934928_0 *)self)->unk_12.u;
                rand_quotient = random_value / 512;
                value = origin_component + ((random_value % 512)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                ((S_81934928_3 *)search_origin)->unk_0E = value;
                ((S_81934928_3 *)search_origin)->unk_22 = value;

                value = ((S_81934928_0 *)self)->unk_14 - 0x100;
                ((S_81934928_3 *)search_origin)->unk_10 = value;
                ((S_81934928_3 *)search_origin)->unk_26 = value;
                ((S_81934928_2 *)particle)->unk_20 = self;
            }
            spawn_index--;
        } while (spawn_index >= 0);
    }

    if (((S_81934928_0 *)self)->unk_0C.u == 0x1E) {
        target = (void *)D_800814A8;
        if (target != NULL) {
            void *lookup_origin = target;
            while ((target = dungeonFindEligibleNearbyEntry(D_80082E80.tileX, D_80082E80.tileY, lookup_origin, target)) != NULL) {
                if ((((S_81934928_4 *)target)->unk_1C & 0x2000) == 0) {
                    copy_src = (Copy24 *)(u32)((S_81934928_0 *)self)->unk_09;
                    func_8009CE1C(target, 0x20, (s32)copy_src, 0xA,
                                  ((S_81934928_5 *)effect)->unk_2A, effect, 2);
                }
                decrementFlaggedItemParameters(target);
            }
        }
    }

    countdown = ((S_81934928_0 *)self)->unk_0C.s - 1;
    ((S_81934928_0 *)self)->unk_0C.s = countdown;
    if (countdown > 0) {
        return;
    }
    ((S_81934928_0 *)self)->unk_0C.s = 8;
    ((S_81934928_0 *)self)->unk_0A.u = 0xFF;
    return;

    case 0xFF:
    countdown = ((S_81934928_0 *)self)->unk_0C.s - 1;
    ((S_81934928_0 *)self)->unk_0C.s = countdown;
    if (countdown > 0) {
        return;
    }
    {
        u16 effect_flags;
        value = ((S_81934928_0 *)self)->unk_0E.s;
        effect_flags = ((S_81934928_0 *)self)->unk_0E.u;
        if ((value & 0x8000) != 0) {
            value = effect_flags & 0x7FFF;
            ((S_81934928_0 *)self)->unk_0E.u = value;
            return;
        }
    }
    dungeonStatus.unk_0C = 0;
    (*(u16 *)((u8 *)self + -2)) |= 0x8000;
    objectFlagBlock.flags |= 0x8000;

        return;
    default:
        return;
    }
}
