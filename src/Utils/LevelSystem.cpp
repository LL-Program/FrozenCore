#include "LevelSystem.hpp"

std::vector<EnvItem> loadLevelData(const std::string &filename)
{
    std::vector<EnvItem> envItems;
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return envItems;
    }

    std::string line;
    std::getline(file, line);
    file.close();

    std::vector<std::string> tileStrings;
    std::string delimiter = "|";
    size_t pos = 0;
    while ((pos = line.find(delimiter)) != std::string::npos)
    {
        tileStrings.push_back(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());
    }
    tileStrings.push_back(line);

    std::regex tileRegex(R"((-?\d+)X(-?\d+)Y(\d+)SH(\d+)I(\d+)B)");
    
    for (const std::string &tileStr : tileStrings)
    {
        if (tileStr.empty())
            continue;

        std::smatch match;
        std::string trimmedTileStr = tileStr;
        trimmedTileStr.erase(trimmedTileStr.begin(), std::find_if(trimmedTileStr.begin(), trimmedTileStr.end(), [](unsigned char ch)
                                                                  { return !std::isspace(ch); }));
        trimmedTileStr.erase(std::find_if(trimmedTileStr.rbegin(), trimmedTileStr.rend(), [](unsigned char ch)
                                          { return !std::isspace(ch); })
                                 .base(),
                             trimmedTileStr.end());

        if (std::regex_match(trimmedTileStr, match, tileRegex))
        {

            EnvItem envItem;
            envItem.rect.x = std::stoi(match[1]) * 48;
            envItem.rect.y = std::stoi(match[2]) * 48;
            envItem.rect.width = 48;
            envItem.rect.height = 48;
            envItem.spriteSheet = std::stoi(match[3]);
            envItem.spriteIndex = std::stoi(match[4]);
            envItem.blocking = std::stoi(match[5]) != 0;

            envItems.push_back(envItem);
        }
        else
        {
        }
    }

    return envItems;
}
