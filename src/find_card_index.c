#include"func.h"

int32_t find_card_index(sPile pile,eType type,int32_t *pCard_index){
    for(int i=0;i<pile.num;i++){
		if(pile.card[i].type==type){
            *pCard_index = i;
            return 1;
        }
	}
    return 0;
}