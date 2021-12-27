//
// Created by alvina on 25.12.21.
//

#ifndef SEMESTALNI_PRACE_PJC_ENTITY_H
#define SEMESTALNI_PRACE_PJC_ENTITY_H


#include <string>

struct Entity {
    int m_x;
    int m_y;
};

bool operator>(Entity one, Entity two);
bool operator<(Entity one, Entity two);
bool operator==(Entity one, Entity two);




#endif //SEMESTALNI_PRACE_PJC_ENTITY_H
