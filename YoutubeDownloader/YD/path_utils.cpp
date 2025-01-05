#include "path_utils.h" // Include the corresponding header file
#include <windows.h>    // For Windows API functions
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <stdexcept>
namespace fs = std::filesystem;

std::string get_executable_path() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string exe_path = buffer;
    return exe_path.substr(0, exe_path.find_last_of("\\/"));
}


void download_video(std::string yt_dlp_path, std::string youtube_url, std::string output_dir) {
    try {
        // Construct the command
        std::string command = yt_dlp_path;
        command += " -f bestvideo[ext=mp4]+bestaudio[ext=m4a]/mp4";
        command += " -o \"" + output_dir + "/%(epoch)s.%(ext)s\"";
        command += " -k \"" + youtube_url + "\"";

        // Log the action
        std::cout << "Downloading from: " << youtube_url << "\n";

        // Execute the command
        int result = std::system(command.c_str());
        if (result != 0) {
            throw std::runtime_error("Error downloading video. Return code: " + std::to_string(result));
        }

        std::cout << "Download complete!\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Press Enter to exit...\n";
        std::cin.get();
    }
}


void merge_files(std::string exe_dir, std::string downloads_dir, std::string out_dir, std::string epoch_seconds) {

    try {
    // Locate the most recent video and audio files
    std::vector<std::filesystem::path> video_files;
   
    for (const auto& entry : fs::directory_iterator(downloads_dir)) {
        if (entry.path().extension() == ".mp4") {
            video_files.push_back(entry.path());
        }
    }

    if (video_files.empty()) {
        throw std::runtime_error("No video or audio files found in the directory.");
    } else {
        std::cout << "Video and Audio files exists !!! \n";
    }


    // Get the first video and audio files (based on most recent modification time)
    auto most_recent_video = *std::max_element(video_files.begin(), video_files.end(),
        [](const fs::path& a, const fs::path& b) {
            return fs::last_write_time(a) > fs::last_write_time(b);
        });

    // Prepare output path
    fs::create_directories(out_dir); // Ensure the output directory exists
    std::string output_path = out_dir + "\\" + epoch_seconds + "_file.mp4";

    // Build ffmpeg command
  
    std::cout << "Video Path: " << most_recent_video.string() << "\n";
    fs::copy(most_recent_video.string(), output_path, fs::copy_options::overwrite_existing);
  
    /*
    std::string ffmpeg_path = exe_dir + "\\ffmpeg.exe";
    std::string command = "" + ffmpeg_path + "";
    command += " -i \"" + most_recent_video.string() + "\"";
    command += " -i \"" + most_recent_audio.string() + "\"";
    command += " -c:v libx264 -c:a aac -strict experimental";
    command += " \"" + output_path + "\"";
    int result = std::system(command.c_str());
    */


    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "An unknown error occurred.\n";
    }
}