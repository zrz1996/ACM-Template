#!/bin/bash
while true; do	
./make_data	
./prog1
./prog2
diff ans1.out ans2.out	
if [ $? -ne 0 ] ; then break; fi
done	
