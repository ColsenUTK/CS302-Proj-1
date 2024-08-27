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

Track createTrack(string name, string artist, string album, int trackNumber, string length)
{
    int timeSeconds = convertToSeconds(length);

    Track track = {
        name,
        artist,
        album,
        trackNumber,
        timeSeconds};

    return track;
}

vector<Track> getAllTracks(string fileName)
{
    ifstream fin(fileName);
    istringstream sin;
    string lineBeingRead;

    // the following variables are for reading in with sstream
    string songName;
    string songLength;
    string songArtist;
    string songAlbum;
    string songGenre;
    int songTrackNumber;

    vector<Track> allTracks;

    while (getline(fin, lineBeingRead))
    {
        sin.str(lineBeingRead);

        sin >> songName >> songLength >> songArtist >> songAlbum >> songGenre >> songTrackNumber;

        underscoreToSpace(songName);
        underscoreToSpace(songArtist);
        underscoreToSpace(songAlbum);
        underscoreToSpace(songGenre);

        sin.clear();

        Track trackToAdd = createTrack(songName, songArtist, songAlbum, songTrackNumber, songLength);
        allTracks.push_back(trackToAdd);
    }
    return allTracks;
}

map<string, Album> getAlbums(vector<Track> allTracks)
{
    map<string, Album> albums;
    for (Track &track : allTracks)
    {
        bool albumDoesNotExist = !(albums.find(track.album) == albums.end()); // Chat gpt told me how to do this line
        if (albumDoesNotExist)
        {
            Album albumToAdd;
            albumToAdd.name = track.album;
            albumToAdd.artistName = track.artist;
            albumToAdd.numSongs = 1;
            albumToAdd.timeSeconds = track.timeSeconds;

            albums[track.album] = albumToAdd;
        }
        else
        {
            Album &albumToModify = albums[track.album];
            albumToModify.tracks[track.trackNumber];
            albumToModify.numSongs++;
            albumToModify.timeSeconds += track.timeSeconds;
        }
    }

    return albums;
}

map<string, Artist> getArtists(map<string, Album> albums)
{
    map<string, Artist> artists;

    for (map<string, Album>::iterator it = albums.begin(); it != albums.end(); ++it) // Talked with chatgpt about how to iterate through this
    {
        Album album = it->second;

        bool artistDoesNotExist = !(artists.find(album.artistName) == artists.end()); // copied from the line where Chat gpt told me how to do this line
        if (artistDoesNotExist)
        {
            Artist artistToAdd;
            artistToAdd.albums[album.name] = album;
            artistToAdd.name = album.artistName;
            artistToAdd.numSongs = album.numSongs;
            artistToAdd.timeSeconds = album.timeSeconds;
        }
        else
        {
            Artist &artistToModify = artists[album.artistName];

            artistToModify.albums[album.name] = album;
            artistToModify.numSongs += album.numSongs;
            artistToModify.timeSeconds += album.timeSeconds;
        }
    }
    return artists;
}

void printTracks(map<int, Track> tracks)
{
    for (map<int, Track>::iterator it = tracks.begin(); it != tracks.end(); ++it) // copied from copied from copied from Talked with chatgpt about how to iterate through this
    {
        Track track = it->second;
        cout << "                " << track.trackNumber << ". " << track.title << ": " << convertToMinutesAndSeconds(track.timeSeconds) << endl;
    }
}

void printAlbums(map<string, Album> albums)
{
    for (map<string, Album>::iterator it = albums.begin(); it != albums.end(); ++it) // copied from copied from Talked with chatgpt about how to iterate through this
    {
        Album album = it->second;
        cout << "        " << album.name << ": " << album.numSongs << ", " << convertToMinutesAndSeconds(album.timeSeconds) << endl;
        printTracks(album.tracks);
    }
}

void printEverythingFromArtists(map<string, Artist> artists)
{
    for (map<string, Artist>::iterator it = artists.begin(); it != artists.end(); ++it) // copied from Talked with chatgpt about how to iterate through this
    {
        Artist artist = it->second;
        cout << artist.name << ": " << artist.numSongs << ", " << convertToMinutesAndSeconds(artist.timeSeconds) << endl;
        printAlbums(artist.albums);
    }
}

int main(int argc, char **argv)
{

    // incorrect command line error
    if (argc != 2)
    {
        cerr << "Invalid number of command line args. Format is ./solution [fileName]\n";
        return 0;
    }

    string inputFileName = argv[0];
    string line; // holds a given line of the text file
    ifstream fin(inputFileName);

    // incorrect fileName error
    if (!fin.is_open())
    {
        cerr << "Invalid fileName. Please try again.\n";
        return 0;
    }

    vector<Track> allTracks = getAllTracks(inputFileName);
    map<string, Album> albums = getAlbums(allTracks);
    map<string, Artist> artists = getArtists(albums);

    printEverythingFromArtists(artists);

    return 1;
}
