#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>
#include <utility>

class Song {
    friend std::ostream &operator<<(std::ostream &os, const Song &s);
    std::string name;
    std::string artist;
    int rating;
public:
    Song() = default;
    Song(std::string name, std::string artist, int rating)
            : name{std::move(name)}, artist{std::move(artist)}, rating{rating} {}
    std::string get_name() const {
        return name;
    }
    std::string get_artist() const {
        return artist;
    }
    int get_rating() const {
        return rating;
    }

    bool operator<(const Song &rhs) const  {
        return this->name < rhs.name;
    }

    bool operator==(const Song &rhs) const  {
        return this->name == rhs.name;
    }
};

std::ostream &operator<<(std::ostream &os, const Song &s) {
    os << std::setw(20) << std::left << s.name
       << std::setw(30) << std::left << s.artist
       << std::setw(2) << std::left << s.rating;
    return os;
}

// func prototype
void display_menu();
void play_current_song(const Song &song);
void display_playlist(const std::list<Song> &playlist, const Song &current_song);

int main() {

    std::list<Song> playlist{
            {"God's Plan",        "Drake",                     5},
            {"Never Be The Same", "Camila Cabello",            5},
            {"Pray For Me",       "The Weekend and K. Lamar",  4},
            {"The Middle",        "Zedd, Maren Morris & Grey", 5},
            {"Wait",              "Maroone 5",                 4},
            {"Whatever It Takes", "Imagine Dragons",           3}
    };

    auto current_song = playlist.begin();
    display_playlist(playlist, *current_song);
    char user_choice {};
    do {
        display_menu();
        std::cin >> user_choice;
        user_choice = std::toupper(user_choice);
        switch (user_choice) {
            case 'F':
                std::cout << "Playing first song" << std::endl;
                current_song = playlist.begin();
                play_current_song(*current_song);
                break;
            case 'L':
                std::cout << "Playing last song" << std::endl;
                current_song = playlist.end();
                current_song--;
                play_current_song(*current_song);
                break;
            case 'N':
                std::cout << "Playing next song" << std::endl;
                current_song++;
                if (current_song == playlist.end()) {
                    current_song = playlist.begin();
                }
                play_current_song(*current_song);
                break;
            case 'P':
                std::cout << "Playing previous song" << std::endl;
                if (current_song == playlist.begin()) {
                    current_song = playlist.end();
                }
                current_song--;
                play_current_song(*current_song);
                break;
            case 'A': {
                std::string name, artist;
                int rating;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter song name:";
                std::getline(std::cin, name);
                std::cout << "Enter song artist:";
                std::getline(std::cin, artist);
                std::cout << "Enter your rating for this song:";
                std::cin >> rating;
                playlist.emplace_back(Song{name, artist, rating});
                current_song = playlist.begin();
                play_current_song(*current_song);
                break;
            }
            case 'D':
                display_playlist(playlist, *current_song);
                break;
            case 'Q':
                std::cout << "Goodbye" << std::endl;
                std::exit(0);
            default:
                std::cout << "Unknown selection, please try again" << std::endl;
        }
    } while (user_choice != 'Q');

    std::cout << "Thanks for listening!" << std::endl;
    return 0;
}


void display_menu() {
    std::cout << "\nF - Play First Song" << std::endl;
    std::cout << "L - Play Last song" << std::endl;
    std::cout << "N - Play Next song" << std::endl;
    std::cout << "P - Play Previous song" << std::endl;
    std::cout << "A - Add and play a new Song at current location" << std::endl;
    std::cout << "D - Display the current playlist" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter a selection (Q to quit):";
}

void play_current_song(const Song &song) {
    // This function should display
    // Playing: followed by the song that is playing
    std::cout << "Playing: " << std::endl
              << song << std::endl;
}

void display_playlist(const std::list<Song> &playlist, const Song &current_song) {
    // This function should display the current playlist
    // and then the current song playing.
    for (const auto &s: playlist) {
        std::cout << s << std::endl;
    }
    std::cout << "Current song: " << std::endl
              << current_song << std::endl;
}