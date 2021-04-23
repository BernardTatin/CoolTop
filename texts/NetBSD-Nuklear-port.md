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


