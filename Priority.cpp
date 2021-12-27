//
// Created by alvina on 27.12.21.
//

#include "Priority.h"

bool operator>(Priority one, Priority two){
    return (one.priority > two.priority);
}
bool operator<(Priority one, Priority two){
    return (one.priority < two.priority);
}
bool operator==(Priority one, Priority two){
    return (one.priority == two.priority);
}