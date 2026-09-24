# E758 retail feature and live-range map

The entire 698-word interval `8003E758..8003F240` was read. `lineage.json`
passes that exact retail slice to the unchanged `lineage_fingerprint.scan`
and `classify` APIs and independently checks all 698 words against the prior
full disassembly. The classifier returns **MIXED dialect**, no unique family:
56 macro evidence entries (28 lui/store pairs), six split stores, one detected
two-register split address, fourteen return copies, and 32 GP accesses.
The signatures are observations, not counts of independent compiler features.

## Frame and register roles

The frame is 48 bytes. Saved registers are ra at +44, s2 at +40, s1 at +36,
s0 at +32. Location and synchronization buffers are passed at sp+16 and sp+24.

| Region | s0 | s1 | s2 | Other significant carriers |
| --- | --- | --- | --- | --- |
| E76C..E8C0, initial dispatch | D814D3 state, including 0xFF reused by equality and stores | driver base 83958, rebuilt at queue loop entry | queue base 83968 in initial dispatch | a0 head; v0 head*3; a1 head*24; a2 selected entry |
| Initial command arms 0/1/2/9/D/E/15 | original state remains available where live | driver fields across calls | queue across calls and argument setup | v1 holds many CdSync results after v0 copy |
| E9EC..EAFC, read arm 6 | destination address, masked then restored to KSEG | pointer to read-info pair | sector count from high nine bits | v0 computes last destination word; stored to CC |
| ED0C..ED88, start stream | retry counter | disk-error constant 5 after driver dies | queue no longer live after location load | sync result v1; location at sp+16 |
| EDA4..EDD0, reset arm | retry counter | driver only before first reset call | no continuing queue use in this arm | shared stream-error block ED48 |
| EE14..EE5C, completion dispatch | previous state is consumed by state==1 test | no held driver needed | no held queue needed | v1 queue then opcode/table offset; v0 entry then jump-table target |
| EF54..EFA4, successful read | no new saved role | no new saved role | no new saved role | a0 driver base; a1 D3 pointer; head through a1-3 |
| F0A0..F0DC, completion stream retries | retries | 0xFF state kept over calls | unused | CDBUF rematerialized into a2 per iteration |
| F104..F168, completion stream status | no new role | no new role | unused | a1 D2 pointer; v1 queue then selected entry flag; a0 head |

These are path-specific live ranges. In particular, s1 is not one function-wide
driver invariant: the read arm and stream retry arm reuse it. The process-loop
back edges rematerialize the driver base.

## Access forms

| Data | Retail form and representative sites | Current source expression |
| --- | --- | --- |
| driver 83958 | two-register lui v0 / addiu s1 at E76C/E770; held +4/+10 accesses in initial arms; folded allocated-scratch stores at ED88, EE78, F018, F05C, F144, F20C | pointer local in initial region; direct object member in later single-use regions; declared 40-byte view at G32 |
| queue 83968 | two-register v0 to s2 at E7AC/E7B4; held base across initial calls; new v1 base for completion arms | queue pointer local, then fresh active queue/stream queue ranges |
| head D0 | GP loads/stores throughout; also D3-3 at EA3C/EA54, EE74/EE94, EF70/EF80; D2-2 at F120/F158/F168 | scalar GP declaration plus neighboring-pointer views |
| D1 tail | absolute split load E77C/E780 | 16-byte external view |
| D2/D3 state | absolute loads and 28 fresh $at macro-store pairs; ordinary absolute pointers for neighbor-relative head updates | multiple existing 16-byte extern aliases, not independently allocated buffers |
| D4 mode | GP store EA74, absolute parameter address EA58/EA5C | scalar plus D3[1] address |
| CC end word | GP store EA6C, load EEF0 then word dereference EEF8 | u32 holding a target address |
| 81450 result buffer | absolute parameter addresses E980/E984 and repeated calls; GP byte reads F048 and F0E4 | scalar status plus overlapping D81438+0x18 pointer; actual callee write extent requires separate audit |
| AD0/AD2/AD4/AD8 | GP byte EEE0; halfword EF18/EF2C; halfword F154; word EECC | unsigned byte/halfwords, signed CdReadSync result |
| 83164 | split absolute halfword F1F8/F1FC; lui duplicated in many jumps into F1FC | 40-byte declared external view; only first halfword read here |
| D81480/D814D8 | absolute load EA08/EA0C and buffer argument EEBC/EEC0 | 32-byte and 16-byte external views |

## Emission order and joins

Initial dispatch is a comparison tree, with explicit no-body cases 4/8/B/C/10/16.
Its emitted bodies are 0, 1, 2, 6, 9, D, E, 15, 1B, A, FF, FC. State FF is
also available as s0 for the FF comparison; the register comparison is not
evidence that the source omitted the constant. The no-op back edge jumps to
E770 with the driver's lui in its delay slot (E8E0/E8E4).

Completion state 1 uses the existing 28-entry retail table at 8002D5C0.
Emitted completion bodies are 0, 6, 9, 15, shared error/status tails, 1B.
The completion no-op back edge goes to E76C and stores the updated head in
its jump delay slot (EE90/EE94). Queue-empty handling follows the completion
bodies at F18C. Shared finish starts at F1F8; F1FC is also a target when its
lui was already emitted in the incoming jump delay slot. Early failures may
return directly through F224 and skip head masking/counter clearing.

## Feature ownership and concrete route

| Feature | Owner supported by present evidence | Route |
| --- | --- | --- |
| held bases, per-arm register reuse, source block order | C shape and register live ranges | Preserve map when normalizing shared CD declarations; `az-c-rebuild` for any resulting C-owned divergence |
| split la and duplicated high half on back edge | compiler split-address emission plus delayed-branch scheduling; CDK/4.1 signature | Current CDK `-G32 -fno-expensive-optimizations` baseline probe; do not replace with the old G8 sweep winner |
| mixed macro stores and allocated-scratch stores | current G32 raw compiler output already combines bare D2/D3 stores and split driver-field stores | Confirmed by raw/w_8003E758/a.s and the complete 698-word local-storage oracle; no new store-rewrite pass |
| GP extern loads/stores | genuine assembler distinguishes local storage from external declarations; current direct baseline measures remaining impact | Recover real local data ownership with measured storage bounds; never fake extents or add whitelist entries |
| overlapping 81450 byte/word/buffer views | data contract and source representation | Follow actual CdSync/CdControl write loop before selecting owner storage |
| noncontiguous owned storage | linker/module representation | Audit supported real sections before choosing a module layout; no gap-padding workaround |
| two existing pins in stream completion | unresolved C shape, lower priority than data correctness | Leave pins during ownership work; map F104..F168 is a later synthesis handoff |

The old report's G8 v3/v4 compiler sweep is superseded **as a diagnosis of
the current source**, not erased as historical measurement. Current source
has different declarations, aliases, scheduling flags and block structure.
No compiler impossibility or original translation-unit attribution follows
from either the mixed classifier or the old score table.

The completed local-storage oracle is recorded in `e758_owned_oracle_receipt.json`: all 698 words agree under stock, private generic and genuine 2.79-q after eight real-width tentative definitions. This resolves the instruction-generation question at the registered recipe, but does not place the discontiguous data or establish a production owner.
