# Complete TOWN phase callbacks

Seven complete sections (520 bytes) use five new C definitions and two shared
placements. Their load views are the existing config/link/town ll3a/ll34 images
named in the portable town_phase_map. Their runtime addresses and bounded gate
windows follow those validated physical image mappings, without changing an
existing owner. The common nonzero body is defined at +64B0F8 and placed at
+64D0F8 and +6579D4 with three explicit helper-address substitutions.

The linked-value query returns s32 and takes no input. The current-entry flag
setter takes no input and returns void; incidental a0 in a branch delay slot is
not an argument. The checked-entry worker takes (void *, s32), returning its
explicit 0/1 result. The >=5 variant has the same contract. Phase-specific
friendly aliases name those existing helper addresses; new definition homes
require no placement bindings. config/names.tsv supports aliases for a shared
runtime address across distinct phase images.

The +49EBC4 callback returns 1 only after the script-mask query for 0x5C7 and
the indexed flag setter execute, otherwise 0. The +68DCC4 routine sets flag
0x94C and returns void. All seventeen physical call sites in the validated
68D000 image discard its result; all sixteen current C sources now include the
owning town/scene.h declaration and use the same name, replacing mixed legacy
void/s32 declarations. The +4CFA14 routine invokes service +1EC, selects its
fixed data pointer, and clears flag 0x591. That loaded service is the existing
void start_keima_func(void); the same-sized table padding is given that type.

The lane carries source/callee hashes, caller audit and complete-section
receipts. The ordinary compiler is 2.7.2-cdk -G0. A fresh full changed-file union
and repeat replay are required before counting these entries as delivered.
