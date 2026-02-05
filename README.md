# 📊 Memory Access Pattern Tracer (Real-Time)

Un outil C de traçage mémoire en temps réel, basé sur l'injection dynamique (LD_PRELOAD), permettant de suivre et d'analyser les accès mémoire (allocations, lectures, écritures) d'un programme cible.

## Structure du projet

```
memory_tracer/
├── src/
│   ├── tracer.c           # Implémentation du traçage mémoire
│   └── main.c             # Exemple d'utilisation (optionnel)
├── include/
│   └── tracer.h           # Déclarations des fonctions de traçage
├── bin/
├── tests/
│   └── test_app.c         # Application de test
├── Makefile               # Compilation et installation
├── README.md              # Documentation
└── LICENSE
```

## Fonctionnalités principales
- Traçage en temps réel des appels à malloc, free, realloc, calloc, memcpy, memset, etc.
- Journalisation des accès mémoire dans un fichier CSV (adresse, type d'accès, timestamp, taille, thread).
- Utilisation de LD_PRELOAD pour l'injection transparente dans n'importe quelle application C/C++.
- Faible surcharge et configuration simple.

## Compilation
```bash
make
```

## Utilisation
```bash
LD_PRELOAD=./bin/libmemorytracer.so ./tests/test_app
```

## Analyse des résultats
Le fichier `memory_access_log.csv` contient les accès mémoire détectés :
```
timestamp,thread_id,access_type,address,size
...
```

## Extension
- Support multi-thread
- Ajout d'autres fonctions à tracer
- Visualisation Python

---

**Outil éducatif et de diagnostic.**