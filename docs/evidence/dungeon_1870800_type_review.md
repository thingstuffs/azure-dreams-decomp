# 1870800 import return corrections and remaining review

Review: pending. Reviewer: pending. Module status: HOLD.

The current definition of func_800A4688 in src/dungeon/func_8009EF28.c returns
s32. The parent had declared s16. Its call already explicitly narrows the
result to s16, so changing the declaration to s32 preserves that narrowing.
The definition of func_800A56E0 in src/dungeon/func_8009FF80.c also returns
s32; the parent had declared void. The return value is ignored, so the s32
correction does not alter the emitted call. The package makes these two
corrections while retaining the parent's legacy composite representation.
Both existing production windows are required proofs.

The lane's separately compiled two-function native experiment also carries
these corrections. Its complete 2,424 bytes are unchanged against GNU,
genuine ASPSX 2.79, and retail. This is a native byte diagnostic, not a module
certificate or a production-window proof of the native source replacement.

The callback signature matches the parent's three-argument callback slots:
effect payload, position, primitive. Callback effect fields +0x48/+0x4A/
+0x4C/+0x4E agree with parent initialization; its owner at effect+0 points
back to the parent, whose +0x52 flag it marks. The position has six s32
coordinates/velocities through +0x14. Sprite reads at +4/+5/+0x14 and color
writes at +0x0C..+0x0E agree with the recovered 412-byte function.

The shared external runtime declarations are ObjectFlagBlock (16 bytes),
DungeonStatus (32 bytes), and ObjectNodeHeader (32 bytes). The two direction
tables are eight signed halfwords each in the SLUS load. The parent reads
animation descriptors D_800DE9D0 and D_800DEC28 through their first eight bytes
and passes their addresses onward; they remain external resident asset views.
The draft imports JSON reuses the existing proven resident/SLUS maps, and
claims no module-owned allocation for these objects.

No Layer-2 promotion or baseline record was manufactured for the recovered
callback. Fresh screening reports no pins, no tail jumps and no L5 residue,
but the live registered level is -1 and there is no landed Layer-2 history.
Also, two disjoint adjacent proven rowbase records cover the parent/callback,
while the unchanged module loader requires one covering region. Appending a
spanning record is invalid because the rowbase reader forbids overlaps. The
orchestrator must resolve representation of this union and the callback's
ordinary ladder evidence; this package weakens neither check.
