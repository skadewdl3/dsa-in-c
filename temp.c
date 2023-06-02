#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#define no_of_players 5
#define no_of_deck 1
#define shuffle_cards_this_many_times 20
#define max_rounds (no_of_deck * 52) / no_of_players
#define max_table no_of_players *((max_rounds % no_of_players) + 1)

int deck[no_of_deck * 52];

typedef struct player
{
    int inhand_cards[(no_of_deck * 52)];

} player;

player all_players[no_of_players];

void all_cards_neg()
{
    for (int p = 0; p < no_of_players; p++)
    {
        for (int pc = max_rounds; pc < (no_of_deck * 52); pc++)
        {
            all_players[p].inhand_cards[pc] = -1;
        }
    }
}

void make_deck()
{
    int cat[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    for (int i = 0; i < no_of_deck * 52; i++)
    {
        deck[i] = cat[i % 13];
    }
}

void shuffle()
{
    srand(time(0));

    for (int i = 0; i < shuffle_cards_this_many_times; i++)
    {
        int card1 = rand() % (no_of_deck * 52);
        int card2 = rand() % (no_of_deck * 52);
        while (card2 == card1)
        {
            card2 = rand() % (no_of_deck * 52);
        }
        int temp = deck[card1];
        deck[card1] = deck[card2];
        deck[card2] = temp;
    }
}

void deal_cards()
{

    for (int round = 0; round < max_rounds; round++)
    {
        for (int card = round * no_of_players; card < (round + 1) * no_of_players; card++)
        {
            all_players[card % no_of_players].inhand_cards[round] = deck[card];
        }
    }
}

void sort_inhand_cards()
{
    for (int p = 0; p < no_of_players; p++)
    {
        for (int i = 0; i < max_rounds - 1; i++)
        {
            for (int j = i + 1; j < max_rounds; j++)
            {
                if (all_players[p].inhand_cards[i] > all_players[p].inhand_cards[j])
                {
                    int temp = all_players[p].inhand_cards[i];
                    all_players[p].inhand_cards[i] = all_players[p].inhand_cards[j];
                    all_players[p].inhand_cards[j] = temp;
                }
            }
        }
    }
}


void initialize_cards()
{
    make_deck();
    shuffle();
    deal_cards();
    sort_inhand_cards();
}

typedef struct call
{
    int which_rank;
    int how_many_cards;
    int actual_cards[no_of_deck * 4];
} call;

// TABLE stack of call struct

call table[max_table]; // using array

int top = -1;

void initialize_table()
{
    for (int t = 0; t < max_table; t++)
    {
        table[t].which_rank = 0;
        table[t].how_many_cards = 0;
        for (int ini = 0; ini < no_of_deck * 4; ini++)
        {
            table[t].actual_cards[ini] = 0;
        }
    }
}

void put_card(int hmc, int wr, int ac[])
{
    table[top].how_many_cards = hmc;
    table[top].which_rank = wr;
    for (int i = 0; i < hmc; i++)
    {
        table[top].actual_cards[i] = ac[i];
    }
}

void start_page()
{
    system("cls");
    printf("\n\n\t\t\t\t~~~~~ THE ART OF BLUFFING ~~~~~\n\n");
    printf("\t\t\t\t\t1. START GAME.\n");
    printf("\t\t\t\t\t2. EXIT.\n\n");
    printf("\t\tDEFAULT: \n\t\tDECK : 1\n\t\tPLAYERS: 5\n\n");
}

void exit_page()
{
    system("cls");
    printf("\n\t\t\t~~~~~ Thank you for your time ! ~~~~~\n");
    printf("\n\nDeveloped @ Vishwakarma institute of Technology as DSA course project by >> \n");
    printf("\n\t Kashish V");
    printf("\n\t Shaunak K");
    printf("\n\t Kartik P");
    printf("\n\t Limay K");
    printf("\n\t Nikhil K");
    printf("\n\n\t\t Press Enter to exit. ");
    getch();
    system("cls");
}

void winner_page(int p)
{
    system("cls");
    printf("\n\t\t\t\t ~~~~~ !! PLAYER %d WON !! ~~~~~", p + 1);
    printf("\n\n\tPlayer %d was first to loose all his/her cards, CONGRATULATIONS !!\n", p + 1);
    printf("\n\tPress Enter to continue");
    getch();
}

void last_call()
{
    printf("\t\t\t Last CALL,  %d cards of %d rank each.\n\n", table[top].how_many_cards, table[top].which_rank);
}

void player_dashboard(int p)
{
    system("cls");
    // printf("top = %d", top);
    printf("\n\n\t\t\t\t~~ PLAYER %d ~~\n\n", p + 1);
    printf("\t\t1. SHOW cards.\n");
    printf("\t\t2. SHOW and CALL.\n");
    printf("\t\t3. SHOW and PASS.\n");
    printf("\t\t4. BLUFF !.\n");
    printf("\t\t5. KILL game.\n\n");
    last_call();
}

int no_one_is_watching()
{
    system("cls");
    printf("\n\t\t\t ~~~~~~~~ ! MAKE SURE NOBODY ELSE IS WATCHING ! ~~~~~~~~");
    printf("\n\n\t\t\t\tPress Enter if all clear, and continue ");
    getch();
    return 1;
}

void show_my_cards(int p)
{
    system("cls");
    player_dashboard(p);
    printf("\n\t\t\tYour cards << ");
    for (int i = 0; i < sizeof(all_players[p].inhand_cards) / sizeof(int); i++)
    {
        if (all_players[p].inhand_cards[i] != -1)
        {
            printf("%d ", all_players[p].inhand_cards[i]);
        }
        else
        {
            break;
        }
    }
    printf("\n");
}

int check_if_this_player_winner(int p)
{
    if (p >= 0)
    {
        int fail = 0;
        for (int c = 0; c < max_rounds; c++)
        {
            if (all_players[p].inhand_cards[c] != 0) // if atleast 1 non zero then fail
            {
                fail++;
                break;
            }
            if (c == max_rounds - 1 && fail == 0)
            {
                // this p is winner !!
                return p;
            }
        }
        return -1;
    }
    else
    {
        return -1;
    }
}

void CALL(int p, int pass)
{
    if (!pass)
    {
        top++;
        int HMC, WR, AC[no_of_deck * 4];
        printf("\n\t\tHow many cards, you want to keep on Table ? : ");
        scanf("%d", &HMC);
        printf("\n\t\tWhat is the Rank of each card ? (other's can see this) : ");
        scanf("%d", &WR);
        printf("\n\t\t\t~~ MAKE SURE NOBODY IS WATCHING ~~\n\n\t\t\t  Press Enter to continue: ");
        getch();
        printf("\n\n\t\tActuall Ranks of the cards you kept (other's can't see this): ");

        // cards you keep on table becomes zero in hand
        int same_cards = 0;
        for (int c = 0; c < HMC; c++)
        {
            scanf("%d", &AC[c]);
            for (int i = 0; i < max_rounds; i++)
            {
                if (AC[c] == all_players[p].inhand_cards[i])
                {
                    all_players[p].inhand_cards[i] = 0;
                    break;
                }
            }
            same_cards++;
        }

        printf("\n\t\t\tYour cards NOW <<  ");
        for (int i = 0; i < max_rounds; i++)
        {
            printf("%d ", all_players[p].inhand_cards[i]);
        }
        printf("\n");

        put_card(HMC, WR, AC);
    }
    else if (pass)
    {
        show_my_cards(p);
        printf("\n\n\t\t\t\t ~~~~~ Player %d CALLED PASS ~~~~~ ", p + 1);
        getch();
    }
}

void dump_table(int p)
{
    int ac = 0, pc = max_rounds;
    for (int t = top; t > -1; t--)
    {
        for (ac, pc; ac < table[t].how_many_cards; ac++, pc++)
        {
            all_players[p].inhand_cards[pc] = table[t].actual_cards[ac];
        }
    }
    // return pc;
}

void BLUFF(int p)
{
    int honesty = 1;
    system("cls");
    int prev = (p - 1) % no_of_players;
    printf("\n\t\t\t\t  Player %d called BLUFF on PLayer %d\n", p + 1, prev + 1);
    // previous call data;
    printf("\n\t\t PLayer %d called %d cards of %d rank each, but actually kept this cards: ", prev + 1, table[top].how_many_cards, table[top].which_rank);
    for (int i = 0; i < table[top].how_many_cards; i++)
    {
        printf("%d ", table[top].actual_cards[i]);
    }
    for (int i = 0; i < table[top].how_many_cards; i++)
    {
        if (table[top].actual_cards[i] != table[top].which_rank)
        {
            honesty = 0;
            break;
        }
    }
    if (honesty == 1) // if current player is wrong -> dump all calls on current player
    {
        printf("\n\n\n\t\t\t ~~~~~~~ PLAYER %d was HONEST ! ~~~~~~~", prev + 1);
        printf("\n\n\n\t\t\t ~~~~~~~ PLAYER %d GUESSED WRONG ! ~~~~~~~", p + 1);
        dump_table(p);
        printf("\n\n\n\t\t\t\t Press Enter to continue  ");
        getch();
    }
    else // if current player is right -> dump all calls on prev player
    {
        printf("\n\n\n\t\t\t ~~~~~~~ PLAYER %d was DISHONEST !! and so, BLUFFED !! ~~~~~~~", prev + 1);
        printf("\n\n\n\t\t\t\t\t ~~~~~~~ PLAYER %d GUESSED RIGHT ! ~~~~~~~", p + 1);
        dump_table(prev);
        printf("\n\n\n\t\t\t\t Press Enter to continue");
        getch();
    }
}

int game_kill_warning(int p)
{
    system("cls");
    int kill = 0;
    printf("\n\t\t ~~~~~ GAME KILL WARNING ~~~~~ \n");
    printf("\n\t\t ~~~ YOU ( Player %d ) are KILLING game ! ~~~~~\n\n", p + 1);
    do
    {
        printf("\n\t\t Enter 1 , if all Players agree to kill the game. \n");
        printf("\n\t\t Enter 0 , to continue the game. \n");
        printf("\n\t\t\t\t Option << ");
        scanf("%d", &kill);
    } while (kill != 1 && kill != 0);
    return kill;
}

void main_game_loop()
{
    while (true) // not actually infinite , but until any player wins
    {
        int each_player = -1;
        for (each_player = 0; each_player < no_of_players; each_player++)
        {
            player_dashboard(each_player);
            int game_loop_opt = -1;

        looping_for_actual_options:

            do
            {
                printf("\n\t\t\t Option << ");
                scanf("%d", &game_loop_opt);
            } while (game_loop_opt != 1 && game_loop_opt != 2 && game_loop_opt != 3 && game_loop_opt != 4 && game_loop_opt != 5);

            if ((game_loop_opt == 2 || game_loop_opt == 3) && (check_if_this_player_winner(each_player - 1) != -1))
            {
                winner_page(each_player - 1);
                exit_page();
                exit(0);
            }

            switch (game_loop_opt)
            {
            case 1: // show cards
                if (no_one_is_watching())
                {
                    show_my_cards(each_player);
                }
                goto looping_for_actual_options;

            case 2: // show and call
                show_my_cards(each_player);
                CALL(each_player, 0);
                printf("\n\t\tPress Enter to finish your turn. ");
                getch();
                break;

            case 3: // show and pass
                ;
                int pass = 1;
                CALL(each_player, pass);
                show_my_cards(each_player);
                break;

            case 4:
                BLUFF(each_player);
                show_my_cards(each_player);
                printf("\n\t\tPress Enter to finish your turn. ");
                getch();
                break;

            case 5:
                if (game_kill_warning(each_player))
                {
                    exit_page();
                    exit(0);
                }
                else
                {
                    show_my_cards(each_player);
                    goto looping_for_actual_options;
                }
                break;
            }
        }
    }
}

void loop()
{
    int start_page_opt = -1;
    do
    {
        printf("\t\t\t Option << ");
        scanf("%d", &start_page_opt);
    } while (start_page_opt != 1 && start_page_opt != 2);

    switch (start_page_opt)
    {
    case 1: // start
        main_game_loop();
        break;

    case 2: // exit
        exit_page();
        exit(0);
        break;
    }
}

int main()
{
    // initialize table
    initialize_table();

    // do some pre required stuff
    initialize_cards();

    // extra cards negative
    all_cards_neg();

    // start page
    start_page();

    // loop till winner or exit is pressed
    loop();

    return 0;
}