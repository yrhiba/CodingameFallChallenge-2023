# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrhiba <yrhiba@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 16:59:00 by yrhiba            #+#    #+#              #
#    Updated: 2023/12/21 17:00:56 by yrhiba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SCRIPT : makeCodingameFile

FILES : build.cpp

$(SCRIPT) : build

build: $(FILES)
	g++ -std=c++17 $(FILES) -o $(SCRIPT)

run : $(SCRIPT)
	./$(SCRIPT)

clean:
	rm -rf ./prod/*
	rm -rf ./prod/.*
	rm -rf ./src/.*
	rm -rf ./src/includes/.*
	rm -rf ./src/classes/.*
	rm -rf ./src/solutions/.*

re : clean build

all : clean build run

.PHONY : run build clean re
