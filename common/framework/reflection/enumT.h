//
// Created by Admin on 26-8-22.
//

#define enumName enumT
#define enumBase enum enumT
enumStart
enumEntry(a)
enumEntry(b)
enumEntry(c)
enumEnd
#undef enumName
#undef enumBase
#undef enumStart
#undef enumEntry
#undef enumEnd
