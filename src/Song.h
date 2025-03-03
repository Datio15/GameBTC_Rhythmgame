#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>

struct Song {
	std::string name;
	std::string songpath;
	std::string chartpath;
	std::string imagepath;
};
static std::vector<Song> songList = {
	{
		"Sayonara Hatsukoi (feat. Megurine Luka)",
		"assets/music/music1.mp3",
		"assets/chart/chart1.txt",
		"assets/image/Sayonara.png"
},
	{
		"Bad Apple",
		"assets/music/music2.mp3",
		"assets/chart/chart2.txt",
		"assets/image/Bad Apple.jpg"

},
	{
		"Rolling Girl",
		"assets/music/music3.mp3",
		"assets/chart/chart3.txt",
		"assets/image/Miku.jpg"
},
	{
		"Inertia",
		"assets/music/music4.mp3",
		"assets/chart/chart4.txt",
		"assets/image/XHero.jpg"
	}

};

#endif