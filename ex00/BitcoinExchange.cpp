#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _data(), _inputs() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _data(other._data), _inputs(other._inputs) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        this->_data = other._data;
        this->_inputs = other._inputs;
    }
    return *this;
}

bool BitcoinExchange::openable(const char *file) {
    std::ifstream input_file(file);
    if (!input_file.is_open()) 
        return false;
    return true;
}

bool BitcoinExchange::isDateValid(const std::string& date) {
    if (date.empty() || date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    if (!std::isdigit(date[0]))
        return false;
    if (!std::isdigit(date[1]))
        return false;
    if (!std::isdigit(date[2]))
        return false;
    if (!std::isdigit(date[3]))
        return false;
    // if (!std::isdigit(date[5]))
    //     return false;
    // if (!std::isdigit(date[6]))
    //     return false;
    // if (!std::isdigit(date[8]))
    //     return false;
    // if (!std::isdigit(date[9]))
    //     return false;

    int month, day;
    int year;
    // try {
        // month = std::stoi(date.substr(5, 2));
        // day = std::stoi(date.substr(8, 2));
        // year = std::stoi(date.substr(0, 4));
    // } catch (...) {
    //     return false;
    // }
    std::stringstream(date.substr(5,2)) >> month;
	std::stringstream(date.substr(8,2)) >> day;
	std::stringstream(date.substr(0,4)) >> year;
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];

    // try {
    if (month == 2 &&( (year % 4 == 0 && year % 100 != 0 )|| year % 400 == 0)) 
        maxDay = 29;

        // }
    // } catch (...) {
        // return false; 
    // }
    
    // std::cout<<"73"<<std::endl;
    if (month < 1 || month > 12 || day < 1 || day > maxDay) {
        return false;
    }
    return true;
}

// レートの妥当性をチェック
bool BitcoinExchange::isRateValid(const std::string& value, double& number) {
    std::stringstream ss(value);
    ss >> number;
    if (ss.fail() || number < 0 || number > 1000) {
        std::cout << "Error: not a positive number. => " << value << std::endl;
        return false;
    }
    return true;
}

bool isWhitespace(unsigned char c) {
    return std::isspace(c);
}
void BitcoinExchange::loadCSV() {
    std::ifstream csv_file(CSV_FILE);
    if (!csv_file.is_open()) {
        std::cerr << "Error: Could not open file => " << CSV_FILE << std::endl;
        std::exit(1);
    }

    std::string line;
    bool hasContent = false; // ファイルが空かどうかを確認するフラグ

    while (std::getline(csv_file, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), isWhitespace), line.end());

        if (line.empty()) {
            continue;
        }
        hasContent = true;

        std::size_t pos = line.find(',');
        if (pos != std::string::npos) {
            std::string date = line.substr(0, pos);
            std::string rate = line.substr(pos + 1);

            if (date.empty()) {
                std::cerr << "Error: Date is missing in line => " << line << std::endl;
                std::exit(1);
            }
            if (rate.empty()) {
                std::cerr << "Error: Rate is missing in line => " << line << std::endl;
                std::exit(1);
            }

            double value;
            std::istringstream iss(rate);
            iss >> value;

            if (line != FIRST_CSV_LINE && (iss.fail() || !isDateValid(date) || _data.find(date) != _data.end())) {
                std::cerr << "Error: Invalid csv line => " << line << std::endl;
                std::exit(1);
            } else {
                _data[date] = value;
            }
        } else {
            std::cerr << "Error: Invalid line format, missing ',' => " << line << std::endl;
            std::exit(1);
        }
    }

    if (!hasContent) { // ファイル全体が空、または空行や空白行のみの場合
        std::cerr << "Error: CSV file is empty or contains only blank/invalid lines => " << CSV_FILE << std::endl;
        std::exit(1);
    }
}

// void BitcoinExchange::loadCSV() {
//     std::ifstream csv_file(CSV_FILE);
//     std::string line;

//     while (std::getline(csv_file, line)) {
//         line.erase(std::remove_if(line.begin(), line.end(), isWhitespace), line.end());
//         // line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
//         // line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
//         //    std::cout << "Processed line: " << line << std::endl;
//         std::size_t pos = line.find(',');
//         if (pos != std::string::npos) {
//             std::string date = line.substr(0, pos);
//             std::string rate = line.substr(pos + 1);
//         //    std::cout << "Data " << date << std::endl;
//         //    std::cout << "rate " << rate << std::endl;
//             if (date.empty()) {
//                 std::cerr << "Error: Date is missing in line => " << line << std::endl;
//                 std::exit(1);
//             }
//             if (rate.empty()) {
//                 std::cerr << "Error: Rate is missing in line => " << line << std::endl;
//                 std::exit(1);
//             }
//             double value;
//             std::istringstream iss(rate);
//             iss >> value;
//             // キーが存在していない時_data.find(date) の帰り値は_data.end())
//             if (line != FIRST_CSV_LINE && (iss.fail() || !isDateValid(date) || _data.find(date) != _data.end())) {
//                 std::cout << "Invalid csv line => " << line << std::endl;
// 		        std::exit(1);
//             } else {
//                 _data[date] = value;
//             }
//         } else {
//             std::cerr << "Error: Date is missing in line => " << line << std::endl;
//             std::exit(1);
//         }
//     }
// }

void BitcoinExchange::loadInput(const char *filename) {
    std::ifstream ifile(filename);
    std::string line;

    while (std::getline(ifile, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), isWhitespace), line.end());
		if (line == FIRST_INPUT_LINE) {
			continue;
		}
        std::size_t pos = line.find('|');
        std::string date = (pos != std::string::npos) ? line.substr(0, pos) : line;
        std::string rate = (pos != std::string::npos) ? line.substr(pos + 1) : "";

        _inputs.push_back(std::make_pair(date, rate));
        // std::map では、同じキーを持つデータを格納できん
    }
    ifile.close();
}

std::map<std::string, double>::iterator BitcoinExchange::closestDate(const std::string& date) {
    std::map<std::string, double>::iterator near = _data.end();

    for (std::map<std::string, double>::iterator it = _data.begin(); it != _data.end(); ++it) {
        if (it->first > date) {
            break;
        }
        near = it;
    }

    if (near == _data.end()) {
        return _data.begin();
    }
    if ( near->first > date) {
        return _data.end();
    }
    return near;
}

// void BitcoinExchange::processEntry(const std::string& date, const std::string& rate) {
//     if (!isDateValid(date)) {
//         std::cout << "Invalid date format " << date << std::endl;
//         return;
//     }

//     double number;
//     if (!isRateValid(rate, number)) {
//         return;
//     }

//     std::map<std::string, double>::iterator it = closestDate(date);
//             std::cout  << number << std::endl;
//                      std::cout << it->second << std::endl;
//     if (it != _data.end()) {
//         std::cout << date << " => " << rate << " = " << number * it->second << std::endl;
//     }
// }
void BitcoinExchange::processEntry(const std::string& date, const std::string& rate) {
    if (!isDateValid(date)) {
        std::cout << "Invalid date format " << date << std::endl;
        return;
    }

    double number;
    if (!isRateValid(rate, number)) {
        return;
    }

    std::map<std::string, double>::iterator it = closestDate(date);
    if (it != _data.end()) {
        double conversionRate = it->second;
        if (number > 0 && conversionRate > 0) {
            if (number > std::numeric_limits<double>::max() / conversionRate) {
                std::cout << "Overflow detected: " << number << " * " << conversionRate << " exceeds the limit." << std::endl;
                return;
            }
        }

        std::cout << date << " => " << rate << " = " << number * conversionRate << std::endl;
    }
}
void BitcoinExchange::process() {
    typedef std::pair<std::string, std::string> InputPair;
    typedef std::deque<InputPair>::const_iterator InputIterator;

    for (InputIterator it = _inputs.begin(); it != _inputs.end(); ++it) {
        processEntry(it->first, it->second);
    }
}
