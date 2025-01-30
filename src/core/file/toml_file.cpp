#include "toml_file.h"
#include "text.h"
#include <string>
#include <iostream>

std::string toml::searchString(std::string file_serch, const char* path)
{
    std::string file_code = text::read(path);
    //std::string file_serch = "HE";

    const std::string end = "\n";

    int search_index_element = 0;
    int start_index_string = 0;

    bool Continue = 0;
    bool write = false;

    std::string result = "";

    for (int i = 0; i < file_code.size(); i++)
    {

        if (write == true)
        {
            for (int j = start_index_string; j < file_code.size(); j++)
            {
                if (file_code[j] == end[0])
                {
                    std::cout << std::endl;
                    break;
                }
                result += file_code[j];
            }
            break;
        }

        if (file_code[i] == file_serch[search_index_element])
        {
            
            start_index_string = i;

            for (int j = 0; j < file_serch.size(); j++)
            {
                if (file_code[i + j] == file_serch[j])
                {
                    if (j == file_serch.size() - 1) write = true;
                }
                else
                {
                    Continue = true;
                    break;
                }
            }

            if (Continue)
            {
                Continue = false;
                continue;
            }
            //std::cout << Continue << std::endl;
            //break;
        }
    }

    //std::cout << result << std::endl;
    return result;
}

std::string toml::getValue(std::string file_serch, const char* path)
{

}


// WIDTH
// WHITE
// HEIGHT
// HEALTH