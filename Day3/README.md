# Advent of Code, Day 3: Rucksack Reorganization

Part 1 lead me into a false sense of security. A bit of comfort. 
When Part 2 hit, it totally threw me. I had an *idea* of what I wanted to do, but didn't really know the best way to go about it. 

Im shocked actually by the speed of execution presented here, considering how STL heavy this approach was. 
Lots is going on under the hood here, but on my machine in debug mode:  
![Time Measure in Debug mode](./d3-01-DebugBench.png)

and in Release mode:  
![Time measure in Release mode](./d3-02-ReleaseBench.png)

Not much to say really except the puzzle has a practicality problem to me.  

I'd almost like another crack at this one, just to see if I can play a bit of code golf and really reduce the verbosity on display here. I've seen some of the other solutions at this point, in languages other than Python, and noticed im using maybe 70% more lines than they are lmao 