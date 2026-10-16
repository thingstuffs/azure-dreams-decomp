#include "modules/dungeon_ovl_1829800.h"

void dungeonInitializeChildrenOrShutdown(void *owner)
{
    u32 state;
    s32 stop_state;
    s32 source_slot;
    s32 object_or_kind;
    s32 signed_kind;
    s32 shifted_kind;
    s32 parent_value;
    s32 entity_flags;
    s32 flags_mask;
    s32 clear_pairs_left;
    u16 spawn_bits;
    u16 owner_bits;
    u16 child_bits;
    u16 alloc_bits;
    s32 cleanup_flags;
    s32 alloc_flags;
    register void *entity_arg;
    void *child;
    u8 *status_page;
    s32 mode;
    u8 *flag_page;
    u8 *cleanup_page;
    u8 *status;
    void *source;
    void *parent;
    void *main_child;
    void *aux_child;
    void *child_object;
    void *alloc_container;
    void *setup_container;
    s32 mask_work;
    void *spawn_container;
    void *spawn_child;
    void *spawn_resource;
    void *entity;

    status_page = (u8 *)((s8 *)(&gameWork));
    state = ((S_80026190_0 *)owner)->unk_1C.s;
    stop_state = 2;
    if (state == stop_state) {
        if ((*(s16 *)D_8002715C) == 0) {
            (*(u16 *)((u8 *)owner + -2)) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        (*(s16 *)D_8002715C) = 0;
        return;
    }

    status = status_page;
    if (((S_80026190_1 *)status)->unk_08 & 0x20) {
        main_child = ((S_80026190_0 *)owner)->unk_00;
        if (main_child != NULL) {
            ((S_80026190_2 *)main_child)->unk_1C = 3;
        }
        aux_child = ((S_80026190_0 *)owner)->unk_04;
        if (aux_child != NULL) {
            ((S_80026190_3 *)aux_child)->unk_0E = 3;
        }
        D_8002715A = 1;
        ((S_80026190_0 *)owner)->unk_1C.s = stop_state;
        (*(s16 *)D_8002715C) = 0;
        func_8004E130();
        return;
    }

    if (state != 0) {
        return;
    }

    object_or_kind = (s32)func_8003FC64(0x12);
    if (object_or_kind == 0) {
        return;
    }
    ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = (void *)dungeonUpdateSelectionMenuAnimation;
    child = (u8 *)object_or_kind + 0x20;
    ((S_80026190_0 *)owner)->unk_00 = child;
    ((S_80026190_5 *)child)->unk_26 = ((S_80026190_0 *)owner)->unk_26;

    child_object = func_8003FC64(0x112);
    ((S_80026190_5 *)child)->unk_08 = child_object;
    if (child_object == NULL) {
        alloc_container = ((S_80026190_0 *)owner)->unk_00;
        alloc_bits = ((S_80026190_6_pre *)alloc_container)[-1].unk_00;
        (*(u16 *)((u8 *)alloc_container + -2)) = alloc_bits | 0x8000;
        alloc_flags = objectFlagBlock.flags;
        ((S_80026190_0 *)owner)->unk_00 = NULL;
        alloc_flags |= 0x8000;
        objectFlagBlock.flags = alloc_flags;
        return;
    }

    object_or_kind = (s32)child_object;
    ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = (void *)dungeonUpdateDirectionalObjectFade;
    ((S_80026190_4 *)((void *)object_or_kind))->unk_78 = ((S_80026190_0 *)owner)->unk_00;
    if ((((S_80026190_5 *)child)->unk_14 = dungeonAllocateSpriteDataObject((s32)child)) == NULL) {
        setup_container = ((S_80026190_0 *)owner)->unk_00;
        owner_bits = ((S_80026190_7_pre *)setup_container)[-1].unk_00;
        cleanup_page = (u8 *)0x80080000;
        ((S_80026190_7_pre *)setup_container)[-1].unk_00 = owner_bits | 0x8000;
        ((S_80026190_0 *)owner)->unk_00 = NULL;
        mask_work = (s32)(((S_80026190_5 *)child)->unk_08);
        cleanup_flags = ((S_80026190_8 *)cleanup_page)->unk_14A0;
        child_bits = ((S_80026190_9 *)((void *)mask_work))->unk_1E;
        cleanup_flags |= 0x8000;
        ((S_80026190_8 *)cleanup_page)->unk_14A0 = cleanup_flags;
        ((S_80026190_9 *)((void *)mask_work))->unk_1E = child_bits | 0x8000;
        ((S_80026190_5 *)child)->unk_08 = NULL;
        return;
    }

    for (source_slot = 0; source_slot < 2; source_slot++) {
    flag_page = (u8 *)0x80080000;
    source = *(void **)(((u8 *)D_800E3D7C) + (source_slot * 4) + 0xAC);
    if (source != NULL) {
        object_or_kind = 0x1E;
        if (!(((S_80026190_10 *)source)->unk_14 & 0x20000000)) {
            object_or_kind = ((S_80026190_10 *)source)->unk_13;
        }
        if (((S_80026190_10 *)source)->unk_13 == 0x2E) {
            object_or_kind = ((S_80026190_10 *)source)->unk_A8;
            func_8004397C(source);
        } else {
            func_8004397C(source);
        }

        status_page = (u8 *)0x80010000;
        mode = ((S_80026190_11 *)status_page)->unk_2090;
        if (mode == 1) {
            if ((s16)object_or_kind == 2) {
                object_or_kind = 0x39;
            }
        }
        shifted_kind = object_or_kind << 16;
        signed_kind = shifted_kind >> 16;

        entity = func_800A0B94(signed_kind, func_800A1618(signed_kind, 3), 1);
        drainCdCommandQueue();
        entity = ((SpawnFunc)entity)(1, 0, 0, ((S_80026190_10 *)source)->unk_88);

        status_page = (u8 *)0x80010000;
        mode = ((S_80026190_11 *)status_page)->unk_2090;
        if ((mode == 1) && (signed_kind == 0x39)) {
            object_or_kind = 2;
        }

        if (entity == NULL) {
            spawn_container = ((S_80026190_0 *)owner)->unk_00;
            ((S_80026190_12_pre *)spawn_container)[-1].unk_00 |= 0x8000;
            ((S_80026190_0 *)owner)->unk_00 = NULL;

            spawn_child = ((S_80026190_5 *)child)->unk_08;
            ((S_80026190_13 *)spawn_child)->unk_1E |= 0x8000;
            ((S_80026190_5 *)child)->unk_08 = NULL;

            spawn_resource = ((S_80026190_5 *)child)->unk_14;
            ((S_80026190_14 *)spawn_resource)->unk_1E |= 0x8000;

            parent_value = ((S_80026190_15 *)flag_page)->unk_14A0.s;
            entity_arg = ((S_80026190_5 *)child)->unk_0C;
            ((S_80026190_5 *)child)->unk_14 = NULL;
            flags_mask = parent_value | 0x8000;
            ((S_80026190_15 *)flag_page)->unk_14A0.u = flags_mask;
            if (entity_arg != NULL) {
                spawn_bits = ((S_80026190_16 *)entity_arg)->unk_1E;
                ((S_80026190_15 *)flag_page)->unk_14A0.s = flags_mask;
                ((S_80026190_16 *)entity_arg)->unk_1E = spawn_bits | 0x8000;
                ((S_80026190_5 *)child)->unk_0C = NULL;
            }
            return;
        }

        func_80042640(entity, (s16)object_or_kind);
        ((S_80026190_17 *)entity)->unk_14 = 0;
        ((S_80026190_17 *)entity)->unk_1C = 0;
        func_80042710(entity, source);

        ((S_80026190_17 *)entity)->unk_13 = object_or_kind;
        for (clear_pairs_left = 3; clear_pairs_left >= 0; clear_pairs_left--) {
            ((u8 *)entity)[clear_pairs_left * 2 + 0x2C] = 0;
            ((u8 *)entity)[clear_pairs_left * 2 + 0x2D] = 0;
        }

        mask_work = 0xBFFFFFFF;
        entity_arg = entity;
        entity_flags = 0x64;
        ((S_80026190_17 *)entity)->unk_25 = entity_flags;
        ((S_80026190_17 *)entity)->unk_88 = 0;
        ((S_80026190_17 *)entity)->unk_1C &= ~0x1EF8;
        ((S_80026190_17 *)entity)->unk_1C &= mask_work;
        ((S_80026190_17 *)entity)->unk_1C |= 0x40000;
        func_8009A028(entity_arg);

        flags_mask = ((S_80026190_10 *)source)->unk_14;
        parent = ((S_80026190_17_pre *)entity)[-1].unk_00;
        flags_mask &= 0x20000000;
        if (flags_mask) {
            parent_value = func_800429E4(source) << 2;
            ((S_80026190_18 *)parent)->unk_12 = parent_value;
        } else {
            parent_value = ((S_80026190_19 *)(((S_80026190_10_pre *)source)[-1].unk_00))->unk_12;
            ((S_80026190_18 *)parent)->unk_12 = parent_value;
        }

        object_or_kind = (s32)entity - 0x20;
        *(s32 *)((u8 *)child + (source_slot * 4) + 0xC) = object_or_kind;
        ((S_80026190_17 *)entity)->unk_5C = ((S_80026190_4 *)((void *)object_or_kind))->unk_10.u | 0x80000000;
        ((S_80026190_17 *)entity)->unk_58 = ((S_80026190_0 *)owner)->unk_00;
        ((S_80026190_17 *)entity)->unk_6A = source_slot;
        func_80044A50((void *)object_or_kind);
        dungeonRetireTrackedEffectById((void *)object_or_kind);
        func_8009A3D0(((S_80026190_18 *)parent)->unk_24, ((S_80026190_18 *)parent)->unk_25, 0x300);
        ((S_80026190_17 *)entity)->unk_87 = 0xFF;
        ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = (void *)dungeonDrawAndRestoreFadingObject;
    }
    }

    object_or_kind = (s32)func_8003FC64(0x212);
    if (object_or_kind != 0) {
        ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = (void *)dungeonInitializeFadingEffect;
        ((S_80026190_0 *)owner)->unk_04 = (u8 *)object_or_kind + 0x20;
    }
    ((S_80026190_0 *)owner)->unk_1C.u++;

    return;
}
