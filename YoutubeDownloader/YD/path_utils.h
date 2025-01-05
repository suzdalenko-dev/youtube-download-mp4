#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include <string>

std::string get_executable_path();

void download_video(std::string yt_dlp_path, std::string youtube_url, std::string output_dir);


void merge_files(std::string exe_dir, std::string downloads_dir, std::string out_dir, std::string epoch_seconds);

#endif // PATH_UTILS_H
