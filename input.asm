add x3, x4, x5
addi x3, x3, 10

for:
bne x3, x2, done
lw x2, 10(x3)
jal x2, for

done:
sw x1, 13(x3)