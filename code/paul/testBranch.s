main:
         ADDIU   $6, $0, 0x1
         ADDIU   $7, $0, 0
         ADDIU   $8, $0, 0x5

loop1:   
         ADDIU   $9, $9, 0x1
         SLTI    $10, $9, 0x5
         BEQ     $10, $6, loop1
         
loop2:
         ADDIU   $11, $11, 0x1
         SLTIU   $12, $11, 0x5
         BNE     $12, $7, loop2

loop3:
         ADDIU   $13, $13, 0x1
         SLT     $14, $13, $8
         BLEZ    $14, loop3

         ADDIU   $16, $0, 0xBBBB
         ADDIU   $15, $0, 0x01
         BNE     $15, $0, test1
         ADDIU   $16, $0, 0xAAAA
test1:
         ADDIU   $18, $0, 0xBBBB
         ADDIU   $17, $0, 0
         BEQ     $17, $0, test2
         ADDIU   $18, $0, 0xAAAA
test2:
         ADDIU   $20, $0, 0xBBBB
         ADDIU   $19, $0, 1 
         BLEZ    $19, test3
         ADDIU   $20, $0, 0xAAAA
test3:
         jr      $ra



