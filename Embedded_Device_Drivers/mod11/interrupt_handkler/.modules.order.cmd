cmd_/home/desd/Desktop/EDD/bb-codes/mod11/interrupt_handkler/modules.order := {   echo /home/desd/Desktop/EDD/bb-codes/mod11/interrupt_handkler/mod11-1.ko;   echo /home/desd/Desktop/EDD/bb-codes/mod11/interrupt_handkler/mod11-2.ko; :; } | awk '!x[$$0]++' - > /home/desd/Desktop/EDD/bb-codes/mod11/interrupt_handkler/modules.order