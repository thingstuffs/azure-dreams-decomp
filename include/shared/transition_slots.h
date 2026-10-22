#ifndef SHARED_TRANSITION_SLOTS_H
#define SHARED_TRANSITION_SLOTS_H

/* D_80083120: eight 8-byte slots just below gameWork (0x80083120..0x8008315F; no row reaches gameWork from this
 * base).  slus/w_8003F794 func_8003F794(type, param) scans from slot 7 down for type == 0 (free), then stores
 * type / 0 / param / 0 and returns the index (-1 if all are used); slus/w_8003F6F4 services type 5 and 6 slots and
 * frees them (type = 0).  The dungeon takes a type-6 slot with param 0x20 on a type-3 tile and sets unk_6 = 1.
 * Declared by slus/slot_transition.h's module as SlotTransitionSlot (now this type).  r78 type consolidation 7. */
/* One of eight resident transition slots initialized by reserve_runtime_slot.
 * tick_screen_fade_slots services absolute types 5 and 6 and frees completed fades. */
typedef struct TransitionSlot {
    /* 0x0 */ short type; /* slot kind: zero is free; absolute 5 decreases fade intensity, absolute 6 increases it */
    /* 0x2 */ short unk_2; /* elapsed fade-update counter for types 5/6; cleared when reserving a slot */
    /* 0x4 */ short param; /* reservation parameter; fade types 5/6 interpret it as duration in updates */
    /* 0x6 */ short unk_6; /* fade blend selector for types 5/6: zero subtracts, nonzero adds */
} TransitionSlot;

extern TransitionSlot runtime_transition_slots[8];

#endif
