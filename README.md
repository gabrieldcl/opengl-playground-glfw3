# OpenGL Playground GLFW3

I made this project to play a little with OpenGL and understand basic transformations like moving a figure, rotate and scaling. It is possible to control transformations with keyboard keys throw OpenGL events as shown bellow.


## Hotkeys

- ArrowUP: Move figure up
- ArrowDown: Move figure down

## Figure and Scaling
The figure was created using a scale of X = +-10 and Y = +-10. All figure points are passed throw a formula that re-scales all of them to the OpenGL patter, which is X = +-1 and Y = +-1.

### Scale formula
	scaledPoint.x  = ((2  / (limits.maxX  -  limits.minX)) * (point.x  -  limits.minX)) -  1;
	scaledPoint.y  = ((2  / (limits.maxY  -  limits.minY)) * (point.y  -  limits.minY)) -  1;

### Figure
![DiceFaces figure](https://media.discordapp.net/attachments/328735032007065621/770095315688095784/Untitled_Diagram.png)
