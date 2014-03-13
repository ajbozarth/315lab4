main:
         ADDIU   $16, $0, 0x1
         ADDIU   $17, $0, 0
         ADDIU   $18, $0, 0x5

loop1:   
         ADDIU   $19, $19, 0x1
         SLTI    $20, $19, 0x5
         BEQ     $20, $16, loop1
         
loop2:
         ADDIU   $21, $21, 0x1
         SLTIU   $22, $21, 0x5
         BNE     $22, $17, loop2

loop3:
         ADDIU   $23, $23, 0x1
         SLT     $24, $23, $18
         BLEZ    $24, loop3

         ADDIU   $25, $0, 0x01
         ADDIU   $26, $0, 0xBBBB
         BNE     $25, $0, test1
         ADDIU   $26, $0, 0xAAAA
test1:
         ADDIU   $27, $0, 0
         ADDIU   $28, $0, 0xBBBB
         BEQ     $27, $0, test2
         ADDIU   $28, $0, 0xAAAA
test2:
         ADDIU   $29, $0, 1 
         ADDIU   $30, $0, 0xBBBB
         BLEZ    $29, test3
         ADDIU   $30, $0, 0xAAAA
test3:
         jr      $ra



