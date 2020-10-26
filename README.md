# OpenGL Playground GLFW3

The purpose of this project is to play around with OpenGL glfw3 library in order to understand basic transformations, such as moving, rotating or scaling a figure. You can control each one of them by using OpenGL hotkey events as shown below.


## Hotkeys

- ArrowUP: Move figure up
- ArrowDown: Move figure down
- ArrowLeft: Move figure left
- ArrowRight: Move figure right
- Z: Zoom figure by 20% throw center=(0,0) which is the Dice Face with one dot
- X: Zoom figure by 50% throw center=(-2,0) which is the Dice Face with five dots
- C: Rotate the figure by 45º degrees
- S: Separate all dice faces connected to the dice face with one dot
- R: Reset the figure

## Figure and Scaling
The figure was created using a scale of X = +-10 and Y = +-10. All figure points were passed through a formula that re-scales all of them to the OpenGL patter, which is X = +-1 and Y = +-1.

### Scale formula
	scaledPoint.x  = ((2  / (limits.maxX  -  limits.minX)) * (point.x  -  limits.minX)) -  1;
	scaledPoint.y  = ((2  / (limits.maxY  -  limits.minY)) * (point.y  -  limits.minY)) -  1;

### Figure
![enter image description here](https://media.discordapp.net/attachments/328735032007065621/770095315688095784/Untitled_Diagram.png)
