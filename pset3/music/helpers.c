// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x = fraction[0] - 48;
    int y = fraction[2] - 48;

    if(y != 8)
    {
        x = x * 8 / y;
    }
    return x;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
	float frequency = 440;

	if(note[0] == 'C')
		frequency *= pow(2, (float)-9/12);
	else if(note[0] == 'D')
		frequency *= pow(2, (float)-7/12);
	else if(note[0] == 'E')
		frequency *= pow(2, (float)-5/12);
	else if(note[0] == 'F')
		frequency *= pow(2, (float)-4/12);
	else if(note[0] == 'G')
		frequency *= pow(2, (float)-2/12);
	else if(note[0] == 'A')
        ;
	else if(note[0] == 'B')
		frequency *= pow(2, (float)2/12);
	else
		return 1;

	int octave;

	if(note[1] == 'b' || note[1] == '#')
	{
		octave = atoi(&note[2]);

		if(note[1] == '#')
			frequency *= pow(2, (float)1/12);
		else if(note[1] == 'b')
			frequency /= pow(2, (float)1/12);
		else
			return 2;
	}
	else if(atoi(&note[1]) % 1 == 0)
		octave = atoi(&note[1]);
	else
		return 3;

	frequency *= pow(2, octave - 4);
	int int_freq = round(frequency);
	return int_freq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if(strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
