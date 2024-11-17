# 実行ファイル名
NAME = btc

# ソースファイル一覧
SRC = main.cpp BitcoinExchange.cpp

# フラグ
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I./include
DEBUGFLAGS = -g -ggdb -fsanitize=address -fno-omit-frame-pointer
ifneq ($(shell uname), Darwin)
    DEBUGFLAGS += -fstack-usage
endif

# ターゲット
.PHONY: all clean fclean re debug

all: $(NAME)

clean:
	-rm -f *.o *.d

fclean: clean
	-rm -f $(NAME)
	-rm -f *_shrubbery 

re: fclean all

debug: CXXFLAGS += $(DEBUGFLAGS)

debug: fclean all

# 実行ファイル生成
$(NAME): $(SRC:.cpp=.o)
	c++ $(CXXFLAGS) $^ -o $@

# オブジェクトファイル生成
%.o: %.cpp
	c++ $(CXXFLAGS) -c $< -o $@