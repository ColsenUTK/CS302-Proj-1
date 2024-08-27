#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;


struct Song {
    string title;
    int time;
};


struct Album {
    map<int, Song> songs;
    string name;
    int time;
    int numSongs;
};


struct Artist {
    map<string, Album> albums;
    string name;
    int time;
    int numSongs;
};


int convertToSeconds (string timeIn);


int main(int argc, char **argv) {

    if (argc != 2) {
        cerr << "Invalid number of command line args. Format is ./solution [filename]\n";
        return 1;
    }

    string filename = argv[1];
    string line;
    ifstream fin(filename);

    if (!fin.is_open()) {
        cerr << "Invalid filename. Please try again.\n";
        return 1;
    }

    istringstream sin;

    // the following variables are for reading in with sstream
    string songName;
    string songLen;
    string songArtist;
    string songAlbum;
    string songGenre;
    string songTrack;

    while (getline(fin, line)) {
        sin.str(line);

        sin >> songName >> songLen >> songArtist >> songAlbum >> songGenre >> songTrack;

        int songLenInt = 1;

        sin.clear();
    }

    return 0;
}


int convertToSeconds (string timeIn) {
    int timeOut;
    string minsString = "";
    string secsString = "";
    bool isMin = true;
    
    for (int i = 0; i < timeIn.length(); i++)
        if (timeIn[i] != ':' && isMin == true)
            minsString += timeIn[i];
        else if (timeIn[i] != ':' && isMin == false)
            secsString += timeIn[i];
        else
            isMin = false;

    timeOut = 60 * stoi(minsString) + stoi(secsString);

    return timeOut;
}