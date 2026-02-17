#include <iostream>
#include <string>
#include <cstdlib>  // 用于system命令
#include <filesystem> // C++17文件系统库

namespace fs = std::filesystem;
//“混流核心”，实现m4s音视频文件合流的功能

int main() {
    // 检查FFmpeg可用性
    if (system("ffmpeg -version") != 0) {
        std::cerr << "错误：未找到FFmpeg，请检查环境变量配置！\n";
        return EXIT_FAILURE;
    }

    // 输入文件路径（根据实际情况修改），加两道反斜杠，不然会被当成转义字符
    const fs::path videoPath = "D:\\XINAO_VIDEO_TEST\\video.m4s";
    const fs::path audioPath = "D:\\XINAO_VIDEO_TEST\\audio.m4s";
    const fs::path outputPath = "D:\\XINAO_VIDEO_TEST\\output_test.mp4";

    // 验证文件存在性
    if (!fs::exists(videoPath) || !fs::exists(audioPath)) {
        std::cerr << "错误：输入文件不存在！\n";
        return EXIT_FAILURE;
    }

    // 构建FFmpeg命令
    std::string command =
        "ffmpeg -y "    // -y 覆盖输出文件
        "-i \"" + videoPath.string() + "\" "
        "-i \"" + audioPath.string() + "\" "
        "-c copy "       // 直接复制流不重新编码
        "-map 0:v "     // 第一个输入的视频流
        "-map 1:a "     // 第二个输入的音频流
        "\"" + outputPath.string() + "\"";

    std::cout << "执行命令:\n" << command << "\n\n";

    // 执行命令
    int ret = system(command.c_str());

    if (ret == 0) {
        std::cout << "合并成功！输出文件: " << outputPath << "\n";
        return EXIT_SUCCESS;
    }
    else {
        std::cerr << "合并失败，错误码: " << ret << "\n";
        return EXIT_FAILURE;
    }
}

//感谢deepseek！感谢AI！！！实现了大学期间想实现却没有实现的功能！！！