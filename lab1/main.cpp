#include <iostream>
#include "Playlist.h"
using namespace std;

void PrintMenu(string);

void PrintMenu(string title){
    cout << title << " PLAYLIST MENU"<<endl;
    cout<<"a - Add song"<<endl;
    cout<<"d - Remove song"<<endl;
    cout<<"c - Change position of song"<<endl;
    cout<<"s - Output songs by specific artist"<<endl;
    cout<<"t - Output total time of playlist (in seconds)"<<endl;
    cout<<"o - Output full playlist"<<endl;
    cout<<"q - Quit"<<endl; 
    cout<<endl;
    cout<<"Choose an option:"<<endl;
}


int main(){
    
    string title;
    char input;
    cout<<"Enter playlist's title:"<<endl;
    cout<<endl;
    getline(cin, title);
    PrintMenu(title);
    string id;
    string song;
    string artist;
    int length;
    Playlist playlist;
    cin>>input;
    int original;
    int desired;
    while(input!='q'){
        if(input =='a'){
            cout<<"ADD SONG"<<endl<<"Enter song's unique ID:"<<endl;
            cin>>id;
            cout<<"Enter song's name:"<<endl; 
            cin.ignore();
            getline(cin, song);
            cout<<"Enter artist's name:"<<endl;
            getline(cin, artist);
            cout<<"Enter song's length (in seconds):"<<endl;
            cin >>length; 
            cout<<endl;
            playlist.AddSong(id, song, artist,length);
            PrintMenu(title);
            cin>>input;
        }
        if(input =='d'){
            cout<<"REMOVE SONG" << endl;
            cout<<"Enter song's unique ID:" << endl;
            cin>>id;
            playlist.RemoveSong(id);
            cout<<endl;
            PrintMenu(title);
            cin>>input;
        }
        if(input =='c'){
            cout<<"CHANGE POSITION OF SONG"<<endl;
            cout<<"Enter song's current position:"<<endl;
            cin>>original;
            cout<<"Enter new position for song:"<<endl;
            cin>>desired;
            playlist.ChangePosition(original, desired);
            PrintMenu(title);
            cin>>input;
        }
        if(input =='s'){
            cout<<"OUTPUT SONGS BY SPECIFIC ARTIST"<<endl;
            cout<<"Enter artist's name:"<<endl; 
            cin.ignore();
            getline(cin, artist); 
            cout << endl;
            playlist.PrintArtist(artist);
            PrintMenu(title);
            cin>>input;
        }
        if(input == 't'){
            cout<<"OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)"<<endl;
            cout<<"Total time: "<<playlist.TotalTime()<<" seconds"<<endl;
            cout<<endl;
            PrintMenu(title);
            cin>>input;
        }
        if(input == 'o'){
            cout<<title<<" - OUTPUT FULL PLAYLIST"<<endl;
            playlist.PrintPlaylist();
            PrintMenu(title);
            cin>>input;
        }
        if(input == 'q'){
            return 0;
        }
    }
    return 0;
}













