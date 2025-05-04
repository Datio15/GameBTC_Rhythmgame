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
},
	{
		"You Say Run",
		"assets/music/music5.mp3",
		"assets/chart/chart5.txt",
		"assets/image/Deku.jpg"
},
	{
		"IRWTSYH",
		"assets/music/music6.mp3",
		"assets/chart/chart6.txt",
		"assets/image/Lucy.jpg"
}

};

#endif
