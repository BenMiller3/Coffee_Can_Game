/* 3EA3 Sheet 2 - "Implement any of the games from yesterday's lecture."
 *
 * 1 Player Game - The Coffee Can Problem
 * =======================================
 *
 *
 * The game begins with a coffee can that has some black, and some white beans in it.
 *
 * Gameplay progresses as follows:
 *	1) Randomly select two beans from the can.
 *	2) If they are the same colour, throw them out, but put another black bean in the can.
 *	3) If they are different colours, place the white one back into the can and throw the black one away.
 *
 *
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// globally define the initial Coffee Can with arbitrary white and black beans (25). 
int white_beans = 25;
int black_beans = 25;
int current_bean1;
int current_bean2;

// Function Declarations.
int introduction();
void remove_bean(int bean);
int select_bean();
void add_bean(int bean);
void progress();
void current_state();

int main(){
	srand(time(NULL)); // initialize the random number generator
	// Print the instructions of the game to the screen.
	introduction();
	
	int game;
	printf("\nType 0 to view the simulation step by step, or type 1 to view a black box (only final result outputted): ");
	scanf("%d",&game);

	int can = white_beans + black_beans;
	while(can > 1 && can < 98){

		progress(); // Perform 1 move (turn)
		
		// Show each state throughout simulation if the user chooses to view them.
		if(game == 0){
			printf("\nPress ENTER to move to the next state.");
			while(getchar() != '\n'); // Wait for user confirmation of this.
			current_state(); // Output the state of the can and the beans.
		}

		can = white_beans + black_beans; // Update the can counter.
	}

	
	printf("\nThe simulation has now ended! The number of beans in the can is less than 2.");
	printf("\nRemaining white beans: %d", white_beans);
	printf("\nRemaining black beans: %d", black_beans);

	// Answering Questions from the lecture slides about the Coffee Can Game
	printf("\n\n** Post Game Analysis**");
	// Q1) Game-state: What data characterizes a particular position in the game?
	printf("\n\nThe game state is characterized by the number of beans in the can and the total number of turns taken by the player.");
	// Q2) Progress: How does the game-state change? In particular, what value is decreased each turn? -- white or black beans
	printf("\nThe game state changes whenever a player draws beans from the coffee can, or adds/removes beans from the total bean count.");
	// Q3) Termination: Does the game ever actually finish? If so, how many beans are left in the can when the game finishes.
	printf("\nThis game terminates when the number of beans is less than 2, meaning the player cannot draw 2 random beans \
from the can, thus ending the game.");
	printf("\nThe number of beans left in the can at the end of the game will always be 1. This is because at most net 1 \
bean is removed from the can in any given turn, thus decrementing the total beans by 1. The game ends when  \
total_beans < 2, and this will always result to 1.\n");
	printf("\n*** Simulation End ***\n\n");
	

	return 0;
}

int introduction(){
	printf("\n*** The Coffee Can Problem ***\n");
	printf("\nIn this game/problem, we can verify preconditions and postconditions of the following simulation:");
	printf("\nUpon beginning the game a Coffee Can will be filled with an arbitrary number of white and black coffee beans.\n\n");
	printf("We will select beans from the can with the following rules:\n\n");
	printf("\t1) Randomly select two beans from the can.\n");
	printf("\t2) If they are the same colour, throw them out, but put a new black bean in. (\"infinite\" black beans available)\n");
	printf("\t3) If the beans selected are of different colours, place the white one back in the can and throw the black bean away.\n\n");
	printf("At each step, you will be informed of the current state of the coffee can, the beans selected, and what transaction took place.\n\n");
	printf("Press ENTER to begin the game.");
	
	// Wait for the user to press the ENTER key.
	while(getchar() != '\n');

	return 0;
}

void remove_bean(int bean){
	// Remove a single bean from the coffee can.
	if(bean == 0){black_beans--;}
	else{white_beans--;}
}

int select_bean(){
	// Randomly select one bean from the coffee can
	int total_beans = white_beans + black_beans;
	int selection = (rand()%total_beans);

	// 0 - white = white selected, white - total_beans = black bean selected from the can.
	// Return 0 if a black bean is selected, and a 1 if a white is selected from the can.
	return selection >= white_beans ? 0 : 1; 
}

void add_bean(int bean){
	// BLACK = 0, WHITE = 1.
	if(bean == 0){black_beans++;}
	else{white_beans++;}
}

void progress(){
	// Simulate a full gameplay state (turn)
	// First select two beans.
	int bean1 = select_bean();
	remove_bean(bean1); // must remove 1st bean from can before selecting the 2nd.
	int bean2 = select_bean();
	remove_bean(bean2);

	// If the beans are similar, throw them out and put a new black bean in the can.
	// If they are different colours, place the white one back into the can and throw the black one away.
	if(bean1 == bean2){add_bean(0);} // Adding a new black bean.
	else if(bean1 != bean2){add_bean(1);} // Return the white bean back into the can and keep the black one out.

	current_bean1 = bean1;
	current_bean2 = bean2;
}

void current_state(){
	printf("\n");

	int action;
	char *b1 = (current_bean1 == 0) ? "Black" : "White";
	char *b2 = (current_bean2 == 0) ? "Black" : "White";

	printf("\nTwo beans were selected:\n\tBean1: %s\n\tBean2: %s\n",b1,b2);
	
	if(current_bean1 == current_bean2){
		printf("\nThe beans are of similar colour, they are thrown out, and a black bean is added into the can.");
		action = 0;
	}
	else{
		printf("\nThe beans are different colours, the black bean is thrown out, and the white bean is placed back into the can.");
		action = 1;
	}
	
	if(action == 0){printf("\nOn this turn, the total black beans in the can has remained the same.");
			printf("\nOn this turn, the total white beans have decreased from %d, to %d.", white_beans+1, white_beans);}
	else{printf("\nOn this turn, the total black beans in the can have decreased from %d, to %d", black_beans+1, black_beans);
		printf("\nOn this turn, the total white beans in the can has remained the same.");}

	printf("Total beans left in the coffee can: %d\n", (white_beans+black_beans));
	printf("Total white beans in the coffee can: %d\n", white_beans);
	printf("Total black beans in the coffee can: %d\n", black_beans);
}
