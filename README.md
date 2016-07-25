# STREAMLINE
Destination: To Generate Streamlines Of The Given Vector Data

In this program, the seeding points were randomly generated within the specific area, and thus streamlines were traced out from each seed using an adaptive Runge-Kutta fourth order (RK45) integrator in both forward and backward direction. 

When generating the lines, we do not terminate the computation even when it is getting really close to another streamline. Thus, short line segments could be avoided, because short streamlines may not be classified into the same group with nearby long streamlines.

sample picture:
![image](https://github.com/zgzzbws/streamline/blob/master/screenshots/streamline.png)
