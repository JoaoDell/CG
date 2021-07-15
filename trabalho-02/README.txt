VERSÕES:
- SDL2:      2.0.14
- SDL_image: 2.0.1
- GLEW:      2.10
- GLFW:      3.3.4

CÓDIGO ESCRITO PRINCIPALMENTE MAS NÃO EXCLUSIVAMENTE NO WINDOWS

Comando de compilação: 
gcc scene3d.c ..\include\GLib.c -lglfw3 -lglew32 -lgdi32 -lopengl32 -lSDL2_image -lSDL2main -lSDL2 -o scene3d
