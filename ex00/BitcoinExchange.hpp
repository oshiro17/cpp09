#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <deque>
#include <algorithm>
#include <cctype>
#include <cstdlib>

// 定数の定義
#define CSV_FILE "data.csv"             // CSVファイルの名前
#define FIRST_INPUT_LINE "date|value"   // 入力ファイルの1行目
#define FIRST_CSV_LINE "date,exchange_rate" // CSVファイルの1行目

class BitcoinExchange {
    public:
        // コンストラクタとデストラクタ
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();
        BitcoinExchange& operator=(const BitcoinExchange& other);


        static bool openable(const char *file);

        void loadCSV();
        void loadInput(const char *filename);
        void process();

    private:
        // static bool isWhitespace(unsigned char c); 
        bool isDateValid(const std::string& date);
        bool isRateValid(const std::string& value, double& number);
        std::map<std::string, double>::iterator closestDate(const std::string& date);
        void processEntry(const std::string& date, const std::string& value);
        std::map<std::string, double> _data;
        std::deque<std::pair<std::string, std::string> > _inputs;
};
bool isWhitespace(unsigned char c);

#endif
//挿入順: 10, 20, 30, 15, 25
// 赤黒木の構造:std::map
//         20 (黒)
//        /    \
//     10 (赤) 30 (黒)
//        \
//       15 (赤)
//          \
//          25 (赤)
//重複を許さない
// std::deque<std::pair<std::string, std::string> > _inputs;
//メモリ再確保のオーバーヘッドが少ない。
//両端での高速な挿入・削除操作。