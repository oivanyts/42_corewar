.name 		"virus"
.comment	"can eat you to death"

live_init:
    st r1, 34

copy_init:
    ld %-38, r2 ;src
    ld %430, r3 ;dst (approximately)
    ld %68, r4 ;dword counter (approximately)
    ld %4, r7 ;dword size

live:
    live %0

copy:
    ldi r2, r4, r5 ;r5 = dword to copy
    sti r5, r3, r4 ;copy dword
    sub r4, r7, r4 ;reduce counter
    sub r4, r8, r6 ;counter == 0?
    zjmp %416 ;jump if yes

jmp:
    ld %0, r10 ; cf = 1
    zjmp %:live
