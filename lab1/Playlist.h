#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
using namespace std;

class PlaylistNode{
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode *nextNodePtr;

    public:
        PlaylistNode();
        PlaylistNode(string, string, string, int);
        void InsertAfter(PlaylistNode*);
        void SetNext(PlaylistNode*);
        string GetID() const;
        string GetSongName() const;
        string GetArtistName() const;
        int GetSongLength() const;
        PlaylistNode* GetNext() const;
        void PrintPlaylistNode();
};

class Playlist {
    private:
        PlaylistNode *head;
        PlaylistNode *tail;
    public: 
        Playlist();
        ~Playlist();
        void AddSong(string, string, string, int);
        void RemoveSong(string);
        int CountNodes() const;
        void ChangePosition(int, int);
        void PrintArtist(string);
        int TotalTime() const;
        void PrintPlaylist();
        bool Empty();
};


#endif
