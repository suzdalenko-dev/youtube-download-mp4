#include <iostream>
#include "path_utils.h"
#include <filesystem>


int main()
{
    std::cout << "Youtube Downloader Suzdalenko Alexey 2024-12-31 \n";

    // get url for yt-dlp.exe
    std::string exe_dir = get_executable_path();
    std::string yt_dlp_path = exe_dir + "\\yt-dlp.exe";

    while (true) {

        // create works folder
        std::time_t current_time = std::time(nullptr); // Get time in seconds since epoch
        std::string epoch_seconds = std::to_string(current_time);
        std::string downloads_dir = exe_dir + "\\downloads\\" + epoch_seconds;
        std::string out_dir = exe_dir + "\\out";
        std::filesystem::create_directories(downloads_dir);
        std::filesystem::create_directories(out_dir);


        // first posible error
        if (!std::filesystem::exists(yt_dlp_path)) {
            std::cerr << "Error: yt-dlp.exe not found at: " << yt_dlp_path << "\n";
            return 1; // Exit the program with an error code
        }


		std::cout << "Enter short YouTube url: ";
		std::string youtubeUrl = "";
		std::cin >> youtubeUrl;
		if (youtubeUrl == "") {
			youtubeUrl = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
		}
		download_video(yt_dlp_path, youtubeUrl, downloads_dir);
		merge_files(exe_dir, downloads_dir, out_dir, epoch_seconds);
		std::cout << "\n Complete.. \n\n";
        std::string x = "";
		x = std::cin.get();

	}

}