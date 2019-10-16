#ifndef FACTORY_H_INCLUDED
#define FACTORY_H_INCLUDED

#include "cocos2d.h"
#include "Pawn.h"
/*


*/

class MeteorFactory {
public:
    static Pawn* createNewMeteor();
};


#endif // FACTORY_H_INCLUDED
