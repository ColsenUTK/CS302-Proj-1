#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

// structs are from lab document (Dr. Emrich)

struct Track
{ // holds an individual song
    string title;
    string artist;
    string album;
    int trackNumber;
    int timeSeconds;
};

struct Album
{ // each album holds a container of its associated songs
    map<int, Track> tracks;
    string name;
    string artistName;
    int timeSeconds;
    int numSongs;
};

struct Artist
{ // each artist holds a container of its associated albums
    map<string, Album> albums;
    string name;
    int timeSeconds;
    int numSongs;
};

int convertToSeconds(string timeIn); // convert time in [min:sec] format to secs

string convertToMinutesAndSeconds(int timeIn); // converts time in secs back to [min:sec] format

void underscoreToSpace(string &input); // converts all underscores in an input to spaces

int convertToSeconds(string timeIn)
{
    // cout << "This is the time in c2s func:  " << timeIn << endl;

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

    if (sec.length() < 2)
    {
        outputTime = min + ":0" + sec;
    }
    else
    {
        outputTime = min + ':' + sec;
    }

    return outputTime;
}

void underscoreToSpace(string &input)
{
    int len = input.length();

    for (int i = 0; i < len; i++)
        if (input[i] == '_')
            input[i] = ' ';
}

void printTracks(map<int, Track> tracks)
{
    // cout << "PRINT TRACKS RAN" << endl;
    // cout << tracks.size() << endl;
    for (map<int, Track>::iterator it = tracks.begin(); it != tracks.end(); ++it) // copied from copied from copied from Talked with chatgpt about how to iterate through this
    {
        Track track = it->second;
        cout << "                " << track.trackNumber << ". " << track.title << ": " << convertToMinutesAndSeconds(track.timeSeconds) << endl;
    }
}

void printAlbums(map<string, Album> albums)
{
    // cout << "PRINT ALBUMS AND TRACKS RAN" << endl;
    for (map<string, Album>::iterator it = albums.begin(); it != albums.end(); ++it) // copied from copied from Talked with chatgpt about how to iterate through this
    {
        Album album = it->second;
        cout << "        " << album.name << ": " << album.numSongs << ", " << convertToMinutesAndSeconds(album.timeSeconds) << endl;
        printTracks(album.tracks);
    }
}

void printArtists(map<string, Artist> artists)
{
    for (map<string, Artist>::iterator it = artists.begin(); it != artists.end(); ++it) // copied from Talked with chatgpt about how to iterate through this
    {
        Artist artist = it->second;
        cout << artist.name << ": " << artist.numSongs << ", " << convertToMinutesAndSeconds(artist.timeSeconds) << endl;
        printAlbums(artist.albums);
    }
}

int main(int argc, char **argv) {

    // incorrect command line error
    if (argc != 2)
    {
        cerr << "Invalid number of command line args. Format is ./solution [fileName]\n";
        return 0;
    }

    string inputFileName = argv[1];
    string line; // holds a given line of the text file
    ifstream fin(inputFileName);

    // incorrect fileName error
    if (!fin.is_open())
    {
        cerr << "Invalid fileName. Please try again.\n";
        return 0;
    }

    istringstream sin;

    // the following variables are for reading in with sstream
    string songName;
    string songLength;
    string songArtist;
    string songAlbum;
    string songGenre;
    int songTrackNumber;

    vector<Track> allTracks;

    while (getline(fin, line))
    {
        sin.str(line);

        sin >> songName >> songLength >> songArtist >> songAlbum >> songGenre >> songTrackNumber;

        underscoreToSpace(songName);
        underscoreToSpace(songArtist);
        underscoreToSpace(songAlbum);
        underscoreToSpace(songGenre);

        sin.clear();

        int timeSeconds = convertToSeconds(songLength);

        Track trackToAdd = {
            songName,
            songArtist,
            songAlbum,
            songTrackNumber,
            timeSeconds};

        allTracks.push_back(trackToAdd);
    }
    
    map<string, Artist> artists;

    for (size_t i = 0; i < allTracks.size(); i++) {
        Track currentTrack = allTracks[i];

        bool newArtist = artists.find(currentTrack.artist) == artists.end();

        if (newArtist) {        // artist is not in list yet

            Album albumToAdd = {
                {},
                currentTrack.album,
                currentTrack.artist,
                currentTrack.timeSeconds,
                1
            };
            albumToAdd.tracks[currentTrack.trackNumber] = currentTrack;

            Artist artistToAdd = {
                {},
                currentTrack.artist,
                currentTrack.timeSeconds,
                1
            };
            artistToAdd.albums[currentTrack.album] = albumToAdd;

            artists[artistToAdd.name] = artistToAdd;

        } else {                // artist exists

            bool newAlbum = artists[currentTrack.artist].albums.find(currentTrack.album) == artists[currentTrack.artist].albums.end();

            if (newAlbum) {     // album is new to this artist

                Album albumToAdd = {
                    {},
                    currentTrack.album,
                    currentTrack.artist,
                    currentTrack.timeSeconds,
                    1
                };

                albumToAdd.tracks[currentTrack.trackNumber] = currentTrack;

                artists[currentTrack.artist].albums[albumToAdd.name] = albumToAdd;
                artists[currentTrack.artist].timeSeconds += currentTrack.timeSeconds;
                artists[currentTrack.artist].numSongs++;

            } else {            // album already exists for artist

                artists[currentTrack.artist].albums[currentTrack.album].tracks[currentTrack.trackNumber] = currentTrack;
                artists[currentTrack.artist].albums[currentTrack.album].timeSeconds += currentTrack.timeSeconds;
                artists[currentTrack.artist].albums[currentTrack.album].numSongs++;
                artists[currentTrack.artist].timeSeconds += currentTrack.timeSeconds;
                artists[currentTrack.artist].numSongs++;

            }
        }
    }


    printArtists(artists);

    return 0;
}
