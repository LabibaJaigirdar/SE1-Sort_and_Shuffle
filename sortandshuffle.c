
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "sortandshuffle.h"

void sortArtists(Artist artist[], int numOfArtists)
{
    int i, j, minIndex, minIndexChanged;
    Temp swap;
    char lowercase[numOfArtists][MAXSIZE];
    char lowercaseSwap[MAXSIZE];

    //create array with artist names in all lowercase to remove case sensitivity in sorting algorithm
    for (i = 0; i < numOfArtists; i++)
    {
        for (j = 0; artist[i].artistName[j] != '\0'; j++)
        {
            lowercase[i][j] = tolower(artist[i].artistName[j]);
        }
    }

    swap.numTmp = 0;

//sort artists
    for(i = 0; i < (numOfArtists - 1); i ++)
    {
        minIndex = i;
        for(j = i + 1; j < numOfArtists; j++)
        {
            if(strcmp(lowercase[j], lowercase[minIndex]) < 0)
            {
                minIndex = j;
                minIndexChanged = 1;
            }
        }

        if(minIndexChanged == 1)
        {
            swap.nameTmp[MAXSIZE - 1] = '\0';

            //assign artist name to tmp
            strcpy(swap.nameTmp, artist[i].artistName);
            strcpy(lowercaseSwap, lowercase[i]);

            //assign artist song no. to tmp
            swap.numTmp = artist[i].numOfSongs;

            //assign artist songs to tmp
            for (j = 0; j < MAXSONGS; j++)
            {
                swap.songsTmp[j][MAXSIZE - 1] = '\0';
                strcpy(swap.songsTmp[j], artist[i].songs[j]);
            }

            //assign minIndex artist name to artist[i]
            strcpy(artist[i].artistName, artist[minIndex].artistName);
            strcpy(lowercase[i], lowercase[minIndex]);

            //assign minIndex song no. to artist[i]
            artist[i].numOfSongs = artist[minIndex].numOfSongs;

            //assign minIndex songs to artist[i]
            for (j = 0; j < MAXSONGS; j++)
            {
                strcpy(artist[i].songs[j], artist[minIndex].songs[j]);
            }

            //assign swap name to minIndex artist name (i.e. complete swap)
            strcpy(artist[minIndex].artistName, swap.nameTmp);
            strcpy(lowercase[minIndex], lowercaseSwap);

            //assign swap song no. to minIndex song no.
            artist[minIndex].numOfSongs = swap.numTmp;

            //assign swap song names to minIndex song names
            for (j = 0; j < MAXSONGS; j++)
            {
                strcpy(artist[minIndex].songs[j], swap.songsTmp[j]);
            }

            minIndexChanged = 0;
        }

    }

}

void sortSongs(char songs[][MAXSIZE], int numOfSongs)
{

    int i, j, minIndex, minIndexChanged;
    char swap[MAXSIZE] = {0};
    char lowercaseSwap[MAXSIZE] = {0};
    char lowercase[numOfSongs][MAXSIZE];


    //change songs to lowercase for case insensitive comparison
    for (i = 0; i < numOfSongs; i++)
    {
        for (j = 0; songs[i][j] != '\0'; j++)
        {
            lowercase[i][j] = tolower(songs[i][j]);
        }
    }

    //sort songs
    for(i = 0; i < (numOfSongs - 1); i++)
    {
        minIndex = i;
        for(j = i + 1; j < numOfSongs; j++)
        {
            if(strcmp(lowercase[j], lowercase[minIndex]) < 0)
            {
                minIndex = j;
                minIndexChanged = 1;
            }
        }

        if(minIndexChanged == 1)
        {
            swap[MAXSIZE - 1] = '\0';

            //assign song name to swap
            strcpy(swap, songs[i]);
            strcpy(lowercaseSwap, lowercase[i]);

            //assign minindex song name to songs[i]
            strcpy(songs[i], songs[minIndex]);
            strcpy(lowercase[i], lowercase[minIndex]);

            //assign swap to minindex song
            strcpy(songs[minIndex], swap);
            strcpy(lowercase[minIndex], lowercaseSwap);

            minIndexChanged = 0;
        }

    }




}

void shufflePlaylist(char playlist[][MAXSIZE], int numberOfSongs)
{
    int i, j, indexSwap;
    char swap[MAXSIZE] = {0};

    //seed random number generator
    srand(time(NULL));

    //fisher yates algorithm
    for (i = numberOfSongs - 1; i > 0; i--)
    {
        j = rand()%(i + 1);

        if (strcmp(playlist[i], playlist[j]) != 0)
        {
            strcpy(swap, playlist[j]);
            strcpy(playlist[j], playlist[i]);
            strcpy(playlist[i], swap);
        }
    }


    if (numberOfSongs < 12)
    {
        return;
    }

    //check that there are at least 12 songs

    if (numberOfSongs >= 12)
    {
        //ensure that songs dont repeat within 5 songs of each other
        for (i = 0; i < numberOfSongs - 6; i++)
        {
            for (j = i + 1; j <= i + 6; j++)
            {
                if (strcmp(playlist[i], playlist[j]) == 0)
                {
                    indexSwap = i + (rand() % ((numberOfSongs - i - 1) - 6 + 1) + 6);
                    strcpy(swap, playlist[j]);
                    strcpy(playlist[j], playlist[indexSwap]);
                    strcpy(playlist[indexSwap], swap);
                }

            }
        }

        for (i = numberOfSongs - 1; i > numberOfSongs - 6; i--)
        {
            for (j = i - 1; j >= i - 6; j--)
            {
                if (strcmp(playlist[i], playlist[j]) == 0)
                {
                    indexSwap = i - (rand() % ((numberOfSongs - i - 1) - 6 + 1) + 6);
                    strcpy(swap, playlist[j]);
                    strcpy(playlist[j], playlist[indexSwap]);
                    strcpy(playlist[indexSwap], swap);
                }

            }
        }
    }
}




