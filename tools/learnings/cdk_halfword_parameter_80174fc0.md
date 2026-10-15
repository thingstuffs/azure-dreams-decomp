# CDK halfword parameter and saved-register roles

Scope: independently recovered `func_80174FC0`, DUNGEON file
`0x9C37C0..0x9C38E4`, stock GCC 2.7.2-cdk, `-O2 -G0`, stock maspsx
2.79 and genuine ASPSX 2.79 `-q -G0 -0`.

The retail creator holds its direction argument in s2 and its draw-value argument
in s3. A signed-word direction parameter produced the same 40-byte frame and
292-byte body, but exchanged those two saved-register roles. The direction is
stored only as a halfword at state+0x14. Declaring that parameter as `s16`
reproduces the retail roles without pins, additional operations or flags.

The retail scale stores are +0x1E followed by +0x1C. The assignment
`draw->scale_x = draw->scale_y = 0x1000` expresses that order. The opposite
chain reverses the two stores. With both evidence-based changes, the complete
292-byte function matches retail and independently resolved genuine ASPSX bytes,
with zero masks and no raw substitution. No claim that the halfword idiom has
the same allocation effect in other functions or compilers is made.

The standalone lineage scanner found no uniquely discriminating store-emission
signature in this function. CDK is the assigned cohort recipe and an exact
explanation; it is not a uniquely identified historical lineage here.
