#include "BitcoinExchange.hpp"
// static bool hasValidExtension(const std::string& filename, const std::string& validExtension) {
//     std::size_t pos = filename.rfind('.');
//     if (pos == std::string::npos) {
//         std::cerr << "Error: No extension found in file name: " << filename << std::endl;
//         return false; 
//     }
//     std::string extension = filename.substr(pos + 1);
//     if (extension != validExtension) {
//         std::cerr << "Error: Invalid file extension '" << extension
//                   << "' for file: " << filename << ". Expected: '" << validExtension << "'" << std::endl;
//         return false; 
//     }
//     return true;
// }
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Error: cannot open file."<< std::endl;
        return 1;
    }
    if (!BitcoinExchange::openable(argv[1])) {
        std::cout << "Error: cannot open file "<< argv[1] << std::endl;
        return 1;
    }
    //     if (!hasValidExtension(argv[1], "scv")) {
    //     std::cout << "Error: invalid file extension " << argv[1] << std::endl;
    //     return 1;
    // }
    if (!BitcoinExchange::openable(CSV_FILE)) {
        std::cout << "Error: cannot open file "<< CSV_FILE << std::endl;
        return 1;
    }

    BitcoinExchange btcExchange;

    btcExchange.loadCSV();
    btcExchange.loadInput(argv[1]);

    // 入力データに基づいてビットコインの交換レートを出力
    btcExchange.process();

    return 0;
}
