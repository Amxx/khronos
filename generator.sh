#!/bin/bash


function setup
{
	# Define here the installation path for your platform
	printf "┌──────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
	printf "│ %-100s │\n" "Platform identification"
	printf "└──────────────────────────────────────────────────────────────────────────────────────────────────────┘\n"

	case "$HOSTNAME" in
		Archteryx)
			install_path="$PWD/install"
			options="-DCMAKE_VERBOSE_MAKEFILE=ON"
			;;

		*) printf "Your platform is not defined in $0.\n"
			install_path="$PWD/install"
			options="-DCMAKE_VERBOSE_MAKEFILE=OFF"
			;;
	esac

	# Summary
	printf "┌──────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
	printf "│ %-100s │\n" "Configuration summary"
	printf "├──────────────────────────────────────────────────────────────────────────────────────────────────────┤\n"
	printf "│ %-100s │\n" "Options :"
	for option in $options
	do
		printf "│     %-96s │\n" $option
	done
	printf "└──────────────────────────────────────────────────────────────────────────────────────────────────────┘\n"

}

function build
{
	setup \
		|| exit 1

	mkdir -p build \
		|| exit 1

	cd build \
		|| exit 1

	cmake -DCMAKE_INSTALL_PREFIX:PATH=$install_path \
				$options																	\
				.. 																				\
		|| exit 1

	make \
		|| exit 1

	make install \
		|| exit 1
}

function remove
{
	rm -rfv $1
}

function help
{
	printf "┌──────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
	printf "│ %-100s │\n" "Project generator"
	printf "├──────────────────────────────────────────────────────────────────────────────────────────────────────┤\n"
	printf "│ %-100s │\n" "Options are:"
	printf "│ %-100s │\n" " -h, --help         show brief help"
	printf "│ %-100s │\n" " -b, --build        build the project"
	printf "│ %-100s │\n" " -c, --clean        clean the project"
	printf "└──────────────────────────────────────────────────────────────────────────────────────────────────────┘\n"
}

############################################
#                   MAIN                   #
############################################

if test $# -gt 0; then
	case "$1" in
		-h|--help)
			help
			exit 0
			;;

		-b|--build)
			build
			exit 0
			;;

		-c|--clean)
			remove "build"
			exit 0
			;;

		*)
			printf "invalid option -- '$1'\n"
			help
			exit 0
			;;
	esac
fi

help
