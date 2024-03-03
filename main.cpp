#include <string>
#include <iostream>
#include <fstream> {

void file_grep(std::string filename, std::string needle, bool print_row, bool print_total)
{
    std::ifstream file(filename);

    std::string line{};

    if (!file.is_open()) {
        std::cout << "Could not open file \"" << filename << "\"";
        return;
    }

    int total = 0;
    int linenum = 0;

    while (getline(file, line)) {
        linenum++;
        if (line.find(needle) != std::string::npos) {
            total++;
            if (print_row) {
                std::cout << linenum << ":    ";
            }
            std::cout << line << "\n";
        }
    }

    file.close();
 
    if (print_total) {
        std::cout << "\nOccurrences of lines containing \"" << needle << "\": " << total << "\n";
    }

    return;
}

void string_grep()
{
    std::cout << "Give me a string to search from: ";

    std::string haystack;
    std::getline(std::cin, haystack);

    std::cout << "Give search string: ";

    std::string needle;
    std::getline(std::cin, needle);

    size_t pos = haystack.find(needle);

    if (pos != std::string::npos) {
        std::cout << "\"" << needle << "\" found in \"" << haystack << "\" in position " << pos << "\n";
    }
    else {
        std::cout << "\"" << needle << "\" NOT found in \"" << haystack << "\"\n";
    }
}

void print_help()
{
    std::cout << "./mygrep [-o<o|l>] <needle> <filename>\n";
    std::cout << "or ./mygrep\n";
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        string_grep();
    }
    else if (argc == 2 || argc > 4) {
        print_help();

        return 0;
    }
    else if (argc == 3) {
        file_grep(argv[2], argv[1], false, false);
    }
    else if (argc == 4) {
        std::string switches = argv[1];

        bool row = false;
        bool total = false;

        //std::cout << argc << " " << argv[1] << " " << argv[2] << " " << argv[3] << "\n";

        if (switches.compare(0, 2, "-o") == 0 && switches.size() >= 3) {
            for (int i = 2; i < switches.size(); i++) {
                switch (switches[i]) {
                    case 'o':
                        total = true;
                        break;
                    case 'l':
                        row = true;
                        break;
                    default:
                        print_help();
                        return 0;
                        break;
                }
            }
        }
        else {
            print_help();
            return 0;
        }

        //std::cout << "row: " << row << " total: " << total << " size: " << switches.size() << "\n";

        file_grep(argv[3], argv[2], row, total);
    }

    return 0;
}
 