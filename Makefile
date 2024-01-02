# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrhiba <yrhiba@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 16:59:00 by yrhiba            #+#    #+#              #
#    Updated: 2024/01/01 12:32:46 by yrhiba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SCRIPT = makeCodingameFile

FILES = build.cpp

buildClean:
	make run clean

$(SCRIPT) : $(FILES)
	@make build

build :
	g++ -std=c++17 $(FILES) -o $(SCRIPT)

run : $(SCRIPT)
	@mkdir -p prod
	./$(SCRIPT)
	cat ./prod/code.cpp | pbcopy

clean:
	@rm -rf prod $(SCRIPT)

re : clean build

all : clean build run

.PHONY : run build clean re
