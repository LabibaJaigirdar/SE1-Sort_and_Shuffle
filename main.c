#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sortandshuffle.h"

int main()
{
    Artist artists[MAXARTISTS];
    int numOfArtists, h, i, j, k;
    int totalSongs = 0;
    int playlistNumOfSongs = 0;

    //enter artists and songs
    numOfArtists = insertArtistsAndSongs(artists);

    //sort artists
    sortArtists(artists, numOfArtists);

    //sort songs
    for (i = 0; i < numOfArtists; i++)
    {
        sortSongs(artists[i].songs, artists[i].numOfSongs);
    }

    //print sorted list of artists and songs
    printf("\nSorted list of songs:\n");
    for (i = 0; i < numOfArtists; i++)
    {
        printf("\n%s\n", artists[i].artistName);

        for (j = 0; j < artists[i].numOfSongs; j++)
        {
            printf("- %s\n", artists[i].songs[j]);
        }

    }

    //get total number of songs
    for (i = 0; i < numOfArtists; i++)
    {
        totalSongs = totalSongs + artists[i].numOfSongs;
    }

    playlistNumOfSongs = totalSongs * 2;

    //make array for playlist
    char playlist[playlistNumOfSongs][MAXSIZE];

    for (i = 0; i < playlistNumOfSongs; i++)
    {
        playlist[i][0] = '\0';
    }

    k = 0;

    //copy all songs twice into one array for shuffling

    for (h = 0; h < 2; h++)
    {
        for (i = 0; i < numOfArtists; i++)
        {

            for (j = 0; j < artists[i].numOfSongs; j++)
            {
                strcpy(playlist[k], artists[i].artistName);
                strcat(playlist[k], " - ");
                strcat(playlist[k], artists[i].songs[j]);
                k++;
            }
        }
    }

    //shuffle playlist
    shufflePlaylist(playlist, playlistNumOfSongs);

    //print shuffled playlist
    printf("\nShuffled playlist:\n");
    for (i = 0; i < playlistNumOfSongs; i++)
    {
        printf("%s\n", playlist[i]);
    }


}

int insertArtistsAndSongs(Artist artists[])
{
    int numOfArtists = 0;
    int i, j;
    int len = 0;


    printf("Enter %% to end artist input.\n");

    for (i = 0; i < MAXARTISTS; i++)
    {
        //sets number of songs for artist to 0
        artists[i].numOfSongs = 0;

        //enter artists
        printf("\nPlease enter an artist name.\n");
        fgets(artists[i].artistName, MAXSIZE, stdin);

        //if % is entered, artist input ends
        if (artists[i].artistName[0] == '%')
        {
            artists[i].artistName[0] = '\0';
            break;
        }

        //Removes newline from artist name
        len = strlen(artists[i].artistName);
        artists[i].artistName[len - 1] = '\0';

        printf("\nEnter %% to end song input.\n");
        //enter songs
        for (j = 0; j < MAXSONGS; j++)
        {

            printf("\nPlease enter song %d of %s\n", j + 1, artists[i].artistName);
            fgets(artists[i].songs[j], MAXSIZE, stdin);

            if (artists[i].songs[j][0] == '%')
            {
                artists[i].songs[j][0] = '\0';
                break;
            }

            //Removes newline from song name
            len = strlen(artists[i].songs[j]);
            artists[i].songs[j][len - 1] = '\0';

            artists[i].numOfSongs++;

        }
        numOfArtists++;
    }

    return numOfArtists;
}


