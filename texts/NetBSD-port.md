# portage vers NetBSD

C'est _compliqué_! Il y a deux parties essentielles:

- _[Nuklear](NetBSD-Nuklear-port.md)_, et je ne m'attendais vraiment pas à avoir des prolèmes,
- le _code système_, c'est à dire le nombre de processeurs, la taille de la RAM, etc.

## notes rapides et, parfois, importantes
### le répertoire `texts`
Il contient des fichiers _Markdown_, dont celui-ci, qui documentent  code et application, relatent les (més)aventures du développeur et bien d'autres choses encore si je n'y prend garde.

La feuille de style `texts.css` est utilisée par l'application _ReText_, éditeur de _Markdown_ avec aperçu dynamique.

### X11 et `sudo`
Par défaut, après un `sudo -i`, les applicatioins graphiques échouent au démarrage en signalant un problème de `DISPLAY`. Pour ne plus etre em...merdé, avec `visudo`, on décommente la ligne:

```
Defaults env_keep += "XAPPLRESDIR XFILESEARCHPATH XUSERFILESEARCHPATH"
```

