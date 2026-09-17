# Exact CDK reload-CSE trace

The Luna dump boundary is confirmed more precisely by a read-only debugger
trace of the actual gcc-2.7.2-cdk/cc1 binary. Compiler SHA-256:
90db2db7bcfe372244ca4d9785a7bfbf7613d711f69ee3bfe6c91d82a85e611d.
Candidate is r51 v3_literal_zero.c, source SHA-256:
a1b853645c2d1e305798cb704c69c143403e90194f86ad4a2df845eb5cd9fcfd.

At reload_cse_simplify_set (0x08180ab7), UID362 enters as s1 <- const_int0.
Its reload_cse_regno_equal_p calls (0x081807a1) reject registers0..16 and18;
register17 is the destination and is skipped. Register19 (s3) is the first
accepted equivalent zero. On return, SET_SRC is a register19 RTX. This is
exactly the previously observed move s1,s3. No compiler RTL or data was modified; debugger breakpoints were used.
The normalized traced assembly equals an independent ordinary driver compile
of the same source and fixed -O2 -G0 flags. The candidate remains one retail
substitution away, not exact. Raw EAX on the untyped simplifier return is logged
only as a machine observation and is not interpreted as a C return value.

This attributes the rewrite to post-allocation reload CSE, not earlier CSE and
not global register assignment alone. Stock 2.8.1 reload1.c:8178 onward describes
the corresponding search/replacement algorithm, but exact CDK attribution comes
from the measured executable rather than assuming that source is identical.
The hardware zero register's comparison returns false in this value cache;
its architectural constancy does not guarantee that this pass will select it.

Next experiment: trace the zero-value cache invalidation/recording across the
second traversal's real control-flow joins, then select at most two source
lifetimes that retain the retail s1/s2 allocation while avoiding that cached
copy. The previous row-entry reset already changes allocation order, so simply
repeating it is ruled out. No fake use, compiler state patch, new constraint or
function-specific backend exception is a candidate repair.
