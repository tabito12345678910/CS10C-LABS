#include <iostream>
#include "Playlist.h"
using namespace std;

/*node class def*/

/*constructors*/
PlaylistNode::PlaylistNode(){
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}

PlaylistNode::PlaylistNode(string id, string song, string artist, int len){
    uniqueID = id;
    songName = song;
    artistName = artist;
    songLength = len;
}

/*accessors*/

string PlaylistNode::GetID() const{
    return uniqueID;
}

string PlaylistNode::GetSongName() const{
    return songName;
}

string PlaylistNode::GetArtistName() const{
    return artistName;
}

int PlaylistNode::GetSongLength() const{
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const{
    return nextNodePtr;
}

/*modifier*/

void PlaylistNode::SetNext(PlaylistNode* node){
    nextNodePtr=node;
}

void PlaylistNode::InsertAfter(PlaylistNode* node){
    node->SetNext(this->GetNext());
    this->SetNext(node);
}

/*Print*/

void PlaylistNode::PrintPlaylistNode(){
    cout<< "Unique ID: "<<uniqueID<<endl;
    cout<< "Song Name: "<<songName<<endl;
    cout<< "Artist Name: "<<artistName<<endl;
    cout<< "Song Length (in seconds): "<<songLength<<endl;
}


/*list class def*/

/*constructor and deconstructor*/

Playlist::Playlist(){
    head = nullptr;
    tail = nullptr;
}

Playlist::~Playlist(){  
    PlaylistNode *curr=head;
    while(curr != nullptr){
        PlaylistNode *next=curr->GetNext();
        delete curr;
        curr = next;
    }
    head = nullptr;
    tail = nullptr;
}


void Playlist::AddSong(string id, string song, string artist, int length){
    PlaylistNode *temp = new PlaylistNode(id, song, artist, length);
    if(head == nullptr){
        head = temp;
        tail = temp;
    } else {
        tail->SetNext(temp);
        tail = temp;
    }
}

void Playlist::RemoveSong(string id){
    if(head->GetID() == id){ //special case for front node
        cout<<"\""<<head->GetSongName()<<"\" removed."<<endl;
        PlaylistNode *temp = head;
        head = nullptr;
        tail = nullptr;
        delete temp;
    } else { 
        PlaylistNode *prev = head;
        PlaylistNode *curr = head->GetNext();
        while(curr != nullptr){
            if(curr->GetID() == id){
                cout<<"\""<<curr->GetSongName()<<"\" removed."<<endl;
                prev->SetNext(curr->GetNext());
                delete curr;
                curr = prev->GetNext();
                return;
            }
            prev = prev->GetNext();
            curr = curr->GetNext();
        }
    }
}

int Playlist::CountNodes() const{
    int count = 0;
    PlaylistNode *curr = head;
    if(head == nullptr){
        return 0;
    } else {
        while(curr != nullptr){
            count++;
            curr = curr->GetNext();
        }
    }
    return count;
}

bool Playlist::Empty(){
    if(head==nullptr){
        return true;
    }
    else{
        return false;
    }
}

void Playlist::ChangePosition(int original, int desired){
    if(original < 1 || original > this->CountNodes() || original == desired){
        return;
    }

    PlaylistNode *curr = head; 
    PlaylistNode *prev = nullptr; 
    int i = 1;
    while(i < original){
        if(curr != nullptr){
            prev = curr;
            curr = curr->GetNext();
            i++;
        }
    }
    i = 1; 
    PlaylistNode *curr1 = head; 
    PlaylistNode *prev1 = nullptr; 
    while(i < desired){
        if(curr != nullptr){
            prev1 = curr1;
            curr1 = curr1->GetNext();
            i++;
        }
    }

    //Connects node before fromIndex to node after fromIndex
    if(prev != nullptr){
        prev->SetNext(curr->GetNext()); 
    } else {
        head = curr->GetNext();
    }
    if(curr == tail){
        tail = prev;
    }

    //Moves fromIndex node to the toIndex node location
    if(desired <= 1){
        curr->SetNext(head);
        head = curr;
        cout<<"\""<<curr->GetSongName()<<"\""<<" moved to position "<<desired<<endl;
        cout<<endl;
    } else {
        if(desired < original){
            curr->SetNext(curr1);
            prev1->SetNext(curr);
        } else {
            curr1->InsertAfter(curr);
            if(curr->GetNext() == nullptr){
                tail = curr;
            }
        }
        cout<<"\""<<curr->GetSongName()<<"\""<<" moved to position "<<desired<<endl;
        cout<<endl;
    }
}

void Playlist::PrintPlaylist(){
    if(Empty()){
        cout<<"Playlist is empty"<<endl;
        cout<<endl;
        return;
    }
    PlaylistNode *curr = head;
    int i = 1;
    while(curr != nullptr){
        cout<<i<<"."<<endl; 
        curr->PrintPlaylistNode(); 
        cout<<endl;

        curr = curr->GetNext(); 
        i++;
    }
}

void Playlist::PrintArtist(string artistName){
    PlaylistNode *curr = head;
    int i = 1;
    while(curr != nullptr){
        if(curr->GetArtistName() == artistName){
            cout<<i<<"."<<endl; 
            curr->PrintPlaylistNode(); 
            cout<<endl;
        }
        curr = curr->GetNext(); 
        i++;
    }
}

int Playlist::TotalTime() const{
    PlaylistNode *curr = head;
    int total = 0;
    while(curr != nullptr){
        total += curr->GetSongLength();
        curr = curr->GetNext();
    }
    return total;
}









