Individual Programming Exercise num 1
Dependencies visible in makefile.

Useful files:

list.c [list.h]
operations.c [operations.h]
tree.c [tree.h]
parser.c [parser.h]
main.c

Usage:

note that only main.c is executable
Commands:

addUser [adds user to the tree (both id's must be >0 && <65536, parent's id can be 0 tho)
delUser [deletes user in the tree]
addMovie [adds a movieRating to the user's preferences]
delMovie [deletes a movieRAting from the user's preferences]
marathon [returns the k best films from the preferences of userID and recursively, from the preferences of its children]
