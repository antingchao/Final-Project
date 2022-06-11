#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"src/def.h"
#include"src/func.h"
int main(){
	int32_t num;
	while(1){
		system("clear");
		printf("Please enter the player number(4-7, Exit:0): ");
		if(!num_scanf(&num)){
			printf("Not integer!\n");
		}else if(!num){
			return 0;
		}else if(num<4||num>7){
			printf("number should be in 4 to 7\n");
		}else break;
		sleep(1);
	}
	if(!set_game(num)){printf("Error!\n");return 0;}
	while(1){
		system("clear");
		print_all_status();
		printf("Now: Player%d\n",PlayerNow+1);
		sleep(1);
		if(have_card(player[PlayerNow].equip,Dynamite)){
			printf("Dynamite determine:");
			sPile temp; // determine card
			temp.num=0;
			if(!get_last_card(&temp, &stock)){ // check
				// stock 沒牌
				shuffling();
				get_last_card(&temp, &stock);		
			}
			printf("(%s,%s) %s\n",
					suit_nametxt[temp.card[0].suit],
					rank_nametxt[temp.card[0].rank],
					type_nametxt[temp.card[0].type]);
			if(temp.card[0].suit==Spade && (temp.card[0].rank>=2 && temp.card[0].rank<=9)){
				// explode <- spade 2~9
				printf("The dynamite explodes.\n");
				player[PlayerNow].blood -= 3; // -3 blood
				get_last_card(&discard, &temp); // discard determine card
				print_all_status(); // print_player_state after (-3 blood) & (discard dynamite)			
				if(player[PlayerNow].blood <= 0){ // dying
					while(PlayerNow==PlayerHuman && have_card(player[PlayerNow].hand, Beer)){ // playerHuman -> use beer?
						printf("Do you want to use Beer and +1 blood? (y/n)");
						char opt[100]={0};
						scanf("%[^\n]",opt);
						if(opt[0]=='Y' || opt[0]=='y'){							
							player[PlayerNow].blood += 1; // +1 blood
							// discard beer
							int32_t card_index = -1;
							find_card_index(player[PlayerNow].hand, Beer, &card_index);
							get_card(discard, player[PlayerNow].hand, card_index);
						}
						else if(opt[0]=='N' || opt[0]=='n'){
							break;
						}
						else{
							printf("Invalid input!\n");
							continue;
						}
					}
					if(player[PlayerNow].blood <= 0){ // dead
						printf("player%d is dead.\n", PlayerNow+1);
						player_dead(PlayerNow);
						continue;
					}
				}
			}
			else{ // not explode
				printf("Dinamite pass to Player%d\n", ((PlayerNow+1)%PlayerNum)+1);
				int32_t card_index = -1;
				find_card_index(player[PlayerNow].equip, Dynamite, &card_index);
				get_card(player[(PlayerNow+1)%PlayerNum].equip, player[PlayerNow].equip, card_index);		
			}						
		}
		if(have_card(player[PlayerNow].equip,Jail)){
		}
		if(player[PlayerNow].role==Black_Jack){
		}else if(player[PlayerNow].role==Jesse_Jones){
		}else if(player[PlayerNow].role==Kit_Carlson){
		}else if(player[PlayerNow].role==Pedro_Ramirez){
		}else{
			//for(int i=0;i<2;i++)printf
		}
		next_round();
	}
	print_who_win();
	return 0;
}
