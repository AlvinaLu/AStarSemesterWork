//
// Created by alvina on 25.12.21.
//

#include "Entity.h"



bool operator>(Entity one, Entity two) {
    return (one.m_x*1000 + one.m_y > two.m_x*1000 + two.m_y);
}

bool operator<(Entity one, Entity two) {
    return (one.m_x*1000 + one.m_y < two.m_x*1000 + two.m_y);;
}
bool operator==(Entity one, Entity two) {
    return (one.m_x == two.m_x && one.m_y == two.m_y);
}