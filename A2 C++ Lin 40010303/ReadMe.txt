1. 3 Output sceenshots has attached for your convinient proof reading.

2. Command.h and Command.cpp has meet all requirement from .PDF, the main fuction i'm using is
parse, parseAddress, and validate.

The parse will divide String(p1,2) to symbol(p) and address range(1,2).
parseAddress will divide range(1,2) to address1(1) and address2(2).
validate was created for checking invalid address such as: 1$,$-,&%^.

3. All LineEd functions are coded from A2.PDF requirement. 

Two additional functions has been created: a) strToInt and b) savefile
strToInt is for convert Command.h output string type to int type, it will handle some speicial
cases such as <0 range and $,and. .
savefile is created for handle output file.

4. No new or delete has been used. The idea is using buffer&clipboard to operate memory.

5. The  string filename{"abc.txt"}; has been difined for testLineEd.