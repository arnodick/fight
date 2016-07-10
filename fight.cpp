#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;
void options();
void locbonusset();
void statusincrement();
void result();
int attackroll(int atkbonus, int defbonus);
int damagecalc (int status, int power, int str, int res, int atkbonus, int defbonus, int concbonus, int painbonus, int condbonus);
void statusreset();
void endgame();

void player1valid();
void player2valid();

int d2 ();
int resultcalc(int tempresult);
int basicskillroll (int numofdice);

void movenameset();
void damagenameset();
void namefix();


int resultmatrix[5][5] = { 1, 1, 3, 2, 5,
                           1, 1, 2, 3, 5,
                           3, 2, 4, 4, 4,
                           2, 3, 4, 4, 4, 
                           5, 5, 4, 4, 4 };
//This will become a 5x5 array, or larger, as more possibilities are added.

int player1[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}, player2[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
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

int statsplayer1[5] = {2, 2, 2, 2, 2}, statsplayer2[5] = {2, 2, 2, 2, 2};
// First = STR, second = SPD, third = RES, fourth = WILL, fifth = COND.

int knockdown1 = 0, knockdown2 = 0, timercheck = 0;

int locbonus1[3] = {0, 0, 0}, locbonus2[3] = {0, 0, 0};
                            
vector<string> movenames(5);
vector<string> damagenames(8);


int main()
{
    
    srand((unsigned)time(NULL));
    movenameset();
    damagenameset();
    
    for (int x = 1; x == 1; )
    {
     
        //Reset all statuses and counts for a new game.   
        knockdown1 = 0; knockdown2 = 0; player2[2] = 0; player2[3] = 0;  player1[2] = 0;  player1[3] = 0;
        
        for ( ; knockdown1 < 3 && knockdown2 < 3 && player1[2] < 7 && player2[2] < 7; )
        {
    
            options();
            
            statusincrement();
               
            result();
            
            statusreset();
        
        }
        
        endgame();
       
    cout<< "\nIf you would like to continue, press 1:  ";
    cin>> x;
    system("cls");
    }
}

void options()
{
    
    if (player1[2] > 0)
    {
        cout<< "\nPlayer 1 is " << damagenames[player1[2]] << " and may only:\n\n   3) Parry\n   4) Dodge\n   5) Block\n\n   ";
        cin>> player1[0];
        player1valid();
    }
    else
    {
        cout<< "\nPlease choose a move for Player 1:\n\n   1) Punch\n   2) Kick\n   3) Parry\n   4) Dodge\n   5) Block\n\n   ";
        cin>> player1[0];
        player1valid();
        if (player1[0] == 1)
        {
            cout<< "\n   Please choose a power for Player 1's " << movenames[player1[0]-1] << ":\n\n      0) Jab\n      1) Straight\n      2) Uppercut\n      3) Hook\n      4) Haymaker\n\n   ";
            cin>> player1[1];
            cout<< "\n     Please choose a location for Player 1's " << movenames[player1[0]-1] << ":\n\n        1) Head\n        2) Body\n        3) Legs\n\n   ";
            cin>> player1[8];            
        }
        if (player1[0] == 2)
        {
            cout<< "\n   Please choose a power for Player 1's " << movenames[player1[0]-1] << ":\n\n      1) Kick\n\n      3) Roundhouse\n\n      5) Spinning Kick\n\n   ";
            cin>> player1[1];
            cout<< "\n     Please choose a location for Player 1's " << movenames[player1[0]-1] << ":\n\n        1) Head\n        2) Body\n        3) Legs\n\n   ";
            cin>> player1[8];
        }
    }

    if (player2[2] > 0)
    {
        cout<< "\nPlayer 2 is " << damagenames[player2[2]] << " and may only:\n\n   3) Parry\n   4) Dodge\n   5) Block\n\n   ";
        cin>> player2[0];
        player2valid();
    }
    else
    {
        cout<< "\nPlease choose a move for Player 2:\n\n   1) Punch\n   2) Kick\n   3) Parry\n   4) Dodge\n   5) Block\n\n   ";
        cin>> player2[0];
        player2valid();
        if (player2[0] == 1)
        {
            cout<< "\n   Please choose a power for Player 2's " << movenames[player2[0]-1] << ":\n\n      0) Jab\n      1) Straight\n      2) Uppercut\n      3) Hook\n      4) Haymaker\n\n   ";
            cin>> player2[1];
            cout<< "\n     Please choose a location for Player 2's " << movenames[player2[0]-1] << ":\n\n        1) Head\n        2) Body\n        3) Legs\n\n   ";
            cin>> player2[8];
        }
        if (player2[0] == 2)
        {
            cout<< "\n   Please choose a power for Player 2's " << movenames[player2[0]-1] << ":\n\n      1) Front Kick\n\n      3) Roundhouse\n\n      5) Spinning Kick\n\n   ";
            cin>> player2[1];
            cout<< "\n     Please choose a location for Player 2's " << movenames[player2[0]-1] << ":\n\n        1) Head\n        2) Body\n        3) Legs\n\n   ";
            cin>> player2[8];
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
    if (player1[2] > 0)
       player1[3]++;
    if (player2[2] > 0)
       player2[3]++;
}

void result ()
// Uses both players' moves and their comparison in the matrix to output a result for the turn's moves.
{
    int result = 0, atkbonus = 0, defbonus = 0;        

    if (resultmatrix[player2[0]-1][player1[0]-1] == 1)
    {
       atkbonus = 3;
       defbonus = 0; // The person being hit has a -3 to defense, because they are attacking.
       // Compares speed of each player's attack, by checking the speed stat minus the power of the attack. The more powerful an attack, the slower.
       if (statsplayer1[2] - player1[1] > statsplayer2[2] - player2[1])
       {
            cout << "Player 1 was faster than player 2!";
            player2[2] = damagecalc (player2[2], player1[1], statsplayer1[0], statsplayer2[3], atkbonus, defbonus, locbonus1[0], locbonus1[1], locbonus1[2]);
            if (timercheck == 1)
                player2[3] = 0; //Timer reset, because a new status has been inflicted.
            
            namefix();
             
            cout<< "\nPlayer 2 is " << damagenames[player2[2]] << "!\n";
            
            if (player2[2] < 1)
            {
                cout << "\nPlayer 2 fought through the pain!\n";
                player1[2] = damagecalc (player1[2], player2[1], statsplayer2[0], statsplayer1[3], atkbonus, defbonus, locbonus2[0], locbonus2[1], locbonus2[2]);
                if (timercheck == 1)
                    player1[3] = 0; //Timer reset, because a new status has been inflicted.
                
                namefix();
             
                cout<< "\nPlayer 1 is " << damagenames[player1[2]] << "!\n";
            }
            
       }
       else if (statsplayer1[2] - player1[1] == statsplayer2[2] - player2[1])
       {
            cout << "\nBoth players were the same speed, and cancelled each other out!"; 
       }
       else
       {
            cout << "Player 2 was faster than player 1!";
            player1[2] = damagecalc (player1[2], player2[1], statsplayer2[0], statsplayer1[3], atkbonus, defbonus, locbonus2[0], locbonus2[1], locbonus2[2]);
            if (timercheck == 1)
                player1[3] = 0; //Timer reset, because a new status has been inflicted.
            
            namefix();
            
            cout<< "\nPlayer 1 is " << damagenames[player1[2]] << "!\n";
            
            if (player1[2] < 1)
            {
                cout << "\nPlayer 1 fought through the pain!\n";
                player2[2] = damagecalc (player2[2], player1[1], statsplayer1[0], statsplayer2[3], atkbonus, defbonus, locbonus1[0], locbonus1[1], locbonus1[2]);
                if (timercheck == 1)
                    player2[3] = 0; //Timer reset, because a new status has been inflicted.
                
                namefix();
             
                cout<< "\nPlayer 2 is " << damagenames[player2[2]] << "!\n";
            }
       }
    }
       
    if (resultmatrix[player2[0]-1][player1[0]-1] == 2)
    // The attacker made a good choice!
    {
       atkbonus = 3;
       defbonus = 0;
       if (player1[0] == 1 || player1[0] ==  2)
            cout<< "\nPlayer 1 " << movenames[player1[0]-1] <<"ED through Player 2's " << movenames[player2[0]-1] << "!\n";
       else
            cout<< "\nPlayer 2 " << movenames[player2[0]-1] <<"ED through Player 1's " << movenames[player1[0]-1] << "!\n";
            
       if (player1[0] == 1 || player1[0] ==  2)
       {
            player2[2] = damagecalc (player2[2], player1[1], statsplayer1[0], statsplayer2[3], atkbonus, defbonus, locbonus1[0], locbonus1[1], locbonus1[2]);
            if (timercheck == 1)
                player2[3] = 0; //Timer reset, because a new status has been inflicted.
              
            namefix();
              
            cout<< "\nPlayer 2 is " << damagenames[player2[2]] << "!\n";
       }
       else
       {
           player1[2] = damagecalc (player1[2], player2[1], statsplayer2[0], statsplayer1[3], atkbonus, defbonus, locbonus2[0], locbonus2[1], locbonus2[2]);
           if (timercheck == 1)
                player1[3] = 0; //Timer reset, because a new status has been inflicted.
               
           namefix();
               
           cout<< "\nPlayer 1 is " << damagenames[player1[2]] << "!\n";
       }
    }
       
    if (resultmatrix[player2[0]-1][player1[0]-1] == 3)
    // The defender made a good choice!
    {
       atkbonus = 0;
       defbonus = 3;
       if (player1[0] == 3 || player1[0] ==  4)
           cout<< "\nPlayer 1 " << movenames[player1[0]-1] <<"ED Player 2's " << movenames[player2[0]-1] << "!\n";
       else
           cout<< "\nPlayer 2 " << movenames[player2[0]-1] <<"ED Player 1's " << movenames[player1[0]-1] << "!\n";
           
       if (player1[0] == 3 || player1[0] ==  4)
       {
           player2[2] = damagecalc (player2[2], player2[1], 0, 0, atkbonus, defbonus, 0, 0, 0);
           if (timercheck == 1)
                player2[3] = 0; //Timer reset, because a new status has been inflicted.
           
           namefix();
           
           cout<< "\nPlayer 2 is " << damagenames[player2[2]] << "!\n";
       }
       else
       {
           player1[2] = damagecalc (player1[2], player1[1], 0, 0, atkbonus, defbonus, 0, 0, 0);
           if (timercheck == 1)
                player1[3] = 0; //Timer reset, because a new status has been inflicted.
           
           namefix();
           
           cout<< "\nPlayer 1 is " << damagenames[player1[2]] << "!\n";
       }
    }
       
    if (resultmatrix[player2[0]-1][player1[0]-1] == 4)
       cout<< "\nBoth players defended and nothing happened!\n";
       
    if (resultmatrix[player2[0]-1][player1[0]-1] == 5)
    // The defender simply blocked, so a straight comparison of skills is done.
    {
       atkbonus = 0;
       defbonus = 0;
       if (player1[0] == 1 || player1[0] ==  2)
            cout<< "\nPlayer 1 " << movenames[player1[0]-1] <<"ED Player 2's " << movenames[player2[0]-1] << "!\n";
       else
            cout<< "\nPlayer 2 " << movenames[player2[0]-1] <<"ED Player 1's " << movenames[player1[0]-1] << "!\n";
            
       if (player1[0] == 1 || player1[0] ==  2)
       {
            player2[2] = damagecalc (player2[2], player1[1], statsplayer1[0], statsplayer2[3], atkbonus, defbonus, locbonus1[0], locbonus1[1], locbonus1[2]);
            if (timercheck == 1)
                player2[3] = 0; //Timer reset, because a new status has been inflicted.
            
            namefix();
            cout<< "\nPlayer 2 is " << damagenames[player2[2]] << "!\n";
       }
       else
       {
            player1[2] = damagecalc (player1[2], player2[1], statsplayer2[0], statsplayer1[3], atkbonus, defbonus, locbonus2[0], locbonus2[1], locbonus2[2]);
            if (timercheck == 1)
                player1[3] = 0; //Timer reset, because a new status has been inflicted.
            
            namefix();
            
            cout<< "\nPlayer 1 is " << damagenames[player1[2]] << "!\n";
       }
   }
}

int attackroll(int atkbonus, int defbonus)
{
    int outcome1 = 0, outcome2 = 0;
    
    outcome1 = basicskillroll(3+atkbonus); //Attackers rolls 2 dice plus attackbonus, if any. (Will input numbers for skill instead of just 2, later.)
    cout<< "\nThe highest outcome of " << 3 + atkbonus << " dice for The Attacker is: " << outcome1 << "\n\n\n";
    
    outcome2 = basicskillroll(3+defbonus); //Defender rolls 2 dice plus defensebonus, if any. (Will input numbers for skill instead of just 2, later.)
    cout<< "\nThe highest outcome of " << 3 + defbonus << " dice for The Defender is: " << outcome2 << "\n\n";
    
    cout<< "\nThe net result of " << outcome1 << " - " << outcome2 << " is  " << outcome1 - outcome2 << "\n";
    return outcome1 - outcome2;
}

int damagecalc (int status, int power, int str, int res, int atkbonus, int defbonus, int concbonus, int painbonus, int condbonus)
{
    int result;
    if (defbonus > 0)
        result = -attackroll(atkbonus, defbonus); //Flip the result number, because the defender is the focus of the calculatiosn below, and the defender's result is subtracted from the attackers.
    else
        result = attackroll(atkbonus, defbonus);
    if (result < 0)
    {
        timercheck = 0;
        if (defbonus > 0)
            cout<< "\nThe Defender failed.\n";
        else
            cout<< "\nThe Attacker missed.\n";
        return status;
    }
    else
    {
        //cout << "(Status = " << status << " + Attack Pwr = " << power << " + Result = " << result << " = " << status + power + result << ")";
        if (str > power)
            str = power;
        cout << "(Attack Pwr = " << power << " + Strength = " << str << " - Resistance = " << res << " + Result = " << result << " + Conc. Bonus = " << concbonus << " = " << power /*- 1*/ + str - res + result + concbonus<< ")";
        if ( (power + str - res + result + concbonus) > status)
        {
            timercheck = 1;
            return power /*- 1*/ + str - res + result + concbonus; //Player 2 was hit, so her status becomes the power of the strike she was hit with plus whatever her current damage status is, plus the net result of the dice.
        }
        else
        {
            timercheck = 0;
            return status;
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
       knockdown1++;
       cout<< "\nPlayer 1 has been KNOCKED DOWN " << knockdown1 << " times!\n";
    }
    if (player2[2] == 5 || player2[2] == 6)
    {
       player2[2] = 0; //Status reset.
       player2[3] = 0; //Timer reset.
       player1[2] = 0; //Status reset.
       player1[3] = 0; //Timer reset.
       knockdown2++;
       cout<< "\nPlayer 2 has been KNOCKED DOWN " << knockdown2 << " times!\n";
    }
       
    // If a player's STUNNED status is unchanged after two turns of results, then that status goes away. ie: The player didn't get hurt while STUNNED two turns, so they shook it off.
    if ( (player1[2] == 3 || player1[2] == 4) && player1[3] > 1)
    {
       player1[2] = 0; //Status reset.
       player1[3] = 0; //Timer reset.
       cout<< "\nPlayer 1 recovered and is " << damagenames[player1[2]] << "\n";
    }
    if ( (player2[2] == 3 || player2[2] == 4) && player2[3] > 1)
    {
       player2[2] = 0; //Status reset.
       player2[3] = 0; //Timer reset.
       cout<< "\nPlayer 2 recovered and is " << damagenames[player2[2]] << "\n";
    }
    
    // If a player's DISTRACTED status is unchanged after one turn of results, then that status goes away. ie: The player didn't get hurt while DISTRACTED for one turn, so they shook it off.
    if ( (player1[2] == 1 || player1[2] == 2) && player1[3] > 0)
    {
       player1[2] = 0; //Status reset.
       player1[3] = 0; //Timer reset.
       cout<< "\nPlayer 1 recovered and is " << damagenames[player1[2]] << "\n";
    }
    if ( (player2[2] == 1 || player2[2] == 2) && player2[3] > 0)
    {
       player2[2] = 0; //Status reset.
       player2[3] = 0; //Timer reset.
       cout<< "\nPlayer 2 recovered and is " << damagenames[player2[2]] << "\n";
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
        for ( ; (player1[0] < 3 || player1[0] > 5); )
        {
            cout<< "Incorrect input. Please enter a valid choice: ";
            cin>> player1[0];
        }
    }
    else
    {
        for ( ; (player1[0] < 1 || player1[0] > 5); )
        {
            cout<< "Incorrect input. Please enter a valid choice: ";
            cin>> player1[0];
        }
    }     
}

void player2valid()
{
     if (player2[2] > 0)
    {
        for ( ; (player2[0] < 3 || player2[0] > 5); )
        {
            cout<< "Incorrect input. Please enter a valid choice: ";
            cin>> player2[0];
        }
    }
    else
    {
        for ( ; (player2[0] < 1 || player2[0] > 5); )
        {
            cout<< "Incorrect input. Please enter a valid choice: ";
            cin>> player2[0];
        }
    }     
}

int d2()
// Rolls a d2 (ie: generates a random number between 1 and 2).
{
    return rand() % 2; 
}

int resultcalc (int tempresult)
// Calculates results; for every 1 a +1 is added to 
// the result. 1s are re-rolled.
{
    int extradie = 0, result = 0;
    if (tempresult == 1)
    {
       for (result = 0; tempresult == 1; result++)
       {
           extradie = d2();
           cout<< "\nExtra die = " << extradie;
           tempresult = extradie;
       }
    }
    else
    {
        result = tempresult;
    }
    return result;
}


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


/*
int basicskillroll (int numofdice)
// Flips a number of coins and outputs their results, using resultcalc.
// The highest result is taken.
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
        if (result > finalresult)
            finalresult = result;
    }
    return finalresult;
}
*/

void movenameset()
// Defines the names of the different moves.
{
    movenames[0]=("PUNCH");
    movenames[1]=("KICK");
    movenames[2]=("PARRY");
    movenames[3]=("DODGE");
    movenames[4]=("BLOCK");
}

void damagenameset()
// Defines the names of the different levels of damage.
{
    damagenames[0]=("FINE");
    damagenames[1]=("DISTRACTED");
    damagenames[2]=("DISTRACTED");
    damagenames[3]=("STUNNED");
    damagenames[4]=("STUNNED");
    damagenames[5]=("KNOCKED DOWN");
    damagenames[6]=("KNOCKED DOWN");
    damagenames[7]=("KNOCKED OUT");
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
}

