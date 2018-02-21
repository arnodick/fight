#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
//TODO turn off debug mode
//TODO use link to link the dll here so it is linked https://stackoverflow.com/questions/20890458/compile-c-in-vs-without-requiring-msvcp120d-dll-at-runtime

using namespace std;
void report();
void options();
void statusincrement();
void turnresult();
void statusreset();
void endgame();

void locbonusset();

int attackroll(int atkbonus, int defbonus);
int damagecalc(int result, int status, int power, int str, int res, int atkbonus, int defbonus, int locbonus);

void resultplayer1attack();
void resultplayer2attack();

void player1valid();
void player2valid();

int d2();
int resultcalc(int tempresult);
int basicskillroll(int numofdice);

void movenameset();
void damagenameset();
void attribnameset();
void namefix();


int resultmatrix[5][5] = { 1, 1, 3, 2, 5,
1, 1, 2, 3, 5,
3, 2, 4, 4, 4,
2, 3, 4, 4, 4,
5, 5, 4, 4, 4 };
//This will become a 5x5 array, or larger, as more possibilities are added.

int player1[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, player2[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// First value is the move.
// Second value is the power of the move. (0 = jab, 1 = power punch, etc.)
// Third value is the concussion status of the player.
//   ie: Stunned, knocked out, etc
// Fourth value is the timer for the concussion status.
//   ie: 1 means that status has been applied to the player for 1 full turn.
// Fifth value is the pain status of the player. 
//   ie: distracted, confused, etc. 
// Sixth value is the timer for the pain status.
// Seventh value is the conditioning status of the player. 
//   ie: -1, -2, to all stats, etc. 
// Eighth value is the timer for the conditioning status.
// Ninth value is the location of the attack.
//   ie: 1 = Head, 2 = Body, 3 = Legs

int statsplayer1[5] = { 2, 2, 2, 2, 2 }, statsplayer2[5] = { 2, 2, 2, 2, 2 };
int permstatsplayer1[5] = { 2, 2, 2, 2, 2 }, permstatsplayer2[5] = { 2, 2, 2, 2, 2 };
// First = STR, second = SPD, third = RES, fourth = WILL, fifth = COND.

int knockdown1 = 0, knockdown2 = 0, timercheck = 0;

int locbonus1[3] = { 0, 0, 0 }, locbonus2[3] = { 0, 0, 0 };
// First = Concussion, Second = Pain, Third = Conditioning

int result = 0, temp = 0, atkbonus = 0, defbonus = 0;

vector<string> movenames(5);
vector<string> damagenames(8);
vector<string> paindamagenames(8);
vector<string> attribnames(5);


int main()
{

	srand((unsigned)time(NULL));
	movenameset();
	damagenameset();
	attribnameset();

	cout << "FIGHT!";

	ifstream player1in("player1.txt");
	ifstream player2in("player2.txt");

	for (int y = 0; y < 5; y++)
	{
		player1in >> permstatsplayer1[y];
		player2in >> permstatsplayer2[y];
		statsplayer1[y] = permstatsplayer1[y];
		statsplayer2[y] = permstatsplayer2[y];
	}

	for (int x = 1; x == 1;)
	{
		//Reset all statuses and counts for a new game.
		knockdown1 = 0; knockdown2 = 0; player2[2] = 0; player2[3] = 0;  player1[2] = 0;  player1[3] = 0; player2[4] = 0; player2[5] = 0;  player1[4] = 0;  player1[5] = 0; player2[6] = 0; player2[7] = 0;  player1[6] = 0;  player1[7] = 0;

		for (; knockdown1 < 3 && knockdown2 < 3 && player1[2] < 7 && player2[2] < 7;)
		{
			report();

			options();

			statusincrement();

			turnresult();

			statusreset();

			cout << "\nPress 1 to continue:  ";
			cin >> x;
			system("cls");

		}

		endgame();

		cout << "\nIf you would like to continue, press 1:  ";
		cin >> x;
		system("cls");
	}
}

void report()
{
	for (int z = 0; z < 5; z++)
	{
		cout << "Player 1's " << attribnames[z] << ": " << statsplayer1[z] << "     ";
		cout << "Player 2's " << attribnames[z] << ": " << statsplayer2[z] << "\n";
	}
}

void options()
{

	if (player1[2] > 0)
	{
		cout << "\nPlayer 1 is " << damagenames[player1[2]] << " and may only:\n\n   3) Parry\n   4) Dodge\n   5) Block\n\n   ";
		cin >> player1[0];
		player1valid();
	}
	else
	{
		cout << "\nPlease choose a move for Player 1:\n\n   1) Punch\n   2) Kick\n   3) Parry\n   4) Dodge\n   5) Block\n\n   ";
		cin >> player1[0];
		player1valid();
		if (player1[0] == 1)
		{
			cout << "\n   Please choose a power for Player 1's " << movenames[player1[0] - 1] << ":\n\n      0) Jab\n      1) Straight\n      2) Uppercut\n      3) Hook\n      4) Haymaker\n\n   ";
			cin >> player1[1];
			cout << "\n     Please choose a location for Player 1's " << movenames[player1[0] - 1] << ":\n\n        1) Head\n        2) Body\n        3) Legs\n\n   ";
			cin >> player1[8];
		}
		if (player1[0] == 2)
		{
			cout << "\n   Please choose a power for Player 1's " << movenames[player1[0] - 1] << ":\n\n      1) Kick\n\n      3) Roundhouse\n\n      5) Spinning Kick\n\n   ";
			cin >> player1[1];
			cout << "\n     Please choose a location for Player 1's " << movenames[player1[0] - 1] << ":\n\n        1) Head\n        2) Body\n        3) Legs\n\n   ";
			cin >> player1[8];
		}
	}

	//TODO: this is where AI code should go
	if (player2[2] > 0)
	{
		cout << "\nPlayer 2 is " << damagenames[player2[2]] << " and may only:\n\n   3) Parry\n   4) Dodge\n   5) Block\n\n   ";
		//cin>> player2[0];//TODO: make this player2[0] = random integer(x) where x is whatever the options are
		player2[0] = rand() % 3 + 3;
		player2valid();
		cout << player2[0] << "\n";
	}
	else
	{
		cout << "\nPlease choose a move for Player 2:\n\n   1) Punch\n   2) Kick\n   3) Parry\n   4) Dodge\n   5) Block\n\n   ";
		//cin >> player2[0];//TODO: here too
		player2[0] = rand() % 5 + 1;
		player2valid();
		cout << player2[0] << "\n";
		if (player2[0] == 1)
		{
			cout << "\n   Please choose a power for Player 2's " << movenames[player2[0] - 1] << ":\n\n      0) Jab\n      1) Straight\n      2) Uppercut\n      3) Hook\n      4) Haymaker\n\n   ";
			//cin >> player2[1];//TODO: here too
			player2[1] = rand() % 5;
			cout << player2[1] << "\n";
			cout << "\n     Please choose a location for Player 2's " << movenames[player2[0] - 1] << ":\n\n        1) Head\n        2) Body\n        3) Legs\n\n   ";
			player2[8] = rand() % 3 + 1;
			cout << player2[8] << "\n";
			//cin >> player2[8];//TODO: here too
		}
		if (player2[0] == 2)
		{
			cout << "\n   Please choose a power for Player 2's " << movenames[player2[0] - 1] << ":\n\n      1) Front Kick\n\n      3) Roundhouse\n\n      5) Spinning Kick\n\n   ";
			player2[1] = rand() % 5 + 1;
			cout << player2[1] << "\n";
			//cin >> player2[1];//TODO: here too
			cout << "\n     Please choose a location for Player 2's " << movenames[player2[0] - 1] << ":\n\n        1) Head\n        2) Body\n        3) Legs\n\n   ";
			player2[8] = rand() % 3 + 1;
			cout << player2[8] << "\n";
			//cin >> player2[8];//TODO: here too
		}
	}
	locbonusset();
}

void locbonusset()
{
	if (player1[8] == 1)
	{
		locbonus1[0] = 0;
		locbonus1[1] = -2;
		locbonus1[2] = -4;
	}
	if (player1[8] == 2)
	{
		locbonus1[0] = -2;
		locbonus1[1] = -4;
		locbonus1[2] = 0;
	}
	if (player1[8] == 3)
	{
		locbonus1[0] = -4;
		locbonus1[1] = 0;
		locbonus1[2] = -2;
	}

	if (player2[8] == 1)
	{
		locbonus2[0] = 0;
		locbonus2[1] = -2;
		locbonus2[2] = -4;
	}
	if (player2[8] == 2)
	{
		locbonus2[0] = -2;
		locbonus2[1] = -4;
		locbonus2[2] = 0;
	}
	if (player2[8] == 3)
	{
		locbonus2[0] = -4;
		locbonus2[1] = 0;
		locbonus2[2] = -2;
	}
}

void statusincrement()
{
	// Now that a turn has passed, and another result hasn't been added in yet, the turn counter for status is incremented.
	// Conussion status and counter
	if (player1[2] > 0)
		player1[3]++;
	if (player2[2] > 0)
		player2[3]++;

	// Pain status and counter
	if (player1[4] > 0)
		player1[5]++;
	if (player2[4] > 0)
		player2[5]++;
}

void turnresult()
// Uses both players' moves and their comparison in the matrix to output a result for the turn's moves.
{
	if (resultmatrix[player2[0] - 1][player1[0] - 1] == 1)
	{
		atkbonus = 3;
		defbonus = 0; // The person being hit has a -3 to defense, because they are attacking.
		// Compares speed of each player's attack, by checking the speed stat minus the power of the attack. The more powerful an attack, the slower.
		if (statsplayer1[2] - player1[1] > statsplayer2[2] - player2[1])
		{
			cout << "Player 1 was faster than player 2!";

			resultplayer1attack();

			if (player2[2] < 1)
			{
				cout << "\nPlayer 2 fought through the pain!\n";
				resultplayer2attack();
			}

		}
		else if (statsplayer1[2] - player1[1] == statsplayer2[2] - player2[1])
		{
			cout << "\nBoth players were the same speed, and cancelled each other out!";
		}
		else
		{
			cout << "Player 2 was faster than player 1!";
			resultplayer2attack();

			if (player1[2] < 1)
			{
				cout << "\nPlayer 1 fought through the pain!\n";
				resultplayer1attack();
			}
		}
	}

	if (resultmatrix[player2[0] - 1][player1[0] - 1] == 2)
		// The attacker made a good choice!
	{
		atkbonus = 3;
		defbonus = 0;
		if (player1[0] == 1 || player1[0] == 2)
			cout << "\nPlayer 1 " << movenames[player1[0] - 1] << "ED through Player 2's " << movenames[player2[0] - 1] << "!\n";
		else
			cout << "\nPlayer 2 " << movenames[player2[0] - 1] << "ED through Player 1's " << movenames[player1[0] - 1] << "!\n";

		if (player1[0] == 1 || player1[0] == 2)
		{
			resultplayer1attack();
		}
		else
		{
			resultplayer2attack();
		}
	}

	if (resultmatrix[player2[0] - 1][player1[0] - 1] == 3)
		// The defender made a good choice!
	{
		atkbonus = 0;
		defbonus = 3;
		if (player1[0] == 3 || player1[0] == 4)
			cout << "\nPlayer 1 " << movenames[player1[0] - 1] << "ED Player 2's " << movenames[player2[0] - 1] << "!\n";
		else
			cout << "\nPlayer 2 " << movenames[player2[0] - 1] << "ED Player 1's " << movenames[player1[0] - 1] << "!\n";

		if (player1[0] == 3 || player1[0] == 4)
		{
			if (defbonus > 0)
				result = -attackroll(atkbonus, defbonus); //Flip the result number, because the defender is the focus of the calculatiosn below, and the defender's result is subtracted from the attackers.
			else
				result = attackroll(atkbonus, defbonus);

			player2[2] = damagecalc(result, player2[2], player2[1], 0, 0, atkbonus, defbonus, 0);
			if (timercheck == 1)
				player2[3] = 0; //Timer reset, because a new status has been inflicted.
			//player2[4] = damagecalc (result, player2[4], player2[1], 0, 0, atkbonus, defbonus, 0);
			//player2[6] = damagecalc (result, player2[6], player2[1], 0, 0, atkbonus, defbonus, 0);

			namefix();

			cout << "\nPlayer 2 is " << damagenames[player2[2]] << ", " << paindamagenames[player2[4]] << " and COND " << player2[6] << "!\n";
		}
		else
		{
			if (defbonus > 0)
				result = -attackroll(atkbonus, defbonus); //Flip the result number, because the defender is the focus of the calculatiosn below, and the defender's result is subtracted from the attackers.
			else
				result = attackroll(atkbonus, defbonus);

			player1[2] = damagecalc(result, player1[2], player1[1], 0, 0, atkbonus, defbonus, 0);
			if (timercheck == 1)
				player1[3] = 0; //Timer reset, because a new status has been inflicted.
			//player1[4] = damagecalc (result, player1[4], player1[1], 0, 0, atkbonus, defbonus, 0);
			//player1[6] = damagecalc (result, player1[6], player1[1], 0, 0, atkbonus, defbonus, 0);

			namefix();

			cout << "\nPlayer 1 is " << damagenames[player1[2]] << ", " << paindamagenames[player1[4]] << " and COND " << player1[6] << "!\n";
		}
	}

	if (resultmatrix[player2[0] - 1][player1[0] - 1] == 4)
		cout << "\nBoth players defended and nothing happened!\n";

	if (resultmatrix[player2[0] - 1][player1[0] - 1] == 5)
		// The defender simply blocked, so a straight comparison of skills is done.
	{
		atkbonus = 0;
		defbonus = 0;
		if (player1[0] == 1 || player1[0] == 2)
			cout << "\nPlayer 1 " << movenames[player1[0] - 1] << "ED Player 2's " << movenames[player2[0] - 1] << "!\n";
		else
			cout << "\nPlayer 2 " << movenames[player2[0] - 1] << "ED Player 1's " << movenames[player1[0] - 1] << "!\n";

		if (player1[0] == 1 || player1[0] == 2)
		{
			resultplayer1attack();
		}
		else
		{
			resultplayer2attack();
		}
	}
}

void resultplayer1attack()
{
	if (defbonus > 0)
		result = -attackroll(atkbonus, defbonus); //Flip the result number, because the defender is the focus of the calculatiosn below, and the defender's result is subtracted from the attackers.
	else
		result = attackroll(atkbonus, defbonus);

	// Concussion damage
	temp = damagecalc(result, player2[2], player1[1], statsplayer1[0], statsplayer2[2], atkbonus, defbonus, locbonus1[0]);
	if (temp > player2[2])
	{
		player2[2] = temp;
		if (timercheck == 1)
			player2[3] = 0; //Timer reset, because a new status has been inflicted.
	}
	// Pain damage
	player2[4] = player2[4] + damagecalc(result, player2[4], player1[1], statsplayer1[0], statsplayer2[3], atkbonus, defbonus, locbonus1[1]);
	if (timercheck == 1)
		player2[5] = 0; //Timer reset, because a new status has been inflicted.
	// Conditioning damage
	player2[6] = player2[6] + damagecalc(result, player2[6], player1[1], statsplayer1[0], statsplayer2[4], atkbonus, defbonus, locbonus1[2]);

	namefix();

	cout << "\nPlayer 2 is " << damagenames[player2[2]] << ", " << paindamagenames[player2[4]] << " and COND " << player2[6] << "!\n";
}

void resultplayer2attack()
{
	if (defbonus > 0)
		result = -attackroll(atkbonus, defbonus); //Flip the result number, because the defender is the focus of the calculatiosn below, and the defender's result is subtracted from the attackers.
	else
		result = attackroll(atkbonus, defbonus);

	// Concussion damage
	temp = damagecalc(result, player1[2], player2[1], statsplayer2[0], statsplayer1[2], atkbonus, defbonus, locbonus2[0]);
	if (temp > player1[2])
	{
		player1[2] = temp;
		if (timercheck == 1)
			player1[3] = 0; //Timer reset, because a new status has been inflicted.
	}
	// Pain damage
	player1[4] = player1[4] + damagecalc(result, player1[4], player2[1], statsplayer2[0], statsplayer1[3], atkbonus, defbonus, locbonus2[1]);
	if (timercheck == 1)
		player1[5] = 0; //Timer reset, because a new status has been inflicted.
	// Conditioning damage
	player1[6] = player1[6] + damagecalc(result, player1[6], player2[1], statsplayer2[0], statsplayer1[4], atkbonus, defbonus, locbonus2[2]);

	namefix();

	cout << "\nPlayer 1 is " << damagenames[player1[2]] << ", " << paindamagenames[player1[4]] << " and COND " << player1[6] << "!\n";
}

int attackroll(int atkbonus, int defbonus)
{
	int outcome1 = 0, outcome2 = 0;

	outcome1 = basicskillroll(3 + atkbonus); //Attackers rolls 2 dice plus attackbonus, if any. (Will input numbers for skill instead of just 2, later.)
	cout << "\nThe highest outcome of " << 3 + atkbonus << " dice for The Attacker is: " << outcome1 << "\n\n\n";

	outcome2 = basicskillroll(3 + defbonus); //Defender rolls 2 dice plus defensebonus, if any. (Will input numbers for skill instead of just 2, later.)
	cout << "\nThe highest outcome of " << 3 + defbonus << " dice for The Defender is: " << outcome2 << "\n\n";

	cout << "\nThe net result of " << outcome1 << " - " << outcome2 << " is  " << outcome1 - outcome2 << "\n";
	return outcome1 - outcome2;
}

int damagecalc(int result, int status, int power, int str, int res, int atkbonus, int defbonus, int locbonus)
{
	if (result < 0)
	{
		timercheck = 0;
		if (defbonus > 0)
			cout << "\nThe Defender failed.\n";
		else
			cout << "\nThe Attacker missed.\n";
		return 0;
	}
	else
	{
		//cout << "(Status = " << status << " + Attack Pwr = " << power << " + Result = " << result << " = " << status + power + result << ")";
		//if (str > power)
		//    str = power;
		cout << "(Atk Pwr = " << (power - 1) << " + Str = " << str << " - Resist = " << res << " + Result = " << result << " + Loc. Bonus = " << locbonus << " = " << (power - 1) /*- 1*/ + str - res + result + locbonus << ")\n";
		if (((power - 1) + str - res + result + locbonus) > 0)
		{
			timercheck = 1;
			return (power - 1) /*- 1*/ + str - res + result + locbonus;
		}
		else
		{
			timercheck = 0;
			return 0;
		}
	}
}

void statusreset()
{
	if (player1[2] == 5 || player1[2] == 6)
	{
		player1[2] = 0; //Status reset.
		player1[3] = 0; //Timer reset.
		player2[2] = 0; //Status reset.
		player2[3] = 0; //Timer reset.

		player1[4] = 0; //Status reset.
		player1[5] = 0; //Timer reset.
		player2[4] = 0; //Status reset.
		player2[5] = 0; //Timer reset.

		player1[6] = 0; //Status reset.
		player1[7] = 0; //Timer reset.
		player2[6] = 0; //Status reset.
		player2[7] = 0; //Timer reset.

		knockdown1++;
		cout << "\nPlayer 1 has been KNOCKED DOWN " << knockdown1 << " times!\n";
	}
	if (player2[2] == 5 || player2[2] == 6)
	{
		player2[2] = 0; //Status reset.
		player2[3] = 0; //Timer reset.
		player1[2] = 0; //Status reset.
		player1[3] = 0; //Timer reset.

		player2[4] = 0; //Status reset.
		player2[5] = 0; //Timer reset.
		player1[4] = 0; //Status reset.
		player1[5] = 0; //Timer reset.

		player2[6] = 0; //Status reset.
		player2[7] = 0; //Timer reset.
		player1[6] = 0; //Status reset.
		player1[7] = 0; //Timer reset.

		knockdown2++;
		cout << "\nPlayer 2 has been KNOCKED DOWN " << knockdown2 << " times!\n";
	}

	// If a player's STUNNED status is unchanged after two turns of results, then that status goes away. ie: The player didn't get hurt while STUNNED two turns, so they shook it off.
	if ((player1[2] == 3 || player1[2] == 4) && player1[3] > 1)
	{
		player1[2] = 0; //Status reset.
		player1[3] = 0; //Timer reset.
		cout << "\nPlayer 1 recovered and his CONCUSSION status is " << damagenames[player1[2]] << "\n";
	}
	if ((player2[2] == 3 || player2[2] == 4) && player2[3] > 1)
	{
		player2[2] = 0; //Status reset.
		player2[3] = 0; //Timer reset.
		cout << "\nPlayer 2 recovered and his CONCUSSION status is " << damagenames[player2[2]] << "\n";
	}

	// If a player's DISTRACTED status is unchanged after one turn of results, then that status goes away. ie: The player didn't get hurt while DISTRACTED for one turn, so they shook it off.
	if ((player1[2] == 1 || player1[2] == 2) && player1[3] > 0)
	{
		player1[2] = 0; //Status reset.
		player1[3] = 0; //Timer reset.
		cout << "\nPlayer 1 recovered and and his CONCUSSION status is " << damagenames[player1[2]] << "\n";
	}
	if ((player2[2] == 1 || player2[2] == 2) && player2[3] > 0)
	{
		player2[2] = 0; //Status reset.
		player2[3] = 0; //Timer reset.
		cout << "\nPlayer 2 recovered and and his CONCUSSION status is " << damagenames[player2[2]] << "\n";
	}

	// If a player's PAIN 2 status is unchanged after two turns of results, then that status goes away. ie: The player didn't get hurt while STUNNED two turns, so they shook it off.
	if ((player1[4] == 3 || player1[4] == 4) && player1[5] > 1)
	{
		player1[4] = 0; //Status reset.
		player1[5] = 0; //Timer reset.
		cout << "\nPlayer 1 recovered and and his PAIN status is " << paindamagenames[player1[4]] << "\n";
	}
	if ((player2[4] == 3 || player2[4] == 4) && player2[5] > 1)
	{
		player2[4] = 0; //Status reset.
		player2[5] = 0; //Timer reset.
		cout << "\nPlayer 2 recovered and his PAIN status is " << paindamagenames[player2[4]] << "\n";
	}

	// If a player's PAIN 1 status is unchanged after one turn of results, then that status goes away. ie: The player didn't get hurt while DISTRACTED for one turn, so they shook it off.
	if ((player1[4] == 1 || player1[4] == 2) && player1[5] > 0)
	{
		player1[4] = 0; //Status reset.
		player1[5] = 0; //Timer reset.
		cout << "\nPlayer 1 recovered and his PAIN status is " << paindamagenames[player1[4]] << "\n";
	}
	if ((player2[4] == 1 || player2[4] == 2) && player2[5] > 0)
	{
		player2[4] = 0; //Status reset.
		player2[5] = 0; //Timer reset.
		cout << "\nPlayer 2 recovered and his PAIN status is " << paindamagenames[player2[4]] << "\n";
	}

	// Lower player's stats according to conditioning status.
	for (int y = 0; y < 5; y++)
	{
		statsplayer1[y] = permstatsplayer1[y] - (player1[6] / 4);
		statsplayer2[y] = permstatsplayer2[y] - (player2[6] / 4);
	}

	// Maybe do this so player goes from STUNNED to DISTRACTED after one turn?
}

void endgame()
{
	if (knockdown1 == 3)
		cout << "\nPlayer 1 was knocked down " << knockdown1 << " times! Player 2 WINS!\n";

	if (knockdown2 == 3)
		cout << "\nPlayer 2 was knocked down " << knockdown2 << " times! Player 1 WINS!\n";

	if (player1[2] > 6)
		cout << "\nPlayer 1 was knocked out! Player 2 WINS!\n";

	if (player2[2] > 6)
		cout << "\nPlayer 2 was knocked out! Player 1 WINS!\n";
}

void player1valid()
{
	if (player1[2] > 0)
	{
		for (; (player1[0] < 3 || player1[0] > 5);)
		{
			cout << "Incorrect input. Please enter a valid choice: ";
			cin >> player1[0];
		}
	}
	else
	{
		for (; (player1[0] < 1 || player1[0] > 5);)
		{
			cout << "Incorrect input. Please enter a valid choice: ";
			cin >> player1[0];
		}
	}
}

void player2valid()
{
	if (player2[2] > 0)
	{
		for (; (player2[0] < 3 || player2[0] > 5);)
		{
			cout << "Incorrect input. Please enter a valid choice: ";
			cin >> player2[0];
		}
	}
	else
	{
		for (; (player2[0] < 1 || player2[0] > 5);)
		{
			cout << "Incorrect input. Please enter a valid choice: ";
			cin >> player2[0];
		}
	}
}

int d2()
// Rolls a d2 (ie: generates a random number between 1 and 2).
{
	return rand() % 2;
}

int resultcalc(int tempresult)
// Calculates results; for every 1 a +1 is added to 
// the result. 1s are re-rolled.
{
	int extradie = 0, result = 0;
	if (tempresult == 1)
	{
		for (result = 0; tempresult == 1; result++)
		{
			extradie = d2();
			cout << "\nExtra die = " << extradie;
			tempresult = extradie;
		}
	}
	else
	{
		result = tempresult;
	}
	return result;
}

/*
int basicskillroll (int numofdice)
// Flips a number of coins and outputs their results, using resultcalc.
// All results are added together.
// (each 1 equals a +1).
{
int tempresult = 0, result = 0, finalresult = 0, bonus = 0;

for (int count = 1; count <= numofdice; count++)
{
tempresult = 0;
tempresult = d2();
cout<< "\nRoll " << count << " = " << tempresult;
result = resultcalc(tempresult);
cout<< "\nResult " << count << " = " << result << "\n";
finalresult = finalresult + result;
}
return finalresult;
}
*/


int basicskillroll(int numofdice)
// Flips a number of coins and outputs their results, using resultcalc.
// The highest result is taken.
// (each 1 equals a +1).
{
	int tempresult = 0, result = 0, finalresult = 0, bonus = 0;

	for (int count = 1; count <= numofdice; count++)
	{
		tempresult = 0;
		tempresult = d2();
		cout << "\nRoll " << count << " = " << tempresult;
		result = resultcalc(tempresult);
		cout << "\nResult " << count << " = " << result << "\n";
		if (result > finalresult)
			finalresult = result;
	}
	return finalresult;
}


void movenameset()
// Defines the names of the different moves.
{
	movenames[0] = ("PUNCH");
	movenames[1] = ("KICK");
	movenames[2] = ("PARRY");
	movenames[3] = ("DODGE");
	movenames[4] = ("BLOCK");
}

void damagenameset()
// Defines the names of the different levels of concussion damage.
{
	damagenames[0] = ("FINE");
	damagenames[1] = ("DISTRACTED");
	damagenames[2] = ("DISTRACTED");
	damagenames[3] = ("STUNNED");
	damagenames[4] = ("STUNNED");
	damagenames[5] = ("KNOCKED DOWN");
	damagenames[6] = ("KNOCKED DOWN");
	damagenames[7] = ("KNOCKED OUT");

	// Defines the names of the different levels of pain damage.

	paindamagenames[0] = ("FINE");
	paindamagenames[1] = ("PAIN 1");
	paindamagenames[2] = ("PAIN 1");
	paindamagenames[3] = ("PAIN 2");
	paindamagenames[4] = ("PAIN 2");
	paindamagenames[5] = ("PAIN 3");
	paindamagenames[6] = ("PAIN 3");
	paindamagenames[7] = ("PAIN 4");
}

void attribnameset()
// Defines the names of the different moves.
{
	attribnames[0] = ("STR");
	attribnames[1] = ("SPD");
	attribnames[2] = ("RES");
	attribnames[3] = ("WILL");
	attribnames[4] = ("COND");
}

void namefix()
//Makes any outcome greater than 7 = 7, or lower than 0 = 0, so that game doesn't crash.
{
	if (player1[2] < 0)
		player1[2] = 0;
	if (player1[2] > 7)
		player1[2] = 7;
	if (player2[2] < 0)
		player2[2] = 0;
	if (player2[2] > 7)
		player2[2] = 7;

	if (player1[4] < 0)
		player1[4] = 0;
	if (player1[4] > 7)
		player1[4] = 7;
	if (player2[4] < 0)
		player2[4] = 0;
	if (player2[4] > 7)
		player2[4] = 7;
}

