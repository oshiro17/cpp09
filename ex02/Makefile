# 実行ファイル名
NAME = PmergeMe

# ソースファイル一覧
SRC = main.cpp PmergeMe.cpp 

# フラグ
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I./include
DEBUGFLAGS = -g -ggdb -fsanitize=address -fno-omit-frame-pointer
ifneq ($(shell uname), Darwin)
    DEBUGFLAGS += -fstack-usage
endif

# ターゲット
.PHONY: all clean fclean re debug test_error test_normal test_large

all: $(NAME)

clean:
	-rm -f *.o *.d

fclean: clean
	-rm -f $(NAME)

re: fclean all

debug: CXXFLAGS += $(DEBUGFLAGS)

debug: fclean all

# 実行ファイル生成
$(NAME): $(SRC:.cpp=.o)
	c++ $(CXXFLAGS) $^ -o $@

# オブジェクトファイル生成
%.o: %.cpp
	c++ $(CXXFLAGS) -c $< -o $@

# エラーテスト
test_error: $(NAME)
	@echo "\n\033[31;1;3mIrregular tests\033[m"
	@echo "\033[41mTest case: No arguments\033[m"
	-./$(NAME) || true
	@echo "\033[43mTest case: Only one argument\033[m"
	-./$(NAME) 9 || true
	@echo "\033[41mTest case: Empty string in arguments\033[m"
	-./$(NAME) 9 3 5 "" || true
	@echo "\033[43mTest case: Non-integer argument\033[m"
	-./$(NAME) 9 3 5 abc || true
	@echo "\033[41mTest case: Negative number in arguments\033[m"
	-./$(NAME) 9 3 -5 8 || true
	@echo "\033[43mTest case: Overflow number in arguments\033[m"
	-./$(NAME) 9 3 2147483648 8 || true
	@echo "\033[41mTest case: Zero in arguments\033[m"
	-./$(NAME) 9 3 0 8 || true

# 正常系テスト
test_normal: $(NAME)
	@echo "\n\033[32;1;3mRegular tests\033[m"
	@echo "\033[42mTest case: Small sorted list\033[m"
	./$(NAME) 1 2 3 4 5
	@echo "\033[43mTest case: Small reverse sorted list\033[m"
	./$(NAME) 5 4 3 2 1
	@echo "\033[42mTest case: Random list\033[m"
	./$(NAME) 7 3 5 2 8 1
	@echo "\033[43mTest case: Duplicates\033[m"
	./$(NAME) 5 3 5 2 5 1

# 大規模データテスト
test_large: $(NAME)
	@echo "\n\033[34;1;3mLarge data tests\033[m"
	@echo "\033[44mTest case: 100 elements\033[m"
	seq 1 100 | shuf | tr "\n" " " | xargs ./$(NAME)
	@echo "\033[45mTest case: 1000 elements\033[m"
	seq 1 1000 | shuf | tr "\n" " " | xargs ./$(NAME)
	@echo "\033[44mTest case: 3000 elements\033[m"
	shuf -i 1-10000 -n 3000 | tr "\n" " " | xargs ./$(NAME)

# 全テスト実行
test: test_error test_normal test_large
