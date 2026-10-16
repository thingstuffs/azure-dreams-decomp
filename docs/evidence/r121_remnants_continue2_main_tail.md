# MAIN complete tail recovery site map

All 82 retail instructions: continue2_main_26E3A0.s. Binary is equal over
328 bytes to the independently registered TOWN function at the same offset.
The fixed 2.6.3-G0 recipe is inherited from that exact twin. The fingerprint
is run on that registered twin (the new MAIN body is not in registry yet).

Frame: 120 bytes, saved ra + s0/s1/s2/s3; s2 holds panel, s3 holds count.
First call computes count. count<3 sets a0=panel+0x80, constant string a1,
and a2=1; second path uses signed reciprocal divide by 3. s1 holds number
buffer sp+0x50; s0 holds text buffer sp+0x10 across string joins. Both paths
join at the display call. Loop keeps a2=index and recomputes derived offsets;
conditional count<3 selects two lines, otherwise one. It writes each text
pointer then two halfword coordinates. Epilogue exactly restores frame/roles.

The sole first-candidate residual belongs to C declaration shape: declaring
the five-byte constant as a u8 array loses four-byte alignment and creates
lwl/lwr and swl/swr, adding two words. Retail loads its first word directly
at D_80400714 and its signed byte at +4, while the next constant begins at
+8. A bounded struct { s32 word; s8 byte; } records that alignment and extent;
memcpy still copies exactly five semantic bytes. No literal page or fake
alignment attribute is used. All other changes are explicit imported call
prototypes. Gate 0 frame/register roles already matched before this change.

Lineage fingerprint (neutral; cohort recipe retained):
```
== lineage fingerprint: func_802EE3A0 (overlay town, 82 words) ==
$at macro stores             0   
compiler-split stores        0   
held-page bases (s-reg)      0   
store in jal/j slot          0   
two-reg split la             0   
zero-equiv copies            0   
return-copy after call       1   [8] move $s3, $v0 after call
$gp refs                     0
VERDICT: insufficient store-emission evidence (few globals?); return-copy habit (plain-2.7.2 trait)
claimed '2.6.3' cannot be tested from family-neutral/insufficient evidence
```
