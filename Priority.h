//
// Created by alvina on 27.12.21.
//

#ifndef SEMESTALNI_PRACE_PJC_PRIORITY_H
#define SEMESTALNI_PRACE_PJC_PRIORITY_H


#include "Entity.h"

struct Priority {
Entity entity;
double priority;
};
bool operator>(Priority one, Priority two);
bool operator<(Priority one, Priority two);
bool operator==(Priority one, Priority two);

#endif //SEMESTALNI_PRACE_PJC_PRIORITY_H
