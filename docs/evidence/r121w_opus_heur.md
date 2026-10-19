# r121w_opus_heur: volatile-free donors and their twelve bank twins

Base: B16d (`cefe76079`). Twelve heuristic-only DUNGEON spans (16,920 B) become link-list placements of two
existing home TUs, after the homes' `volatile` stores were replaced by ordinary C. No new TU, no pins, asm,
volatile, NON_MATCHING, pragma or goto were added.

## Donor repairs (byte-neutral, per-row exact at the unchanged recipe 2.7.2-cdk-G0)

Both homes stored the `scan_monster_along_heading` result through `*(void * volatile *)(actor + 0x60)` and then
folded the two signed step bytes with hand-written `if (x < 0) x = -x`. The volatile kept the store ahead of
the two `lb` loads. The natural spelling, used by the already matched sibling `func_80A49170`
(start_selected_move_and_reset_action), is a typed store to `EntityRec.target` and two `s8` locals passed
through `abs()`: the builtin expansion and the `s8` temporaries reproduce retail's order and registers
(`sw v0,96(s0)` right after the call, `x`/`y` in v0/v1). The `s32` locals with `abs()` leave a 12-word
difference; the field store with the `if` form leaves 24.

| home row | function | change | score |
|---|---|---|---|
| dungeon/func_80AF1A80 (true func_80173280) | advance_actor_spell_effect_sequence | volatile store -> `action->target = ...`; `s8` x/y with `abs()` | exact, 0 |
| dungeon/func_80A734C0 (true func_80172CC0) | advance_actor_stored_path_2 | the same, with typed `EntityRec` field accesses for the store, facing and step bytes | exact, 0 |

The pre-existing `goto` arms in both homes are unchanged (goto-lane debt, not new C). A goto-free rewrite of
func_80AF1A80's kind dispatch (`switch` with `break`, as in its sibling) is branch-exact but swaps s0/s1 for
`action`/`kind_data` (48 words); not adopted.

## Placements

Each twin is the same function at the same in-bank offset of a bank of the home's layout family
(`bank_b0f000_family`, `bank_a91000_family`), inside a proven rowbase region; the home rows gain their own
home entries in `config/link/dungeon/bank_b0f000.json` and `bank_a91000.json`. Every twin was an attested
`proven` instance (ledger/instances.jsonl) that had been parked as `partial` only because the home text changed
after its proof epoch; the new events record its promotion to the placement row. Rebinding is by rules 1, 3 and 4
(home-image symbols shifted by the bank delta), e.g. for func_80AF7A80:
`D_80175988 -> D_8016F988, func_80170CF8 -> func_8016ACF8, func_801717F4 -> func_8016B7F4, func_80173280 -> func_8016D280`.

| row | file | size | vma | image | home |
|---|---:|---:|---|---|---|
| dungeon/func_80AF7A80 | 0xB17A80 | 1420 | 0x8016D280 | bank_b15000 | dungeon/func_80AF1A80 |
| dungeon/func_80AFDA80 | 0xB1DA80 | 1420 | 0x80167280 | bank_b1b000 | dungeon/func_80AF1A80 |
| dungeon/func_80B03A80 | 0xB23A80 | 1420 | 0x80161280 | bank_b21000 | dungeon/func_80AF1A80 |
| dungeon/func_80B09A80 | 0xB29A80 | 1420 | 0x8015B280 | bank_b27000 | dungeon/func_80AF1A80 |
| dungeon/func_80B0FA80 | 0xB2FA80 | 1420 | 0x80155280 | bank_b2d000 | dungeon/func_80AF1A80 |
| dungeon/func_80B15A80 | 0xB35A80 | 1420 | 0x8014F280 | bank_b33000 | dungeon/func_80AF1A80 |
| dungeon/func_80A794C0 | 0xA994C0 | 1400 | 0x8016CCC0 | bank_a97000 | dungeon/func_80A734C0 |
| dungeon/func_80A7F4C0 | 0xA9F4C0 | 1400 | 0x80166CC0 | bank_a9d000 | dungeon/func_80A734C0 |
| dungeon/func_80A854C0 | 0xAA54C0 | 1400 | 0x80160CC0 | bank_aa3000 | dungeon/func_80A734C0 |
| dungeon/func_80A8B4C0 | 0xAAB4C0 | 1400 | 0x8015ACC0 | bank_aa9000 | dungeon/func_80A734C0 |
| dungeon/func_80A914C0 | 0xAB14C0 | 1400 | 0x80154CC0 | bank_aaf000 | dungeon/func_80A734C0 |
| dungeon/func_80A974C0 | 0xAB74C0 | 1400 | 0x8014ECC0 | bank_ab5000 | dungeon/func_80A734C0 |

Proof of record: one scoped window gate over every window whose inputs these edits change (the two homes'
windows and every window holding a placement bound to an edited link list); result in the lane gate log.

## Holds examined (not admitted)

- 724-B family (home dungeon/func_809A1A8C, six twins 0x9C7A8C..0x9E5A8C) and its 708-B copy (home
  dungeon/func_812A85D4, six twins 0x12CE5D4..0x12EC5D4): both homes spell the animation table as an integer
  page `anim_table = 0x80170000; anim_table += 0x5EB8` (resp. its 708-B equivalent). Every other differing word is
  a shifted relocation, but this `addiu` low half (0x5EB8 at home, 0xFEB8 in the -0x6000 bank) is a literal with no
  ELF relocation, so no placement can produce it. Symbolic rewrites measured on func_809A1A8C: direct
  `D_80175EB8` use 10 words (case-1 a0/a1 swap once `anim_table` loses its late uses); `anim_table = D_80175EB8`
  2 words (the HIGH temporary lands in v0, `addiu a1,v0,...`, not tied to a1 as retail's `lui a1`/`addiu a1,a1`);
  per-arm symbolic assignment 5. Next: a spelling that keeps the address in a block-local pseudo (tie) while
  something else keeps case 1's allocation priority.
- dungeon/func_80284068 (556 B twin at 0x51F868): home lives in the engine module with two `volatile` loop
  cursors over integer pages and the twin sits in an xfer image; not attempted in this bounded pass.
