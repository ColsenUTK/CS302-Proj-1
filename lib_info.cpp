#include <iostream>
#include <string>
#include <map>
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

int main(int argc, char **argv) {

    return 0;
}