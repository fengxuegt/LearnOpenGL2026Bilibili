//
// Created by fengxuegt on 2026/2/26.
//

#ifndef CHECKERROR_H
#define CHECKERROR_H
#ifdef DEBUG
#define LWGLCALL(func) func;checkError()
#else
#define LWGLCALL(func) func
#endif

void checkError();



#endif //CHECKERROR_H
