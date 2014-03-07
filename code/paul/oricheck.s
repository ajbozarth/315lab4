main:
        lui     $4, 0x1234
        ori     $4, 0xABCD #Load in some data
        jr      $ra

#The following is the register output I got on unix3:
#0
#0
#0
#0
#1234abcd
#0
#1234abcd
#12
#34
#ab
#cd
#cd000000
#cdcd0000
#cdcdcd00
#cdcdcdcd


