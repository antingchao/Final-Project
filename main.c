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
			if(det_dynamite()==2){ // PlayerNow dead
				continue;
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
