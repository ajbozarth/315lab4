main:
         ADDIU    $11, $11, 0xFFFF
         ADDIU    $12, $12, 0xF000
         ADDIU    $13, $13, 0x0001
         ADDIU    $14, $14, 0xAAAA
         ADDIU    $15, $15, 0x2C34

         SRA      $16, $11, 1
         SRA      $17, $12, 1
         SRA      $18, $13, 1
         SRA      $19, $14, 1
         SRA      $20, $15, 1
         
         SRA      $21, $11, 2
         SRA      $22, $12, 2
         SRA      $23, $13, 2
         SRA      $24, $14, 2
         SRA      $25, $15, 2

         SRA      $26, $11, 20 
         SRA      $27, $12, 20 
         SRA      $28, $13, 20
         SRA      $29, $14, 20
         SRA      $30, $15, 20

         jr       $ra
