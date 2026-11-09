#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #define clear_screen() system("cls")
    #define delay_ms(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define clear_screen() system("clear")
    #define delay_ms(ms) usleep((useconds_t)(ms) * 1000)
    #define Sleep(ms) usleep((useconds_t)(ms) * 1000)
#endif


// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
#define GRAY    "\033[1;90m"
#define ORANGE  "\033[38;5;208m"
#define PINK    "\033[38;5;213m"
#define LIME    "\033[38;5;118m"
#define TEAL    "\033[38;5;37m"
#define GOLD    "\033[38;5;220m"
#define SKY     "\033[38;5;117m"
#define PURPLE  "\033[38;5;99m"
#define BROWN   "\033[38;5;130m"
#define SKY_BOLD "\033[1;38;5;117m"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int print_start_menu();
int print_toss_choice();
int toosresult(int, int);
void how_to_play();
void _1v1innings(char *plyr1, char *plyr2, int);
void _11vs11innings(char *plyr1, char *plyr2, int);
void show_top3_players();
void show_top3_11vs11();
#ifndef _WIN32
void strupr(char *name);
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	srand(time(0));
#ifdef _WIN32
	SetConsoleOutputCP(65001);
#endif
	
	int choice, result, coin, overs;
	char ply1[25], ply2[25], name[25];
	while(1){
		
		choice = print_start_menu();						// print start menu of game and take user choice
	
		switch(choice) {
			case 1:
				clear_screen();
				printf(GREEN"Enter Your Name: "RESET);
				scanf(" %24[^\n]", name);
				strupr(name);
				printf(BLUE"%s vs. COMPUTER\n"RESET, name);
				do{
					printf(GREEN"Enter No. Of Overs: " RESET);
					if(scanf("%d", &overs) != 1) {
						while(getchar() != '\n');
						overs = 0;
					}
				}while(overs<1 || overs>50);
				
				choice = print_toss_choice();				// print toss menu and take user choice (head/tail)
				coin = rand()%2+1;							// coin side (1=head and 2=tail)       rand()%2+1 gives 1 or 2 only
				result = toosresult(coin, choice);			// return the toss result (1, 2, 3, or 4)
				
				switch(result){
					case 1: strcpy(ply1, name); strcpy(ply2, "COMPUTER"); break; 
					case 2: strcpy(ply2, name); strcpy(ply1, "COMPUTER"); break; // 
					case 3: strcpy(ply2, name); strcpy(ply1, "COMPUTER"); break;
					case 4: strcpy(ply1, name); strcpy(ply2, "COMPUTER"); break;
				}
				
				_1v1innings(ply1, ply2, overs);			// ply1=first batting | ply2=first bowling

				break;
			case 2: 
				clear_screen();
				printf(GREEN"Enter Your Team Name: " RESET);
				scanf(" %24[^\n]", name);
				strupr(name);
				printf(BLUE"%s vs. COMPUTER\n"RESET,name);
				do{
					printf(GREEN"Enter No. Of Overs: %s(5-50): " ,RESET);
					if(scanf("%d", &overs) != 1) {
						while(getchar() != '\n');
						overs = 0;
					}
				}while(overs<5 || overs>50);
				
				choice = print_toss_choice();				// print toss menu and take user choice (head/tail)
				coin = rand()%2+1;							// coin side (1=head and 2=tail)       rand()%2+1 gives 1 or 2 only
				result = toosresult(coin, choice);			// return the toss result (1, 2, 3, or 4)
				
				switch(result){
					case 1: strcpy(ply1, name); strcpy(ply2, "COMPUTER"); break; 
					case 2: strcpy(ply2, name); strcpy(ply1, "COMPUTER"); break; // 
					case 3: strcpy(ply2, name); strcpy(ply1, "COMPUTER"); break;
					case 4: strcpy(ply1, name); strcpy(ply2, "COMPUTER"); break;
				}
				
				_11vs11innings(ply1, ply2, overs);
				
				break;
			case 3:
                clear_screen();
                printf(GREEN"VIEW HIGH SCORES\n\n"RESET);
                printf(BLUE"1. "LIME"Top 3 (1 vs 1)\n");
                printf(BLUE"2. "LIME"Top 3 (11 vs 11)\n"RESET);
                printf("-> ");
                if(scanf("%d", &choice) != 1) {
                    while(getchar() != '\n');
                    choice = 0;
                }

                switch(choice){
                    case 1: show_top3_players(); break;
                    case 2: show_top3_11vs11(); break;
                    default: printf(RED"Invalid choice!\n"RESET); delay_ms(1500);
                }
                
				break;
			case 4: how_to_play();
				break;
			case 5: printf(RED"Exiting game..." RESET); delay_ms(1500); return 0;
				break;
			default:
				printf(RED"Please choose number from MENU............\n"RESET);
				delay_ms(1500);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
int print_start_menu() {
	int choice = 0;
	clear_screen();
    printf("%s", ORANGE);
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║              %sHAND CRICKET GAME%s               ║\n",SKY_BOLD, ORANGE);
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║                                              ║\n");
    printf("║   %s1. %sQUICK GAME%s                              ║\n", BLUE,LIME,ORANGE);
    printf("║   %s2. %sSQUID GAME%s                              ║\n", BLUE,LIME,ORANGE);
    printf("║   %s3. %sVIEW HIGH SCORES%s                        ║\n", BLUE,LIME,ORANGE);
    printf("║   %s4. %sHOW TO PLAY%s                             ║\n", BLUE,LIME,ORANGE);
    printf("║   %s5. %sEXIT%s                                    ║\n", BLUE,LIME,ORANGE);
    printf("║                                              ║\n");
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║               %sEnter Your Choice%s              ║\n",PURPLE,ORANGE);
    printf("╚══════════════════════════════════════════════╝\n\n%s", RESET);
    printf("-> ");
	if(scanf("%d", &choice) != 1) {
		while(getchar() != '\n');
		choice = 0;
	}
	return choice;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
int print_toss_choice() {
	int choice = 0;
	clear_screen();
	printf("%s", YELLOW);
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║                   %sTOSS MENU%s                  ║\n", GREEN, YELLOW);
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║                                              ║\n");
    printf("║%s            ----              ----            %s║\n",GREEN, YELLOW);
    printf("║%s          /    * \\          / *    \\        %s  ║\n",GREEN, YELLOW);
    printf("║%s         |  %sHEAD%s  |        |  %sTAIL%s  | %s        ║\n",GREEN,RED,GREEN,RED, GREEN,YELLOW);
    printf("║%s          \\*     /          \\    * /        %s  ║\n",GREEN, YELLOW);
    printf("║%s            ----              ----            %s║\n",GREEN, YELLOW);
    printf("║                                              ║\n");
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║             %s[1]              [2]%s             ║\n", RED, YELLOW);
    printf("╚══════════════════════════════════════════════╝\n\n%s", RESET);
    
	do{
		printf("-> ");
		if(scanf("%d", &choice) != 1) {
			while(getchar() != '\n');
			choice = 0;
		}
	}while(choice<1 || choice>2);
	return choice;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
int toosresult(int x, int y){
	int i, j, choice, flag;
	for(i=0;i<10+x;i++){
		clear_screen();
		
		(y==1) ?
		(printf("Your choice is %sHEAD%s\n", GREEN, RESET)):
		(printf("Your choice is %sTAIL%s\n", GREEN, RESET));
		printf("\n%sTossing coin...%s\n", YELLOW, RESET);
		
		for(j=0;j<i;j++) printf("\n");
		
		switch(i%2){
			case 0:
				printf("%s", GREEN);
				printf("\t     ----     \n");
				printf("\t   /    * \\   \n");
				printf("\t  |  %sHEAD%s  |  \n", RED, GREEN);
				printf("\t   \\*     /   \n");
				printf("\t     ----     \n");
				printf("%s", RESET);
				break;
			case 1:
				printf("%s", RED);
				printf("\t     ----     \n");
				printf("\t   / *    \\   \n");
				printf("\t  |  %sTAIL%s  |  \n", GREEN, RED);
				printf("\t   \\    * /   \n");
				printf("\t     ----     \n");
				printf("%s", RESET);
				break;
		}
		delay_ms(150);
	}

	if(x == y) {
		printf(GREEN"\nYou won the toss!\n" RESET);

		do{
			printf("1. Batting\n");
			printf("2. Bowling\n\n-> ");
			if(scanf("%d", &choice) != 1) {
				while(getchar() != '\n');
				choice = 0;
			}
		}while(choice !=1 && choice !=2);
		
		flag = choice;
	} else {
		printf(RED"\nComputer won the toss!\n"RESET);
		printf(YELLOW"Computer choosing...\n\n"RESET);
		delay_ms(1500);
		if (rand() % 2) {
		    printf("Computer choose Batting\n");
		    flag = 3;
		} else {
		    printf("Computer choose Bowling\n");
		    flag = 4;
		}	
	}
	printf("%sPress Enter to continue...%s", BLUE, RESET);
    getchar();
    getchar();
    return flag;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void _1v1innings(char *ply1, char *ply2,int overs){
	int runs, i,j, shot, bowl, ply1_runs, ply2_runs;
	char temp[25];
	char balls[12];
	for(j=1;j<=2;j++){	runs = 0;
		
		if(!strcmp(ply1, "COMPUTER")) // IF BATTING IS COMPUTER
			for(i=0;i<6*overs;i++){
				if(i%6==0) strcpy(balls, "-----------");
				clear_screen();
				printf(RED);
                printf("╔════════════════════════════════════════════╦═════════════════════════════════════════╗\n");
                printf("║"BLUE" %-20s "GREEN"RUNS:%-4d OVERS:%2d.%-2d "RED"║ "BLUE"%-20s"GREEN" BALLS:%-12s "RED"║\n", ply1, runs, i/6, i%6, ply2, balls);
                printf("╚════════════════════════════════════════════╩═════════════════════════════════════════╝\n" RESET);
				if(j==2)printf(LIME"Target: %d____Need: %d Runs.\n\n"RESET, ply1_runs + 1, ply1_runs - runs + 1);
				
				do{
					printf("Enter your bowl (1-6): ");
					if(scanf("%d", &bowl) != 1) {
						while(getchar() != '\n');
						bowl = 0;
					}
				}while(bowl < 1 || bowl > 6);
				shot = rand()%6+1;
				printf("COMPUTER Played: %d\n", shot);
			
				delay_ms(1200);
				if(bowl==shot){
					balls[(i%6)*2] = 'w';
					printf("%sCOMPUTER OUT!%s\n", GREEN, RESET);
					delay_ms(1500);
					i++;
					break;
				}else{
					balls[(i%6)*2] = 48 + shot;
					runs += shot;
					if(j==2 && ply1_runs < runs){printf(GREEN"SCORE UP %s WIN THE MATCH\n\n"RESET,ply1);i++;break;} // here ply1 is bestman and the bestman is ply2. so ply1 is ply2 here
					
				}	
			}
			
		
		else  // IF BATTING IS PLAYER
			for(i=0;i<6*overs;i++){
				if(i%6==0) strcpy(balls, "-----------");
				clear_screen();
				printf(RED);
                printf("╔════════════════════════════════════════════╦═════════════════════════════════════════╗\n");
                printf("║"BLUE" %-20s "GREEN"RUNS:%-4d OVERS:%2d.%-2d "RED"║ "BLUE"%-20s"GREEN" BALLS:%-12s "RED"║\n", ply1, runs, i/6, i%6, ply2, balls);
                printf("╚════════════════════════════════════════════╩═════════════════════════════════════════╝\n" RESET);
				if(j==2)printf(LIME"Target: %d____Need: %d Runs.\n\n"RESET, ply1_runs + 1, ply1_runs - runs + 1);
				
				do{
					printf("Enter your shot (1-6): ");
					if(scanf("%d", &shot) != 1) {
						while(getchar() != '\n');
						shot = 0;
					}
				}while(shot < 1 || shot > 6);
				bowl = rand()%6+1;
				printf("COMPUTER bowled: %d\n", bowl);
			
				delay_ms(1200);
				if(bowl==shot){
					balls[(i%6)*2] = 'w';
					printf("%sYOU ARE OUT!%s\n", RED, RESET);
					delay_ms(1500);
					i++;
					break;
				}else{
					balls[(i%6)*2] = 48 + shot;
					runs += shot;
					if(j==2 && ply1_runs < runs){printf(GREEN"SCORE UP %s WIN THE MATCH\n\n"RESET,ply1);i++;break;} // here ply1 is bestman and the bestman is ply2. so ply1 is ply2 here
						
					
				}	
			}
			
			printf(RED);
            printf("╔════════════════════════════════════════════╦═════════════════════════════════════════╗\n");
			printf("║"BLUE" %-20s "GREEN"RUNS:%-4d OVERS:%2d.%-2d "RED"║ "BLUE"%-20s"GREEN" BALLS:%-12s "RED"║\n", ply1, runs, i/6, i%6, ply2, balls);
			printf("╚════════════════════════════════════════════╩═════════════════════════════════════════╝\n" RESET);
			
			if(j==1){
				ply1_runs = runs;
				printf(LIME"%s target: %d in %d.%d\n\n"RESET, ply1, runs + 1, i/6, i%6);
			}else{
				ply2_runs = runs;
			}
			
			strcpy(temp, ply1);
			strcpy(ply1, ply2);
			strcpy(ply2, temp);
		    
		    printf("%sPress Enter to continue...%s", BLUE, RESET);
		    getchar();
		    getchar();
	}
	char winner[25];
	if
		(ply1_runs == ply2_runs) printf(RED"Game Draw................................................\n"RESET);
	else{
			if(ply1_runs > ply2_runs){
				strcpy(winner, ply1);
				runs = ply1_runs-ply2_runs;
			}else{
				strcpy(winner, ply2);
				runs = ply2_runs-ply1_runs;
			}
		printf(ORANGE);
		printf("╔═══════════════════════════════════════╦═══════════╗\n");
		printf("║"RESET" PLAYER 01: "GREEN" %-25s "ORANGE"║"GREEN" RUNS: %-3d "ORANGE"║\n", ply1,  ply1_runs);
		printf("╠═══════════════════════════════════════╬═══════════╣\n");
		printf("║"RESET" PLAYER 02: "GREEN" %-25s "ORANGE"║"GREEN" RUNS: %-3d "ORANGE"║\n", ply2,  ply2_runs);
		printf("╠═══════════════════════════════════════╬═══════════╣\n");
		printf("║"RESET" WINNER     "GREEN" %-25s "ORANGE"║"GREEN" RUNS:+%-3d "ORANGE"║\n", winner,  runs);
		printf("╚═══════════════════════════════════════╩═══════════╝\n\n" RESET);
		
		FILE *file = fopen("1v1game.txt", "a");
		if (file != NULL) {
			fprintf(file,"player_01: %s: %d\n", ply1, ply1_runs);
			fprintf(file,"player_02: %s: %d\n", ply2, ply2_runs);
			fprintf(file,"winner: %s: +%d\n\n", winner, runs);
			fclose(file);
		}
		
	}
	printf("%sPress Enter to continue...%s", BLUE, RESET);
    getchar();
    getchar();
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void _11vs11innings(char *ply1, char *ply2, int overs) {
    int runs, i, j, shot, bowl, bst_ind = 0, blr_ind = 0;
    int plyt1_runs[11] = {0};
    int plyt2_runs[11] = {0};
    int team1_wickets = 0, team2_wickets = 0;
    char balls[12];
    char temp[25];
    
	char team1[11][25];
	char team2[11][25];
	
 if(!strcmp(ply1, "COMPUTER")) {
        strcpy(team1[0], "PROCESSOR");
        strcpy(team1[1], "CPU");
        strcpy(team1[2], "KEYBOARD");
        strcpy(team1[3], "BATTERY");
        strcpy(team1[4], "SSD");
        strcpy(team1[5], "STORAGE");
        strcpy(team1[6], "RAM");
        strcpy(team1[7], "TOUCHPAD");
        strcpy(team1[8], "WEBCAM");
        strcpy(team1[9], "SPEAKERS");
        strcpy(team1[10], "GRAPHICS CARD");
        printf(RED"Enter ALL Team Member Names:\n"RESET);
        for(i = 0; i < 11; i++) {
            printf(LIME"[%d]-> "RESET, i+1);
            scanf(" %24[^\n]", team2[i]);
        }
    } else {
    	
        printf(RED"Enter ALL Team Member Names:\n"RESET);
        for(i = 0; i < 11; i++) {
            printf(LIME"[%d]-> "RESET, i+1);
			scanf(" %24[^\n]", team1[i]);
        }
        strcpy(team2[0], "PROCESSOR");
        strcpy(team2[1], "CPU");
        strcpy(team2[2], "KEYBOARD");
        strcpy(team2[3], "BATTERY");
        strcpy(team2[4], "SSD");
        strcpy(team2[5], "STORAGE");
        strcpy(team2[6], "RAM");
        strcpy(team2[7], "TOUCHPAD");
        strcpy(team2[8], "WEBCAM");
        strcpy(team2[9], "SPEAKERS");
        strcpy(team2[10], "GRAPHICS CARD");
    }
    
    int team1_runs = 0, team2_runs = 0;
    
    for(j = 1; j <= 2; j++) {
        runs = 0;
        bst_ind = 0; 
        blr_ind = 0; 
        int wickets = 0;
        
        if(!strcmp(ply1, "COMPUTER")) { // COMPUTER batting
            for(i = 0; i < 6 * overs && wickets < 10; i++) {
                if(i % 6 == 0) {
                    strcpy(balls, "-----------");
                    if(i > 0) blr_ind = (blr_ind + 1) % 11;  
                }
                
                clear_screen();
                printf(LIME"  %-44s vs %s\n"RED, ply1, ply2);
                printf("╔═══════════════════════════════════════════════╦═════════════════════════════════════════╗\n");
                printf("║"BLUE" %-20s "GREEN"RUNS:%4d/%-2d OVERS:%2d.%-2d "RED"║ "BLUE"%-20s"GREEN" BALLS:%-12s "RED"║\n", team1[bst_ind], runs,wickets, i/6, i%6, team2[blr_ind], balls);
                printf("╚═══════════════════════════════════════════════╩═════════════════════════════════════════╝\n" RESET);
                if(j == 2) printf(LIME"Target: %d | Need: %d Runs | Wickets Left: %d\n\n"RESET, team1_runs + 1, team1_runs - runs + 1, 10 - wickets);
                
                
                // Get user bowl
                do {
                    printf("Enter your bowl (1-6): ");
                    if(scanf("%d", &bowl) != 1) {
                        while(getchar() != '\n');
                        bowl = 0;
                    }
                } while(bowl < 1 || bowl > 6);
                
                // Computer shot
                 shot = rand() % 6 + 1;
                printf("COMPUTER Played: %d\n", shot);
                delay_ms(1200);
                
                if(bowl == shot) {
                    balls[(i % 6) * 2] = 'w';
                    printf("%sOUT! %s is out!%s\n", RED, team1[bst_ind], RESET);
                    wickets++;
                    bst_ind++;  // Next batsman
                    delay_ms(1500);
                    if(bst_ind >= 11) { i++; break; }  // All out
                } else {
                    balls[(i % 6) * 2] = 48 + shot;
                    plyt1_runs[bst_ind] += shot;
                    runs += shot;
                    
                    if(j == 2 && runs > team1_runs) {
                        printf(GREEN"\n%s WIN THE MATCH by %d wickets!%s\n", ply1, 10 - wickets, RESET);
                        i++;
                        break;
                    }
                }
                
                // Check if all wickets gone
                if(wickets >= 10) {
                    printf(RED"\nALL OUT!%s\n", RESET);
                    i++;
                    break;
                }
            }
        } else { // PLAYER batting
            for(i = 0; i < 6 * overs && wickets < 10; i++) {
                if(i % 6 == 0) {
                    strcpy(balls, "-----------");
                    if(i > 0) blr_ind = (blr_ind + 1) % 11;  // Change bowler every over
                }
                
                clear_screen();
                printf(LIME"  %-44s vs %s\n"RED, ply1, ply2);
                printf("╔═══════════════════════════════════════════════╦═════════════════════════════════════════╗\n");
                printf("║"BLUE" %-20s "GREEN"RUNS:%4d/%-2d OVERS:%2d.%-2d "RED"║ "BLUE"%-20s"GREEN" BALLS:%-12s "RED"║\n", team1[bst_ind], runs,wickets, i/6, i%6, team2[blr_ind], balls);
                printf("╚═══════════════════════════════════════════════╩═════════════════════════════════════════╝\n" RESET);
                if(j == 2) printf(LIME"Target: %d | Need: %d Runs | Wickets Left: %d\n\n"RESET, team1_runs + 1, team1_runs - runs + 1, 10 - wickets);
                
                // Get user shot
                do {
                    printf("Enter your shot (1-6): ");
                    if(scanf("%d", &shot) != 1) {
                        while(getchar() != '\n');
                        shot = 0;
                    }
                } while(shot < 1 || shot > 6);
                
                // Computer bowl
                 bowl = rand() % 6 + 1;
                printf("COMPUTER bowled: %d\n", bowl);
                delay_ms(1200);
                
                if(bowl == shot) {
                    balls[(i % 6) * 2] = 'w';
                    printf("%sOUT! %s is out!%s\n", RED, team1[bst_ind], RESET);
                    wickets++;
                    bst_ind++;  // Next batsman
                    delay_ms(1500);
                    if(bst_ind >= 11) { i++; break; }  // All out
                } else {
                    balls[(i % 6) * 2] = 48 + shot;
                    plyt1_runs[bst_ind] += shot;
                    runs += shot;
                    
                    if(j == 2 && runs > team1_runs) {
                        printf(GREEN"\n%s WIN THE MATCH by %d wickets!%s\n", ply1, 10 - wickets, RESET);
                        i++;
                        break;
                    }
                }
                
                // Check if all wickets gone
                if(wickets >= 10) {
                    printf(RED"\nALL OUT!%s\n", RESET);
                    i++;
                    break;
                }
            }
        }
        
        // Display innings summary
        printf(RED);
        printf("╔═══════════════════════════════════════════════╦═════════════════════════════════════════╗\n");
        printf("║"BLUE" %-20s "GREEN"RUNS:%4d/%-2d OVERS:%2d.%-2d "RED"║ "BLUE"%-20s"GREEN" BALLS:%-12s "RED"║\n", ply1, runs,wickets, i/6, i%6, ply2, balls);
        printf("╚═══════════════════════════════════════════════╩═════════════════════════════════════════╝\n" RESET);
        
        if(j == 1) {
            team1_runs = runs;
            team1_wickets = wickets;
            printf(LIME"\n%s set target: %d/%d in %d.%d overs\n\n"RESET, ply1, runs, wickets, i/6, i%6);
        } else {
            team2_runs = runs;
            team2_wickets = wickets;
        }
        
        strcpy(temp, ply1);
        strcpy(ply1, ply2);
        strcpy(ply2, temp);
    
        char temp_team[11][25];
        int temp_runs[11];
        
        for(int k = 0; k < 11; k++) {
            strcpy(temp_team[k], team1[k]);
            strcpy(team1[k], team2[k]);
            strcpy(team2[k], temp_team[k]);
            
            temp_runs[k] = plyt1_runs[k];
            plyt1_runs[k] = plyt2_runs[k];
            plyt2_runs[k] = temp_runs[k];
        }
        
        printf("%sPress Enter to continue...%s", BLUE, RESET);
        getchar();
        getchar();
    }
    
    printf(ORANGE);
    printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  %sMATCH RESULT%s                                  ║\n", BLUE, ORANGE);
    printf("╠════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                ║\n");
    printf("║  %sTeam 1 Score: %3d/%-3d%s                                                         ║\n", GREEN,  team1_runs, team1_wickets, ORANGE);
    printf("║                                                                                ║\n");
    printf("║  %s%-25s%s                                                     ║\n", CYAN,ply1, ORANGE);
    for(i = 0; i < 11; i++)
    printf("║    %-25s %3d runs                                          ║\n", team1[i], plyt1_runs[i]);
    printf("║                                                                                ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                ║\n");
    printf("║  %sTeam 2 Score: %3d/%-3d%s                                                         ║\n", GREEN, team2_runs, team2_wickets, ORANGE);
    printf("║                                                                                ║\n");
    printf("║  %s%-25s%s                                                     ║\n", CYAN,ply2, ORANGE);
    for(i = 0; i < 11; i++) 
    printf("║    %-25s %3d runs                                          ║\n", team2[i], plyt2_runs[i]);
    printf("║                                                                                ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════════╣\n");
    if(team1_runs == team2_runs) 
    printf("║                                   %sMATCH TIED!%s                                  ║\n", YELLOW, ORANGE);
    else if(team1_runs > team2_runs)
    printf("║                  %sWINNER: %25s by %-4d runs%s                ║\n", GREEN, ply1, team1_runs - team2_runs, ORANGE);
    else
    printf("║                  %sWINNER: %25s by %-4d wickets%s             ║\n", GREEN, ply2, 10 - team2_wickets, ORANGE);
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n"RESET);
    
    // Save to file
    FILE *file = fopen("11v11game.txt", "a");
    if(file) {
        fprintf(file, "Match: %s vs %s\n", ply1, ply2);
        fprintf(file, "%s: %d/%d\n", ply1, team1_runs, team1_wickets);
        fprintf(file, "%s: %d/%d\n", ply2, team2_runs, team2_wickets);
        
        if(team1_runs > team2_runs) {fprintf(file, "Winner: %s: by %d runs\n\n", ply1, team1_runs - team2_runs);
        } else if(team2_runs > team1_runs) {fprintf(file, "Winner: %s: by %d wickets\n\n", ply2, 10 - team2_wickets);
        } else {fprintf(file, "Winner: NONE by 0 runs\n\n");
        }
        fclose(file);
    }
    
    printf("\n%sPress Enter to continue...%s", BLUE, RESET);
    getchar();
    getchar();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void show_top3_11vs11(){
    FILE *fp = fopen("11v11game.txt", "r");
    if (fp == NULL) {
        printf(RED "No 11v11 records found!\n" RESET);
        delay_ms(1500);
        return;
    }

    char names_runs[100][25];
    int ply_runs[100];
    int ply_ind_runs = 0;
    
    char names_wicket[100][25];
    int ply_wicket[100];
    int ply_ind_wicket = 0;
    
    char temp[100];
    char win_by[20];
    int runs;

    while (fscanf(fp, " %[^\n]\n", temp) == 1) {
        if (fscanf(fp, " %[^\n]\n", temp) != 1) break;
        if (fscanf(fp, " %[^\n]\n", temp) != 1) break;
        if (fscanf(fp, "Winner: %[^:]: by %d %19s\n", temp, &runs, win_by) == 3) {
            if (strcmp(temp, "COMPUTER") != 0 && strcmp(temp, "NONE") != 0) {
                if (strcmp(win_by, "runs") == 0) {
                    if (ply_ind_runs < 100) {
                        strcpy(names_runs[ply_ind_runs], temp);
                        ply_runs[ply_ind_runs] = runs;
                        ply_ind_runs++;
                    }
                } else {
                    if (ply_ind_wicket < 100) {
                        strcpy(names_wicket[ply_ind_wicket], temp);
                        ply_wicket[ply_ind_wicket] = runs;
                        ply_ind_wicket++;
                    }
                }
            }
        }
    }
    fclose(fp);

    for (int i = 0; i < ply_ind_runs - 1; i++) {
        for (int j = i + 1; j < ply_ind_runs; j++) {
            if (ply_runs[j] > ply_runs[i]) {
                int t = ply_runs[i];
                ply_runs[i] = ply_runs[j];
                ply_runs[j] = t;

                char tempName[25];
                strcpy(tempName, names_runs[i]);
                strcpy(names_runs[i], names_runs[j]);
                strcpy(names_runs[j], tempName);
            }
        }
    }
    
    for (int i = 0; i < ply_ind_wicket - 1; i++) {
        for (int j = i + 1; j < ply_ind_wicket; j++) {
            if (ply_wicket[j] > ply_wicket[i]) {
                int t = ply_wicket[i];
                ply_wicket[i] = ply_wicket[j];
                ply_wicket[j] = t;

                char tempName[25];
                strcpy(tempName, names_wicket[i]);
                strcpy(names_wicket[i], names_wicket[j]);
                strcpy(names_wicket[j], tempName);
            }
        }
    }

    clear_screen();
    printf(ORANGE);
    printf("╔════════════════════════════════════════╗\n");
    printf("║           "GREEN"TOP 3 TEAMS BY RUNS"ORANGE"          ║\n");
    printf("╠════════════════════════════════════════╣\n");
    for (int i = 0; i < ply_ind_runs && i < 3; i++) 
    printf("║ %d. %-25s +%-3d runs ║\n", i + 1, names_runs[i], ply_runs[i]);
    printf("╚════════════════════════════════════════╝\n" RESET);
    
    printf(ORANGE);
    printf("╔══════════════════════════════════════════╗\n");
    printf("║           "GREEN"TOP 3 TEAMS BY WICKET"ORANGE"          ║\n");
    printf("╠══════════════════════════════════════════╣\n");
    for (int i = 0; i < ply_ind_wicket && i < 3; i++) 
    printf("║ %d. %-25s +%-3d wicket ║\n", i + 1, names_wicket[i], ply_wicket[i]);   
    printf("╚══════════════════════════════════════════╝\n" RESET);

    printf("\n%sPress Enter to continue...%s", BLUE, RESET);
    getchar();
    getchar();

}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void show_top3_players(){
    FILE *fp = fopen("1v1game.txt", "r");
    if (fp == NULL) {
        printf(RED "No 1v1 records found!\n" RESET);
        delay_ms(1500);
        return;
    }

    char names[100][25];
    char temp[50];
    int ply_runs[100];
    int ply_ind = 0;
    int runs;

    while (ply_ind < 100 && fscanf(fp, " %[^\n]\n", temp) == 1) {
        if (fscanf(fp, " %[^\n]\n", temp) != 1) break;
        if (fscanf(fp, "winner: %[^:]: +%d\n", temp, &runs) == 2) {
            if (strcmp(temp, "COMPUTER") != 0) {
                strcpy(names[ply_ind], temp);
                ply_runs[ply_ind] = runs;
                ply_ind++;
            }
        }
    }
    fclose(fp);

    for (int i = 0; i < ply_ind - 1; i++) {
        for (int j = i + 1; j < ply_ind; j++) {
            if (ply_runs[j] > ply_runs[i]) {
                int t = ply_runs[i];
                ply_runs[i] = ply_runs[j];
                ply_runs[j] = t;

                char tempName[25];
                strcpy(tempName, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], tempName);
            }
        }
    }

    clear_screen();
    printf(ORANGE);
    printf("╔════════════════════════════════════════╗\n");
    printf("║           "GREEN"TOP 3 PLAYERS (1v1)"ORANGE"          ║\n");
    printf("╠════════════════════════════════════════╣\n");
    for (int i = 0; i < ply_ind && i < 3; i++) 
    printf("║ %d. %-25s +%-3d runs ║\n", i + 1, names[i], ply_runs[i]);
    printf("╚════════════════════════════════════════╝\n" RESET);

    printf("\n%sPress Enter to continue...%s", BLUE, RESET);
    getchar();
    getchar();

}
////////////////////////////////////////////////////////////////////////////////////////////////////////

void how_to_play() {
    clear_screen();
    
	printf("%s", ORANGE);
	printf("╔════════════════════════════════════════════════╗\n");
	printf("║            %sHOW TO PLAY HAND CRICKET%s            ║\n", BLUE, ORANGE);
	printf("╚════════════════════════════════════════════════╝\n\n");
	printf("%s", RESET);

    printf("%sRULES OF HAND CRICKET:%s\n\n", CYAN, RESET);

    printf("%s1.%s You and computer choose numbers 1 to 6\n", MAGENTA, RESET);
    printf("%s2.%s If numbers match -> BATSMAN IS OUT!\n", MAGENTA, RESET);
    printf("%s3.%s If numbers don't match -> runs = batsman's number\n", MAGENTA, RESET);
    printf("%s4.%s First toss decides who bats/bowls first\n", MAGENTA, RESET);
    printf("%s5.%s Chase the target score to win!\n\n", MAGENTA, RESET);

    printf("%sEXAMPLE:%s\n", GREEN, RESET);
    printf("- You bat: choose 4\n");
    printf("- Computer bowls: choose 2\n");
    printf("- Result: You score 4 runs!\n\n");

    printf("- You bat: choose 3\n");
    printf("- Computer bowls: choose 3\n");
    printf("- Result: YOU'RE OUT! Wicket lost.\n\n");

    printf("%sPress Enter to return to main menu...%s", BLUE, RESET);
    getchar();
    getchar();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _WIN32
void strupr(char *name) {
    for (int i = 0; name[i]; i++) {
        if (name[i] >= 'a' && name[i] <= 'z') {
            name[i] -= 32;
        }
    }
}
#endif
