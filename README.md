![Alt text](img/fdf_scrot_1.png?raw=true "fdf")
![Alt text](img/fdf_scrot_2.png?raw=true "fdf")
![Alt text](img/fdf_scrot_3.png?raw=true "fdf")
![Alt text](img/fdf_scrot_4.png?raw=true "fdf")
![Alt text](img/fdf_scrot_5.png?raw=true "fdf")
![Alt text](img/fdf_scrot_6.png?raw=true "fdf")
![Alt text](img/fdf_scrot_7.png?raw=true "fdf")

#fdf
This project consist to create graphically the schematic representation of a ground in relief.

Compile both on Mac and Linux. (with X11)

# How to launch :

- git clone http://github.com/pbillett/fdf.git && cd fdf
- make re && ./fdf [file]
<code>

      example : ./fdf maps/42.fdf
      
                ./fdf maps/20-60.fdf
                
                ./fdf maps/basictest.fdf
                
                ./fdf maps/pyramide.fdf
                
                ./fdf maps/mars.fdf
</code>

# Shortcut :

<h3>Mouse:</h3>

- Left click: Rotate around obj
- Spacebar + Left click: Move obj
- Mouse wheels Click + go Up/Down: Increase/decrease field level
- Mouse wheels Click + go left/right: Narrower/Wider field level

<h3>Keyboard:</h3>

- F1: Help toogle 
- F2|F3: Iso Mode / Para Mode
- Arrow keys Numpad (R/L/Up/Dwn): Move fdf
- Arrow keys (R/L/Up/Dwn): Rotate fdf
- PgUp/PgDown: Increase/decrease field level
- +/- Numpad: Zoom/UnZoom
- 1/2/3/4: Dot/Wireframe/Tesselate/Fill faces (warning fill faces could slow down rendering on high density map)
- W/E/R: Gizmo toggle Move/Rotate/Scale (WIP)
- P: Paint tool toogle.(draw with left button, P key again to stop).
- T: Turntable toggle (to automatically rotate object around pivot gizmo point). (Insert to move pivot point)
- Insert: Move pivot point ('W' then 'insert', then move pivot point with Numpad arrows keys).
- Escape: Quit


# Compilation possible issues

<h3>Linux</h3>

- Compilation of the Minilibx under Linux needs X11 and Xext dependencies, to install them simply enter this command:
- sudo apt-get install libx11-dev && sudo apt-get install libxext-dev (You should now found all the file under /usr/include/X11/).
- for an eventual problem of use of strlcpy, just comment the line in the file ./minilibx/mlx_xpm.c and uncomment the line just over it that use strcpy.

<h3>Mac</h3>

- Compiltation on Mac should not have any pb issue. As framework OpenGl and framework appKit should be installed by default,
- But if not just use this command line instead of classic make re.
- gcc -o fdf *.c -lm -L libft -lft -L minilibx_macos -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit</br>

That's it !
You should now be able to run this project on Mac and Linux.
Enjoy !
