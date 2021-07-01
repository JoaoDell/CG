# CG


Compilação feita com: gcc ob3d.c ..\GLib.c -lglfw3 -lglew32 -lgdi32 -lopengl32 -lSDL2_image -lSDL2main -lSDL2 -o ob3d


A versão sendo rodada do SDL que deu certo foi apenas a 2.0.1. Acima dessa versão estava dando problema.

Mude o include da GLib.h para a pasta que você vai estar usando.
