#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

struct Track
{ // holds an individual song
    string title;
    string artist;
    string album;
    int songTrackNumber;
    int timeSeconds;
};

struct Album
{ // each album holds a container of its associated songs
    map<int, Track> songs;
    string name;
    int time;
    int numSongs;
};

struct Artist
{ // each artist holds a container of its associated albums
    map<string, Album> albums;
    string name;
    int time;
    int numSongs;
};

int convertToSeconds(string timeIn); // convert time in [min:sec] format to secs

string convertToMinutesAndSeconds(int timeIn); // converts time in secs back to [min:sec] format

void underscoreToSpace(string &input); // converts all underscores in an input to spaces

int main(int argc, char **argv)
{

    // incorrect command line error
    if (argc != 2)
    {
        cerr << "Invalid number of command line args. Format is ./solution [filename]\n";
        return 1;
    }

    string filename = argv[1];
    string line; // holds a given line of the text file
    ifstream fin(filename);

    // incorrect filename error
    if (!fin.is_open())
    {
        cerr << "Invalid filename. Please try again.\n";
        return 1;
    }

    istringstream sin;

    vector<string> songInputStrings;

    // the following variables are for reading in with sstream
    string songName;
    string songLen;
    string songArtist;
    string songAlbum;
    string songGenre;
    int songTrack;

    while (getline(fin, line))
    {
        sin.str(line);

        sin >> songName >> songLen >> songArtist >> songAlbum >> songGenre >> songTrack;

        int songLenInt = convertToSeconds(songLen); // gives us a time in secs for the album map

        underscoreToSpace(songName);
        underscoreToSpace(songArtist);
        underscoreToSpace(songAlbum);
        underscoreToSpace(songGenre);

        sin.clear();

        trackToAdd = createTrack(songName, songArtist, songAlbum, songGenre);
    }

    /*


    This section here needs to be done.

    Maps on each level need to be formed.


    */

    /*

    We need to do output here

    */

    return 0;
}

int convertToSeconds(string timeIn)
{
    int outputTime;
    string mins = "";
    string secs = "";
    bool isMin = true; // this differentiates between the left and right of the colon

    for (size_t i = 0; i < timeIn.length(); i++)

        if (timeIn[i] != ':' && isMin == true) // left of the colon
            mins += timeIn[i];
        else if (timeIn[i] != ':' && isMin == false) // right of the colon
            secs += timeIn[i];
        else // is the colon
            isMin = false;

    outputTime = 60 * stoi(mins) + stoi(secs); // convert mins to secs and add to existing secs

    return outputTime;
}

string convertToMinutesAndSeconds(int timeIn)
{
    string outputTime;
    string min, sec;

    min = to_string(timeIn / 60);
    sec = to_string(timeIn % 60);

    outputTime = min + ':' + sec;

    return outputTime;
}

void underscoreToSpace(string &input)
{
    int len = input.length();

    for (int i = 0; i < len; i++)
        if (input[i] == '_')
            input[i] = ' ';
}

Track createTrack(songName, songArtist, songAlbum, songGenre)
{
    Track track = {} return
}
