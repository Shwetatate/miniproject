#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> 
#include <ctime>     
#include <cstdlib>  

using namespace std;

class Media {
public:
    Media() {}
};

class Multimedia : public Media {
public:
    Multimedia() {}
}; 

class Song : public Multimedia {
public:
    Song(string title, string artist) : title(title), artist(artist) {}

    string getTitle() const {
        return title;
    }

    string getArtist() const {
        return artist;
    }

private:
    string title;
    string artist;
};

class Playlist : public Multimedia {
public:
    void addSong(const Song& song) {
        playlist.push_back(song);
        savePlaylistToFile();
        cout << "Song added to the playlist: " << song.getTitle() << " by " << song.getArtist() << endl;
    }

    void removeSong(int index) {
        if (index >= 0 && index < playlist.size()) {
            cout << "Removing song from the playlist: " << playlist[index].getTitle() << " by " << playlist[index].getArtist() << endl;
            playlist.erase(playlist.begin() + index);
            savePlaylistToFile();
        } else {
            cout << "Invalid index. No song removed." << endl;
        }
    }

    void clearPlaylist() {
        playlist.clear();
        savePlaylistToFile();
        cout << "Playlist cleared." << endl;
    }

    void shufflePlaylist() {
        if (playlist.size() > 1) {
            random_shuffle(playlist.begin(), playlist.end());
            savePlaylistToFile();
            cout << "Playlist shuffled." << endl;
        } else {
            cout << "Not enough songs to shuffle. Add more songs to the playlist." << endl;
        }
    }

    void displayPlaylist() const {
        if (playlist.empty()) {
            cout << "Playlist is empty." << endl;
        } else {
            cout << "Playlist:" << endl;
            for (size_t i = 0; i < playlist.size(); ++i) {
                cout << i + 1 << ". " << playlist[i].getTitle() << " by " << playlist[i].getArtist() << endl;
            }
        }
    }

    void loadPlaylistFromFile() {
        ifstream file("playlist.txt");
        if (file.is_open()) {
            playlist.clear();

            string title, artist;
            while (file >> title >> artist) {
                Song newSong(title, artist);
                playlist.push_back(newSong);
            }

            file.close();
        }
    }

    void savePlaylistToFile() const {
        ofstream file("playlist.txt");
        if (file.is_open()) {
            for (const auto& song : playlist) {
                file << song.getTitle() << " " << song.getArtist() << endl;
            }

            file.close();
        }
    }

    void displayFileContents() const {
        ifstream file("playlist.txt");
        if (file.is_open()) {
            string line;
            cout << "File Contents:" << endl;
            while (getline(file, line)) {
                cout << line << endl;
            }

            file.close();
        } else {
            cerr << "Unable to open 'playlist.txt'." << endl;
        }
    }

private:
    vector<Song> playlist;
};

int main() {
    Playlist myPlaylist;
    myPlaylist.loadPlaylistFromFile();

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add a song to the playlist\n";
        cout << "2. Display playlist\n";
        cout << "3. Remove a song from the playlist\n";
        cout << "4. Clear playlist\n";
        cout << "5. Shuffle playlist\n";
        cout << "6. Display file contents\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int numSongs;
                cout << "Enter the number of songs you want to add: ";
                cin >> numSongs;
                cin.ignore(); 

                for (int i = 0; i < numSongs; ++i) {
                    string title, artist;
                    cout << "Enter the title of the song: ";
                    getline(cin, title);
                    cout << "Enter the artist of the song: ";
                    getline(cin, artist);

                    Song newSong(title, artist);
                    myPlaylist.addSong(newSong);
                }
                break;
            }
            case 2:
                myPlaylist.displayPlaylist();
                break;
            case 3: {
                int index;
                cout << "Enter the index of the song to remove: ";
                cin >> index;
                myPlaylist.removeSong(index - 1); 
                break;
            }
            case 4:
                myPlaylist.clearPlaylist();
                break;
            case 5:
                myPlaylist.shufflePlaylist();
                break;
            case 6:
                myPlaylist.displayFileContents();
                break;
            case 0:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
