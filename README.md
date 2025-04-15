# ToDo
Simple to-do list app with tasks per directory and global

![App screenshot](https://nasiadka.pl/project/todo-cpp/ToDo.png)

# Building and installation
`$ make`  
`# make install`

# Usage

## Listing
All tasks (global and current directory):  
` todo ` or ` todo -l`  

Tasks from current directory:  
` todo -lc `  

## Creating
Global task:  
` todo -c Task description`  

Task in current directory:  
` todo -cc Task description`

## Removing
Global task:  
` todo -r {Task number (or multiple numbers) from list}`

Task in current directory:  
` todo -rc {Task number (or multiple numbers) from list}`

## Help
` todo -h ` or ` todo --help `
