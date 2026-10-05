#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CE748_0 {
    void * unk_00;
    u8 pad_04[0x13];
    u8 unk_17;
    u8 pad_18[0x10];
    s32 unk_28;
    u8 pad_2C[0x34];
    void * unk_60;
    void * unk_64;
    u8 pad_68[0x34];
    s16 unk_9C;
} S_800CE748_0;   /* record in func_800CE748; pointer addresses record offset 0x14 */

typedef struct S_800CE748_1 {
    u8 unk_00;
    u8 unk_01;
    s8 unk_02;
} S_800CE748_1;   /* firstEntry in func_800CE748 */

typedef struct S_800CE748_2 {
    u8 unk_00;
    u8 pad_01[0x1];
    s8 unk_02;
} S_800CE748_2;   /* secondEntry in func_800CE748 */

typedef struct S_800CE748_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CE748_3;   /* objectData in func_800CE748 */


extern u8 D_800E3D40[];
s32 func_800990FC(void);
s32 func_80099194(u8 *src, u8 *dst);
void func_80099290(s8 *byte_ptr);
s32 func_8009929C(s8 value, s8 *dest);
s32 func_8009955C(void *, s32);
void func_800A56E0(s32);
void func_800A5720(s8 *text);
void func_800A6508(void);
s32 func_800A6D30();
void func_800C5BBC(s16 x, s16 y, s16 z, s32 sprite_data, u16 sprite_id, s16 play_sound);
s32 func_800C80F0(void *);

extern u8 D_800E1B76[18];
extern u8 D_800E1B87[18];
extern u8 D_800E1B99[18];
extern u8 D_800E1BAA[18];

s32 func_800CE748(void *record, s32 unused1, s32 unused2, s32 unused3) {
    s32 randomValueSecond;
    s32 randomValueFirst;
    s32 secondLookupValue;
    s32 firstLookupValue;
    s32 initialValue;
    s32 entryCode;
    s32 currentValue;
    s16 entryFlags;
    s32 triggerFlags;
    s32 entryValue;
    S_800CE748_1 *firstEntry;
    S_800CE748_2 *secondEntry;
    S_800CE748_3 *objectData;

    triggerFlags = 0;
    entryFlags = 0;
    if (func_800C80F0(record) == 0) {
        s16 probability;
        s32 random_mod;
        firstEntry = ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_60;
        if (firstEntry != NULL) {

            entryFlags = 1;
            if (firstEntry->unk_01 == 0xF) {
                s32 is_one;

                is_one = firstEntry->unk_00 == 1;
                entryFlags = is_one;
            }
            if (*D_800E3D40 == 0) {
                                /* garbage-passthru: a1/a3 are residue from func_800C80F0, without a defined C value. */
                randomValueFirst = func_800A6D30() & 0xFFFF;
                if (((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17 != 0) {
                    random_mod = randomValueFirst % ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17;
                    probability = random_mod;
                } else {
                    probability = 0;
                }
            } else {
                probability = 0;
            }
            if (probability < 0x40) {
                if (!(entryFlags & 1)) {
                    if (firstEntry->unk_02 >= -0x62) {
                        firstEntry->unk_02 = (s8) ((u8) firstEntry->unk_02 - 1);
                    }
                }
                triggerFlags = 1;
            }
        }
        secondEntry = ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_64;
        if (secondEntry != NULL) {

            entryValue = secondEntry->unk_00;
            entryCode = entryValue & 0xFF;
            if ((entryCode == 1) || (entryCode == 7) || (((u32) (entryValue - 2) < 2U) != 0)) {
                entryFlags |= 2;
            }
            if (*D_800E3D40 == 0) {
                                /* garbage-passthru: a1/a3 remain residue from earlier calls. */
                randomValueSecond = func_800A6D30() & 0xFFFF;
                if (((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17 != 0) {
                    random_mod = randomValueSecond % ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17;
                    probability = random_mod;
                } else {
                    probability = 0;
                }
            } else {
                probability = 0;
            }
            if (probability < 0x40) {
                if (!(entryFlags & 2)) {
                    if (secondEntry->unk_02 >= -0x62) {
                        secondEntry->unk_02 = (s8) ((u8) secondEntry->unk_02 - 1);
                    }
                }
                triggerFlags |= 2;
            }
        }
    }
    if (((S_800CE748_0 *)((u8 *)record - 0x14))->unk_28 & 0x4000) {
        if ((triggerFlags << 0x10) == 0) {
                        /* garbage-passthru: a3 remains residue from earlier calls. */
            func_800A6508();
        } else {
                        /* garbage-passthru: a3 remains residue from earlier calls. */
            initialValue = func_800990FC();
            currentValue = initialValue;
            if (triggerFlags & 1) {
                firstLookupValue = func_8009955C(((S_800CE748_0 *)((u8 *)record - 0x14))->unk_60, currentValue);
                {

                    if (!(entryFlags & 1)) {
                        currentValue = func_80099194(D_800E1B76, firstLookupValue);
                    } else {
                        currentValue = func_80099194(D_800E1B87, firstLookupValue);
                    }
                }
                if (triggerFlags & 2) {
                    currentValue = func_8009929C(0xA, currentValue);
                }
            }
            if (triggerFlags & 2) {
                secondLookupValue = func_8009955C(((S_800CE748_0 *)((u8 *)record - 0x14))->unk_64, currentValue);
                {

                    if (!(entryFlags & 2)) {
                        currentValue = func_80099194(D_800E1B99, secondLookupValue);
                    } else {
                        currentValue = func_80099194(D_800E1BAA, secondLookupValue);
                    }
                }
            }
            func_80099290(currentValue);
            func_800A5720(initialValue);
        }
    }
    if ((triggerFlags << 0x10) != 0) {
        objectData = ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_00;
        if (!(objectData->unk_14 & 0x8000)) {
            func_800C5BBC((objectData->unk_24 << 6) | 0x20, (objectData->unk_25 << 6) | 0x20,
                ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_9C, 0xC0C040, 0x20, 0);
            func_800A56E0(0x615);
        }
    }
    return 1;
}
