# ToDo
Simple to-do list app with tasks per directory and global

![Game screenshot](https://maciej.ml/projects/ToDo/ToDo.png)

# Building and installation
`$ make`  
`$ sudo make install`

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
` todo -r {Task number from list}`

Task in current directory:  
` todo -rc {Task number from list}`

## Help
` todo -h ` or ` todo --help `