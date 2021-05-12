# portage vers NetBSD: _Nuklear_

Si, après bien des déboires, j'arrive à compiler l'exemple `Nuklear-sample`,  l'exécutable obtenu ne fonctionne pas.

## compilation: part I
Voici une session complète pour compiler correctement `Nuklear-sample`:

```
$ mkdir build
$ cd build
$ export LDFLAGS="-L/usr/X11R7/lib -L/usr/pkg/lib" 
$ export CFLAGS="-I/usr/pkg/include" 
$ cmake ..
$ gmake Nuklear-sample
```

## exécution: part I
Voici un exemple de session:

```
$ export LD_LIBRARY_PATH=/usr/X11R7/lib:/usr/pkg/lib
$ ./Nuklear-sample 
  libGL error: MESA-LOADER: failed to retrieve device information
  Error 65543: GLX: Failed to create context: GLXBadFBConfig
```
### remarques

Les outils `glxinfo` et `glxgear` fonctionnent correctement.

## les démos de _Nuklear_
Il y a trois démos basées sur _glfw_. Bien que la compilation se déroule sans erreurs ni mme warnings, l'exécution échoue comme avec mon code. Pour le moment, on peut dire avec certitude que ça vinet de l'installation ou la configuration de _MESA_ ou _glfwf_.

Après bien des essais, c'est en supprimant les fichiers `/usr/pkg/lib/libGL.so.*` que les démos fonctionnent correctement. Le petit plus est aussi d'avoir utilisé `pkg-config --libs` pour obtenir la bonne ligne de commande pour l'édition de lien. Ces fichiers correspondent à une version 1.2.0 d'_OpenGL_ alors que dans `/usr/X11R7/lib` il y a tout pour la version 3.0. Au moment de l'édition des liens et/ou du lancement de l'application, le mélange des deux versions n'était  pas bon du tout.

## retour sur mon code
Enfin, `Nuklear_sampl` compile et, de plus, fonctionne sans l'aide de la variable (genante) `LD_LIBRARY_PATH`.













