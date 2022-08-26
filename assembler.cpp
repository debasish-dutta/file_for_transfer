#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <cstring>
#include <bitset>


std::unordered_map <std::string, std::uint16_t> symbol_map { 
    {"R0", 0u},
    {"R1", 1u},
    {"R2", 2u},
    {"R3", 3u},
    {"R4", 4u},
    {"R5", 5u},
    {"R6", 6u},
    {"R7", 7u},
    {"R8", 8u},
    {"R9", 9u},
    {"R10", 10u},
    {"R11", 11u},
    {"R12", 12u},
    {"R13", 13u},
    {"R14", 14u},
    {"R15", 15u},
    {"SCREEN", 16384u},
    {"KBD", 24576u},
    {"SP", 0u},
    {"LCL", 1u},
    {"ARG", 2u},
    {"THIS", 3u},
    {"THAT", 4u}
};


const std::unordered_map<std::string, std::bitset<7> > comp_map {
    {"0", 0b0101010},
    {"1", 0b0111111},
    {"-1", 0b0111010},
    {"D", 0b0001100},
    {"A", 0b0110000},
    {"M", 0b1110000},
    {"!D", 0b0001101},
    {"!A", 0b0110001},
    {"!M", 0b1110001},
    {"-D", 0b0001111},
    {"-A", 0b0110011},
    {"-M", 0b1110011},
    {"D+1", 0b0011111},
    {"A+1", 0b0110111},
    {"M+1", 0b1110111},
    {"D-1", 0b0001110},
    {"A-1", 0b0110010},
    {"D+A", 0b0000010},
    {"D-A", 0b0010011},
    {"A-D", 0b0100111},
    {"D&A", 0b0000000},
    {"D|A", 0b0010101},
    {"M-1", 0b1110010},
    {"D+M", 0b1000010},
    {"D_M", 0b1010011},
    {"M-D", 0b1100111},
    {"D&M", 0b1000000},
    {"D|M", 0b1010101}
};


const std::unordered_map<std::string, std::bitset<3> > dest_map {
    {"M", 0b001},  // RAM[A]
    {"D", 0b010},  // D reg
    {"MD", 0b011}, // RAM[A] and D reg
    {"A", 0b100},  // A reg
    {"AM", 0b101}, // A reg and RAM[A]
    {"AD", 0b110}, // A reg and D reg
    {"AMD", 0b111} // A reg, RAM[A] and D reg
};


const std::unordered_map<std::string, std::bitset<3> > jump_map {
    {"JGT", 0b001}, //JMP is > 0
    {"JEQ", 0b010}, //JMP is = 0 
    {"JGE", 0b011}, //JMP is >= 0
    {"JLT", 0b100}, //JMP is < 0
    {"JNE", 0b101}, //JMP is != 0
    {"JLE", 0b110}, //JMP is =< 0
    {"JMP", 0b111}  //JMP
};


std::string clean_lines(std::string lines){
    lines = std::regex_replace(lines, std::regex("(\\/\\/.*)|[^\\S\\r\\n]"), "");
    if(regex_search(lines, std::regex("."))) return lines;
    else return "";
}

void parser(std::string line){
    if(line.front() != *"\\n") std::cout << "C-inst" << line;
}

void transl(std::string line) {
    if(line.front() == *"@") std::cout << "A-inst" << line;
}

void add_sym(std::string line) {
    if(line.front() == *"(") std::cout << "label" << line;
}


int main() {
    
    std::string file_name = "add/Add.asm";

    std::ifstream in_file;
    std::ofstream out_file;
    std::string line, out_line;

    // First Pass
    in_file.open(file_name);
    while(std::getline(in_file, line)) {
        std::string clean_line = clean_lines(line);

        if(clean_line.front() == *"(") {
            add_sym(clean_line);
        }
    }
    in_file.close();

    //Second Pass
    in_file.open(file_name);

    while (std::getline(in_file, line)) {
        std::string clean_line = clean_lines(line);

        if(clean_line.front() == *"@") {
            transl(clean_line);
        }
        else if(clean_line.front() != *"" && clean_line.front() != *"(") {
            parser(clean_line);
        }
    }
    
    in_file.close();



    return 0;
}