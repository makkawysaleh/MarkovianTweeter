# Markovian Tweeter
Generates text using markov chains for a given twitter user.

### Dependencies
The only required library is `libcurl`. Rest is included with the source.

### Building
* Clone the project.
* Make a folder called `build` inside the source directory
* `cd` into the build folder
* Make a text file named `credentials.txt` inside the build folder
* In the first line of the file place your 
consumer key and in the second line place your consumer secret
* type `cmake ..`
* type `make`

### Running the program
From inside the build folder run the program by doing `./markotweet`
