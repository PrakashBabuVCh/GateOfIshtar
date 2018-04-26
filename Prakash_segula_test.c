#include <stdio.h>
#include <time.h>

#define TRUE 1U
#define FALSE 0U

typedef char uint8_t;
typedef unsigned int uint16_t;

uint8_t Get_Magical_Champion(uint8_t champion);
uint8_t Get_Holly_Days(uint8_t date);


enum 
{
Human = 0,
Wizard,
Spirit,
Giant,
Vampire,
Champions_max
}Champions_health_t;

/*****************************/
//Following function covers the requirement
//1) The amount of health (HP) a champion may lose varies between 7 and 25 HP depending on the time of the day (different god and demon forces are appearing during the day).
//2) “Brand” the god of fire and “Mithra” goddess of the sun have the highest damage and a champion will lose more HP when they are guarding!
/*****************************/
uint8_t calculate_damage_taken(uint8_t champion)
{
    time_t l_time = time(NULL);
    struct tm current_time = *localtime(&l_time);
    
    if ((uint8_t)Get_Holly_Days(current_time.tm_mday) || (uint8_t)Get_Magical_Champion(champion))
	{
        return 0;
	}
    // "Janna" demon of Wind spawned
    if ((current_time.tm_hour == 6) && (current_time.tm_min >= 0) && (current_time.tm_min <= 29))
	{
        return 7;
	}
		
    // "Tiamat" goddess of Oceans spawned
    else if ((current_time.tm_hour == 6) && (current_time.tm_min >= 30) && (current_time.tm_min <= 59))
	{
        return 18;
	}
    // "Mithra" goddess of sun spawned
    else if ((current_time.tm_hour == 7) && (current_time.tm_min >= 0) && (current_time.tm_min <= 59))
	{
        return 25;
	}
    // "Warwick" God of war spawned
    else if ((current_time.tm_hour == 8) && (current_time.tm_min >= 0) && (current_time.tm_min <= 29))
	{
        return 18;
	}
    // "Kalista" demon of agony spawned
    else if ((current_time.tm_hour >= 8) && (current_time.tm_hour <= 14) && (current_time.tm_min >= 30) && (current_time.tm_min <= 59))
	{
        return 7;
	}
    // "Ahri" goddess of wisdom spawned
    else if ((current_time.tm_hour == 15) && (current_time.tm_min >= 0) && (current_time.tm_min <= 29))
	{
        return 13;
	}
    // "Br&&" god of fire spawned
    else if ((current_time.tm_hour == 15) && (current_time.tm_min >= 30) || (current_time.tm_hour == 16) && (current_time.tm_min <= 59))
	{
        return 25;
	}
    // "Rumble" god of lightning spawned
    else if ((current_time.tm_hour == 17) && (current_time.tm_min >= 0) && (current_time.tm_min <= 59))
	{
        return 18;
	}
    // "Skarner" the scorpion demon spawned
    else if ((current_time.tm_hour >= 18) && (current_time.tm_hour <= 19) && (current_time.tm_min >= 0) && (current_time.tm_min <= 59))
	{
        return 7;
	}
    // "Luna" The goddess of the moon spawned
    else if ((current_time.tm_hour == 20) && (current_time.tm_min <=59))
	{
        return 13;
	}
    else
	{
        return 0;
	}
}

/*****************************/
//Following function covers the requirement
//5) Tuesdays and Thursdays are holly days in ancient babylon, so neither gods nor demons roam around the Gate. Our champions are safe from harm on the holly days.
/*****************************/
uint8_t Get_Holly_Days(uint8_t date)
{
	//Tuesday && Thursday
	if((date == 1)|| (date == 3))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*****************************/
//Following function covers the requirement
//4) Some Magical champions (e.g. Wizards, Spirits) are able to deceive the guards and pass through the gate without losing any HP
/*****************************/
uint8_t Get_Magical_Champion(uint8_t champion)
{
	//Tuesday && Thursday
	if((champion == Wizard)|| (champion == Spirit))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*****************************/
//Following function covers the requirement
//3) Champion should only lose HP once every hour
/*****************************/
uint8_t calculate_champion_timegap(long int time)
{
    static int l_time_check = 0;
	static long int l_prevtime = 0;
	
	//CHeck based on the real time date
	if(time != l_prevtime)
	{
	    l_time_check++;
		l_prevtime = time;
		if(l_time_check == 1)
		{
		   return TRUE;
		}
	}
	else
	{	
	    if(l_time_check == 3600) // 1hr = 60min = 60X60 seconds
		{
		   l_time_check =0;
		}
	    return FALSE;
	}
}

void main()
{
    //Champions initial health are (Requirement 6)
    const int Champions_HP[Champions_max] = {100, 100, 100, 150, 110};
    const char Champions_names[Champions_max][10] = {"Human", "Wizard", "Spirit", "Giant", "Vampire"};    
    int life_left[Champions_max] = {0};
    int Loop_run_over[Champions_max] = {0};
    int total_damage;
	
	//get the time
    time_t l_time = time(NULL);
    struct tm tm = *localtime(&l_time);
	
	//Copy the strings
    strcpy(Champions_names[Human], "Human");
    strcpy(Champions_names[Wizard], "Wizard");
    strcpy(Champions_names[Spirit], "Spirit");
    strcpy(Champions_names[Giant], "Giant");
    strcpy(Champions_names[Vampire], "Vampire");
    
	printf("SegulaTechnologies - GateOfIshtar \n");
    printf("List of champions : 1.Human 2.Wizard 3.Spirit 4.Giant 5.Vampire\n");
	
	//Run the loop until champions gets run out of health
    while((Loop_run_over[Human] != 1) || (Loop_run_over[Wizard] != 1) || (Loop_run_over[Spirit] != 1) || (Loop_run_over[Giant] != 1) || (Loop_run_over[Vampire] != 1))
    {
	    // get the time interval of 1hour
        if(TRUE == calculate_champion_timegap(tm.tm_sec))
        {
		    // check of all champions
            for(int l_output=Human; l_output<Champions_max; l_output++)
            {
				total_damage = calculate_damage_taken(l_output);
				life_left[l_output] = Champions_HP[l_output] - total_damage;            
            
                if (life_left[l_output] <= 0)
            	{
                    printf("%s is Dead\n", Champions_names[l_output]);
            		Loop_run_over[l_output] = 1;
            	}
                else
            	{
                    printf("%s has %d HP left\n", Champions_names[l_output], life_left[l_output]);
            	}            
            }
        }
        else
        {
        	//do nothing
        }
    }
	
	printf("Champions health is zero");
}